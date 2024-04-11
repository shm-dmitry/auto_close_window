#include "fm_sender.h"

#include "driver/rmt_tx.h"
#include "stddef.h"
#include "sdkconfig.h"
#include "../log/log.h"
#include "stdbool.h"
#include "fm_command_encoder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "fm_receiver.h"

#define FM_SENDER_TASK_STACK_SIZE 2048

rmt_channel_handle_t tx_channel = NULL;
rmt_encoder_handle_t fm_send_encoder = NULL;
QueueHandle_t fm_send_queue = NULL;

static void fm_sender_task(void* arg) {
    rmt_transmit_config_t transmit_config = {
        .loop_count = 0, // no loop
    };

	while(true) {
		t_fm_command tx_command;
		xQueueReceive(fm_send_queue, &tx_command, portMAX_DELAY);

		while(!fm_receiver_is_air_clean()) {
			vTaskDelay(100 / portTICK_PERIOD_MS);
		}

	    uint8_t * buffer = NULL;
	    uint8_t buffer_size = 0;
		fm_command_encode(&tx_command, &buffer, &buffer_size);
		if (buffer != NULL) {
			_ESP_LOGI(LOG_FM_SENDER, "Sending command %04X [ %02X %02X %02X %02X %02X %02X ]",
					tx_command.address,
					buffer[0],
					buffer[1],
					buffer[2],
					buffer[3],
					buffer[4],
					buffer[5]);

			ESP_ERROR_CHECK(rmt_transmit(tx_channel,
										 fm_send_encoder,
										 buffer,
										 buffer_size,
										 &transmit_config));

			free(buffer);
			buffer = NULL;
		}

		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

void fm_sender_init() {
    rmt_tx_channel_config_t tx_chan_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .gpio_num = CONFIG_PIN_FM_OUT_433,
        .mem_block_symbols = 64,
        .resolution_hz = 1 * 1000 * 1000,
        .trans_queue_depth = 2,
    };

    esp_err_t res = rmt_new_tx_channel(&tx_chan_config, &tx_channel);
    if (res) {
		_ESP_LOGE(LOG_FM_SENDER, "rmt_new_tx_channel error: %d", res);
		return;
    }

    res = rmt_enable(tx_channel);
    if (res) {
		_ESP_LOGE(LOG_FM_SENDER, "rmt_enable error: %d", res);
		return;
    }

    rmt_new_ir_nec_encoder(&fm_send_encoder);

	fm_send_queue = xQueueCreate(10, sizeof(t_fm_command));

	xTaskCreate(fm_sender_task, "FM sender", FM_SENDER_TASK_STACK_SIZE, NULL, 10, NULL);

    _ESP_LOGI(LOG_FM_SENDER, "FM Sender initialized");
}

void fm_sender_send(const t_fm_command * command) {
    xQueueSend(fm_send_queue, command, ( TickType_t ) 10);
}
