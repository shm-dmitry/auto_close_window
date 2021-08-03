#include "sdkconfig.h"

#include "init/init.h"
#include "init/mqtt.h"
#include "init/init_logger.h"
#include "init/mqtt_logger.h"
#include "controller/controller.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
#if CONFIG_MQTT_INIT_LOGGER_ENABLED
	mqtt_logger_start();
#endif

#if CONFIG_MQTT_INIT_LOGGER_ENABLED
	init_logger_enable();
#endif

	init_flash();
	init_wifi(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD, CONFIG_WIFI_TOPIC);
	init_snmp();

	controller_init();

	mqtt_start();

#if CONFIG_MQTT_INIT_LOGGER_ENABLED
	init_logger_dump_messages(CONFIG_MQTT_INIT_LOGGER_TOPIC);
#endif

	while(true) {
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

