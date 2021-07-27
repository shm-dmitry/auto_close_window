#include "sdkconfig.h"

#include "init/init.h"
#include "init/mqtt.h"
#include "init/init_logger.h"
#include "init/mqtt_logger.h"
#include "servo/servo.h"

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

#if CONFIG_SERVO_ENABLED
	servo_init(CONFIG_SERVO_GPIO, CONFIG_SERVO_MQTT_TOPIC_COMMAND, CONFIG_SERVO_MQTT_TOPIC_STATUS);
#endif

	mqtt_start();

#if CONFIG_MQTT_INIT_LOGGER_ENABLED
	init_logger_dump_messages(CONFIG_MQTT_INIT_LOGGER_TOPIC);
#endif

	while(true) {
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

