#include "charger_init.h"

#include "driver/gpio.h"
#include "esp_attr.h"
#include "sdkconfig.h"
#include "../log/log.h"
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define CHARGER_AUTO_STOP_IN_PROGRESS_SEC 	180
#define CHARGER_AUTO_STOP_SEC 				30

#define CHARGER_TASK_STACK_SIZE 			2048

#define CHARGER_COMMAND_UNKNOWN 	0x00
#define CHARGER_COMMAND_OFF 		0x01
#define CHARGER_COMMAND_ON  		0x02
#define CHARGER_COMMAND_CONFIRM_IN_PROGRESS  0x03

#define CHARGER_LOG_EVENTS true

uint32_t charger_auto_stop = 0;
QueueHandle_t charger_auto_stop_queue = NULL;
t_isr_charger_onkeypress charger_isr_onkeypress_handler = NULL;

static void IRAM_ATTR isr_charger_on_button_click(void* arg) {
	if (charger_isr_onkeypress_handler != NULL) {
		charger_isr_onkeypress_handler();
		return;
	}

	uint8_t level = gpio_get_level(CONFIG_PIN_CHARGER_ENABLE);
	level = ((level == 1) ? CHARGER_COMMAND_OFF : CHARGER_COMMAND_ON);

    xQueueSendFromISR(charger_auto_stop_queue, &level, NULL);
}

static void charger_auto_stop_on_timeout(void* arg) {
	uint8_t command;
	while(true) {
		command = CHARGER_COMMAND_UNKNOWN;
		xQueueReceive(charger_auto_stop_queue, &command, 100 / portTICK_PERIOD_MS);

		if (command == CHARGER_COMMAND_OFF) {
			gpio_set_level(CONFIG_PIN_CHARGER_ENABLE, 0);
			charger_auto_stop = 0;
		} else if (command == CHARGER_COMMAND_ON) {
			gpio_set_level(CONFIG_PIN_CHARGER_ENABLE, 1);
			charger_auto_stop = time(NULL) + CHARGER_AUTO_STOP_SEC;
		} else if (command == CHARGER_COMMAND_CONFIRM_IN_PROGRESS) {
			if (charger_auto_stop != 0) {
				charger_auto_stop = time(NULL) + CHARGER_AUTO_STOP_IN_PROGRESS_SEC;
			}
		} else if (charger_auto_stop > 0) {
			if (time(NULL) > charger_auto_stop) {
				gpio_set_level(CONFIG_PIN_CHARGER_ENABLE, 0);
				charger_auto_stop = 0;
			}
		}
	}
}

void charger_init() {
	charger_auto_stop_queue = xQueueCreate(5, sizeof(uint8_t));
	xTaskCreate(charger_auto_stop_on_timeout, "charger_auto_stop", CHARGER_TASK_STACK_SIZE, NULL, 10, NULL);

	ESP_LOGI(LOG_CHARGER, "Initializing output pin...");

	gpio_config_t chargerEnableConfig = {
		.intr_type = GPIO_INTR_DISABLE,
	    .mode = GPIO_MODE_INPUT_OUTPUT,
		.pin_bit_mask = BIT64(CONFIG_PIN_CHARGER_ENABLE),
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE,
	};

	esp_err_t res = gpio_config(&chargerEnableConfig);
	if (res) {
		ESP_LOGE(LOG_CHARGER, "gpio_config error: %d", res);
		return;
	}

	uint8_t level = CHARGER_COMMAND_OFF;
    xQueueSend(charger_auto_stop_queue, &level, 0);

	ESP_LOGI(LOG_CHARGER, "Initializing input pin...");

	gpio_config_t buttonConfig = {
		.intr_type = GPIO_INTR_POSEDGE,
		.pin_bit_mask = BIT64(CONFIG_PIN_CHARGER_START_BUTTON),
		.mode = GPIO_MODE_INPUT,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE
	};

	res = gpio_config(&buttonConfig);
	if (res) {
		ESP_LOGE(LOG_CHARGER, "gpio_config error: %d", res);
		return;
	}

	res = gpio_set_intr_type(CONFIG_PIN_CHARGER_START_BUTTON, GPIO_INTR_NEGEDGE);
	if (res) {
		ESP_LOGE(LOG_CHARGER, "gpio_set_intr_type error: %d", res);
		return;
	}

	res = gpio_install_isr_service(0);
	if (res && res != ESP_ERR_INVALID_STATE) {
		ESP_LOGE(LOG_CHARGER, "gpio_install_isr_service error: %d", res);
		return;
	}

    res = gpio_isr_handler_add(CONFIG_PIN_CHARGER_START_BUTTON, isr_charger_on_button_click, NULL);
	if (res) {
		ESP_LOGE(LOG_CHARGER, "gpio_isr_handler_add A error: %d", res);
		return;
	}

	ESP_LOGI(LOG_CHARGER, "Charger initialied");
}

void charger_stop() {
	uint8_t level = CHARGER_COMMAND_OFF;
    xQueueSend(charger_auto_stop_queue, &level, 0);
}

void charger_confirm_in_progress() {
	uint8_t level = CHARGER_COMMAND_CONFIRM_IN_PROGRESS;
    xQueueSend(charger_auto_stop_queue, &level, 0);
}

void charger_set_isr_onkeypress_handler(t_isr_charger_onkeypress handler) {
	charger_isr_onkeypress_handler = handler;
}


