#include "charger/charger_init.h"
#include "stepper/stepper_init.h"
#include "fm/fm_sender.c"
#include "fm/fm_receiver.c"
#include "common/nvs_rw.h"
#include "common/wifi.h"
#include "common/mqtt.h"
#include "controller/controller_mqtt.h"

#include "stdbool.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
	nvs_init();
	wifi_init();

	controller_init();
	charger_init();
	stepper_init();
	fm_sender_init();
	fm_receiver_init();
	controller_mqtt_init();

	mqtt_start();

	_ESP_LOGI(LOG_MAIN, "Firmware initialied");

	vTaskDelay(1000 / portTICK_PERIOD_MS);
	controller_publish_status();

	_ESP_LOGI(LOG_MAIN, "Initial status published");

	while(true) {
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
