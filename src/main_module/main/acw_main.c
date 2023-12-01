#include "charger/charger_init.h"
#include "stepper/stepper_init.h"
#include "fm/fm_sender.c"
#include "fm/fm_receiver.c"
#include "common/nvs_rw.h"
#include "common/wifi.h"
#include "common/mqtt.h"

#include "stdbool.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
	nvs_init();
	wifi_init();

	charger_init();
	stepper_init();
	fm_sender_init();
	fm_receiver_init();

	mqtt_start();

	while(true) {
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
