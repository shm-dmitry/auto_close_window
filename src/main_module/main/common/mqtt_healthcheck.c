#include "mqtt_healthcheck.h"

#include "mqtt.h"

#include "sdkconfig.h"
#include "esp_timer.h"
#include "../log/log.h"
#include "string.h"

#include "esp_system.h"

#define MQTT_HEALTHCHECK_PERIOD 30000000
 // 30 secs * 6 retrys = 3 minutes without wifi/mqtt broker -> restart
#define MQTT_HEALTHCHECK_MAX_ERRORS_COUNT 6

uint8_t mqtt_healthcheck_errors_count = 0;

uint8_t mqtt_healthcheck_sended_counter = 0;
uint8_t mqtt_healthcheck_received_counter = 0;

void mqtt_healthcheck_events(const char * topic, const char * data) {
	if (strcmp(data, "restart") == 0) {
		_ESP_LOGE(LOG_MQTT, "Healthcheck received %s command from topic %s. Restart!", data, topic);
		esp_restart();
	} else {
		mqtt_healthcheck_received_counter = atoi(data);
	}
}

void mqtt_healthcheck_task(void* arg) {
	if (mqtt_healthcheck_sended_counter == mqtt_healthcheck_received_counter) {
		mqtt_healthcheck_errors_count = 0;
	} else {
		_ESP_LOGW(LOG_MQTT, "Healthcheck error [%d]: mistmatch counters: sended (%d) != last received (%d)", mqtt_healthcheck_errors_count, mqtt_healthcheck_sended_counter, mqtt_healthcheck_received_counter);
		mqtt_healthcheck_errors_count++;
	}

	if (mqtt_healthcheck_errors_count > MQTT_HEALTHCHECK_MAX_ERRORS_COUNT) {
		_ESP_LOGE(LOG_MQTT, "Healthcheck ERROR: counter == %d. Restart!", mqtt_healthcheck_errors_count);
		esp_restart();
	}

	mqtt_healthcheck_sended_counter++;
	char message[5];
	memset(message, 0, 5);
	snprintf(message, 5, "%d", mqtt_healthcheck_sended_counter);
	mqtt_publish_nolog(CONFIG_MQTT_HEALTHCHECK_TOPIC, message);
}

void mqtt_healthcheck_init() {
	mqtt_healthcheck_errors_count = 0;
	mqtt_healthcheck_sended_counter = 0;
	mqtt_healthcheck_received_counter = 0;

	mqtt_subscribe_nolog(CONFIG_MQTT_HEALTHCHECK_TOPIC, mqtt_healthcheck_events);

	esp_timer_create_args_t periodic_timer_args = {
			.callback = &mqtt_healthcheck_task,
			/* name is optional, but may help identify the timer when debugging */
			.name = "mqtt healthcheck task"
	};

	esp_timer_handle_t periodic_timer;
	ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
	ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, MQTT_HEALTHCHECK_PERIOD));
}
