#include "controller_mqtt.h"

#include "../cjson/cjson_helper.h"
#include "../common/mqtt.h"
#include "sdkconfig.h"
#include "../stepper/stepper_init.h"
#include "../log/log.h"

#include "string.h"

void controller_mqtt_stepper_callback(const char * topic, const char * data) {
	cJSON *root = cJSON_Parse(data);
	if (root == NULL) {
		return;
	}

	const char * type = cJSON_GetStringValue(cJSON_GetObjectItem(root, "type"));

	if (strcmp(type, "move") == 0) {
		uint8_t percent = get_number8_from_json(cJSON_GetObjectItem(root, "percent"), 0xFF);
		if (percent <= 100) {
			stepper_move_to(percent);
		}
	} else if (strcmp(type, "calibrate") == 0) {
		stepper_calibrate();
	}

	cJSON_Delete(root);
}

void controller_mqtt_process_om_air_data(int8_t temperature, uint8_t humidity, uint32_t pressure) {
	ESP_LOGI(LOG_CONTROLLER, "OM AIR status: temperature=%d C, humidity=%d%%, pressure=%li Pa", temperature, humidity, pressure);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "temperature", temperature);
    cJSON_AddNumberToObject(root, "humidity",    humidity);
    cJSON_AddNumberToObject(root, "pressure",    pressure);

    char * json = cJSON_Print(root);
    mqtt_publish(CONFIG_CONTROLLER_MQTT_AIR_STATUS, json);
    cJSON_free(json);

    cJSON_Delete(root);
}

void controller_mqtt_process_om_noise_alarm(bool alarm) {
    ESP_LOGI(LOG_CONTROLLER, "OM NOISE alarm: %s", (alarm ? "ON" : "OFF"));

    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "noise_alarm", alarm);

    char * json = cJSON_Print(root);
    mqtt_publish(CONFIG_CONTROLLER_MQTT_NOISE_ALARM, json);
    cJSON_free(json);

    cJSON_Delete(root);
}

void controller_mqtt_process_om_noise_data(uint8_t freq1, uint8_t level1, uint8_t freq2, uint8_t level2, uint8_t freq3, uint8_t level3, uint8_t freq4, uint8_t level4, uint8_t freq5, uint8_t level5) {
	ESP_LOGI(LOG_CONTROLLER, "OM NOISE data: freq1: [ %d = %d ]; freq2: [ %d = %d ]; freq3: [ %d = %d ]; freq4: [ %d = %d ]; freq5: [ %d = %d ]",
			freq1, level1,
			freq2, level2,
			freq3, level3,
			freq4, level4,
			freq5, level5
			);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "freq1", freq1);
    cJSON_AddNumberToObject(root, "level1", level1);
    cJSON_AddNumberToObject(root, "freq2", freq2);
    cJSON_AddNumberToObject(root, "level2", level2);
    cJSON_AddNumberToObject(root, "freq3", freq3);
    cJSON_AddNumberToObject(root, "level3", level3);
    cJSON_AddNumberToObject(root, "freq4", freq4);
    cJSON_AddNumberToObject(root, "level4", level4);
    cJSON_AddNumberToObject(root, "freq5", freq5);
    cJSON_AddNumberToObject(root, "level5", level5);

    char * json = cJSON_Print(root);
    mqtt_publish(CONFIG_CONTROLLER_MQTT_NOISE_STATUS, json);
    cJSON_free(json);

    cJSON_Delete(root);
}

void controller_mqtt_on_stepper_current_open(uint8_t percent) {
    cJSON *root = cJSON_CreateObject();
    if (percent <= 100) {
    	cJSON_AddNumberToObject(root, "percent", percent);
        cJSON_AddBoolToObject(root, "ok", true);
    } else {
        cJSON_AddBoolToObject(root, "ok", false);
    }

    char * json = cJSON_Print(root);
    mqtt_publish(CONFIG_CONTROLLER_MQTT_NOISE_STATUS, json);
    cJSON_free(json);

    cJSON_Delete(root);
}

void controller_mqtt_init() {
	mqtt_subscribe(CONFIG_CONTROLLER_MQTT_STEPPER_TOPIC, controller_mqtt_stepper_callback);
}
