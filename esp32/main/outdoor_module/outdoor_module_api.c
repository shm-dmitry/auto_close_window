#include "outdoor_module_api.h"

#include "driver/uart.h"
#include "../log.h"
#include "stdbool.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define OUTDOOR_MODULE_PORT_NUMBER UART_NUM_1
#define OUTDOOR_MODULE_BUFFER_SIZE 2048
#define OUTDOOR_MODULE_TEMPERATURE_OFFSET 100

outdoor_module_callback_t outdoor_module_api_callback = NULL;

bool outdoor_module_api_read_buffer(uint8_t * bytes, uint8_t count, uint8_t * crc) {
	uint8_t position = 0;
	uint16_t retries = 0;

	while (count > 0) {
		if (retries++ > 1000) {
			ESP_LOGE(OUTDOOR_MODULE_LOG, "Timeout");
			return false;
		}

		int len = uart_read_bytes(OUTDOOR_MODULE_PORT_NUMBER, bytes + position, count, 20 / portTICK_RATE_MS);
		if (len > 0) {
			count -= len;
			position += len;
		} else if (len < 0) {
			ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to read data from UART");
			return false;
		}
	}

	if (crc != NULL) {
		for (int i = 0; i<position; i++) {
			*crc += bytes[i];
		}
	}

	return true;
}

bool outdoor_module_api_read_word(uint16_t * word, uint8_t * crc) {
	uint8_t buffer[2] = { 0x00, 0x00 };
	if (!outdoor_module_api_read_buffer(buffer, 2, crc)) {
		return false;
	}

	*word = (buffer[0] << 8) + buffer[1];
	return true;
}

void outdoor_module_api_release_data(outdoor_module_data_t ** data) {
	if ((*data)->noise != NULL) {
		if ((*data)->noise->freq != NULL) {
			free((*data)->noise->freq);
		}
		if ((*data)->noise->vol != NULL) {
			free((*data)->noise->vol);
		}
		free((*data)->noise);
	}
	free(*data);
	*data = NULL;
}

outdoor_module_data_t * outdoor_module_api_read(uint8_t crc) {
	outdoor_module_data_t * temp = malloc(sizeof(outdoor_module_data_t));
	if (temp == NULL) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to allocate data");
		return NULL;
	}

	memset(temp, 0, sizeof(outdoor_module_data_t));

	uint8_t temperature = 0;
	if (!outdoor_module_api_read_buffer(&temperature, 1, &crc)) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to read temperature");
		outdoor_module_api_release_data(&temp);
		return NULL;
	}

	temp->temperature = temperature - OUTDOOR_MODULE_TEMPERATURE_OFFSET;

	if (!outdoor_module_api_read_word(&temp->tvoc, &crc)) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to read tvoc");
		outdoor_module_api_release_data(&temp);
		return NULL;
	}

	uint8_t count = 0;
	if (!outdoor_module_api_read_buffer(&count, 1, &crc)) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to read noise count");
		outdoor_module_api_release_data(&temp);
		return NULL;
	}

	if (count > 0) {
		temp->noise = malloc(sizeof(outdoor_module_noise_data_t));
		if (temp->noise == NULL) {
			ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to allocate noise data");
			outdoor_module_api_release_data(&temp);
			return NULL;
		}

		memset(temp->noise, 0, sizeof(outdoor_module_noise_data_t));
		temp->noise->count = count;
		temp->noise->freq = malloc(sizeof(uint16_t) * count);
		temp->noise->vol = malloc(sizeof(uint16_t) * count);
		if (temp->noise->freq == NULL || temp->noise->vol == NULL) {
			ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to allocate noise freq/vol data. count == %d", count);
			outdoor_module_api_release_data(&temp);
			return NULL;
		}

		memset(temp->noise->freq, 0, sizeof(uint16_t) * count);
		memset(temp->noise->vol, 0, sizeof(uint16_t) * count);

		for (int i = 0; i<count; i++) {
			if (!outdoor_module_api_read_word(&temp->noise->freq[i], &crc)) {
				ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to read noise freq[%d]", i);
				outdoor_module_api_release_data(&temp);
				return NULL;
			}
			if (!outdoor_module_api_read_word(&temp->noise->vol[i], &crc)) {
				ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to read noise vol[%d]", i);
				outdoor_module_api_release_data(&temp);
				return NULL;
			}
		}
	}

	uint8_t read_crc = 0;
	if (!outdoor_module_api_read_buffer(&read_crc, 1, NULL)) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "Failed to read CRC");
		outdoor_module_api_release_data(&temp);
		return NULL;
	}

	if (read_crc != crc) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "Bad CRC. Remote %d / Local %d", read_crc, crc);
		outdoor_module_api_release_data(&temp);
		return NULL;
	}

	return temp;
}

void outdoor_module_api_listener(void* arg) {
	while (true) {
		uint8_t crc = 0;
		uint8_t buffer[3] = { 0x00, 0x00, 0x00 };
		if (!outdoor_module_api_read_buffer(buffer, 3, &crc)) {
			continue;
		}

		if (buffer[0] == 0xA0 && buffer[1] == 0xA1 && buffer[2] == 0xA2) {
			outdoor_module_data_t * data = outdoor_module_api_read(crc);
			if (data != NULL) {
				outdoor_module_api_callback(data);
				outdoor_module_api_release_data(&data);
			}
		} else {
			ESP_LOGE(OUTDOOR_MODULE_LOG, "Bad preambula %02x %02x %02x", buffer[0], buffer[1], buffer[2]);
		}
	}
}

esp_err_t outdoor_module_api_init(int gpio, outdoor_module_callback_t callback) {
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

	esp_err_t res = uart_driver_install(OUTDOOR_MODULE_PORT_NUMBER, OUTDOOR_MODULE_BUFFER_SIZE, OUTDOOR_MODULE_BUFFER_SIZE, 10, NULL, 0);
	if (res) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "uart_driver_install error %d", res);
		return res;
	}

	// Configure UART parameters
	res = uart_param_config(OUTDOOR_MODULE_PORT_NUMBER, &uart_config);
	if (res) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "uart_param_config error %d", res);
		return res;
	}

	res = uart_set_pin(OUTDOOR_MODULE_PORT_NUMBER, UART_PIN_NO_CHANGE, gpio, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	if (res) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "uart_set_pin error %d", res);
		return res;
	}

	outdoor_module_api_callback = callback;

	xTaskCreate(outdoor_module_api_listener, "outdoor module listener", 10240, NULL, 10, NULL);

	return ESP_OK;
}
