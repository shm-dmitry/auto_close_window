#include "controller_mqtt.h"

#include "../cjson/cjson_helper.h"
#include "../common/mqtt.h"
#include "sdkconfig.h"
#include "../stepper/stepper_init.h"
#include "../log/log.h"
#include "controller.h"

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
	} else if (strcmp(type, "cancel_error") == 0) {
		stepper_cancel_error();
	} else if (strcmp(type, "stepper_noise_alarm") == 0) {
		uint8_t v = get_boolean_from_json(cJSON_GetObjectItem(root, "enable"), 1, 0, 0xFF);
		if (v != 0xFF) {
			stepper_noise_alarm_enable(v == 1);
		}
	} else if (strcmp(type, "stepper_lsw_enabled") == 0) {
		uint8_t v = get_boolean_from_json(cJSON_GetObjectItem(root, "enable"), 1, 0, 0xFF);
		if (v != 0xFF) {
			stepper_limit_switch_enable(v == 1);
		}
	} else if (strcmp(type, "controller_light_open_percent") == 0) {
		uint8_t v = get_number8_from_json(cJSON_GetObjectItem(root, "value"), 0xFF);
		if (v != 0xFF) {
			controller_set_light_open_percent(v);
		}
	} else if (strcmp(type, "controller_fm_pdu_enabled") == 0) {
		uint8_t v = get_boolean_from_json(cJSON_GetObjectItem(root, "enable"), 1, 0, 0xFF);
		if (v != 0xFF) {
			controller_set_fm_pdu_enabled(v == 1);
		}
	}

	cJSON_Delete(root);
}

void controller_mqtt_process_om_air_data(int8_t temperature, uint8_t humidity, uint32_t pressure) {
	_ESP_LOGI(LOG_CONTROLLER, "OM AIR status: temperature=%d C, humidity=%d%%, pressure=%li Pa", temperature, humidity, pressure);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "temperature", temperature);
    cJSON_AddNumberToObject(root, "humidity",    humidity);
    cJSON_AddNumberToObject(root, "pressure",    pressure);

    char * json = cJSON_Print(root);
    mqtt_publish(CONFIG_CONTROLLER_MQTT_AIR_STATUS, json);
    cJSON_free(json);

    cJSON_Delete(root);
}

void controller_mqtt_process_bat_status(bool hm, uint16_t v, uint16_t i, bool charge) {
    _ESP_LOGI(LOG_CONTROLLER, "Bat %s status: V = %d mV; I = %d mA; charge: %s", (hm ? "HM" : "OM"), v, i, (charge ? "YES" : "NO"));

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "v", v / 1000.0);
    cJSON_AddNumberToObject(root, "i", i);
    cJSON_AddBoolToObject(root, "charge", charge);

    char * json = cJSON_Print(root);
    mqtt_publish(hm ? CONFIG_CONTROLLER_MQTT_HM_BAT_STATUS : CONFIG_CONTROLLER_MQTT_OM_BAT_STATUS, json);
    cJSON_free(json);

    cJSON_Delete(root);
}

void controller_mqtt_process_om_noise_alarm(bool alarm) {
    _ESP_LOGI(LOG_CONTROLLER, "OM NOISE alarm: %s", (alarm ? "ON" : "OFF"));

    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "noise_alarm", alarm);

    char * json = cJSON_Print(root);
    mqtt_publish(CONFIG_CONTROLLER_MQTT_NOISE_ALARM, json);
    cJSON_free(json);

    cJSON_Delete(root);
}

void controller_mqtt_process_om_noise_data(uint8_t freq1, uint8_t level1, uint8_t freq2, uint8_t level2, uint8_t freq3, uint8_t level3, uint8_t freq4, uint8_t level4, uint8_t freq5, uint8_t level5) {
	_ESP_LOGI(LOG_CONTROLLER, "OM NOISE data: freq1: [ %d = %d ]; freq2: [ %d = %d ]; freq3: [ %d = %d ]; freq4: [ %d = %d ]; freq5: [ %d = %d ]",
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

void controller_mqtt_on_stepper_error(bool error) {
    mqtt_publish(CONFIG_CONTROLLER_MQTT_STEPPER_ERROR, error ? "on" : "off");
}

void controller_mqtt_limit_switch_enabled(bool enabled) {
    mqtt_publish(CONFIG_CONTROLLER_MQTT_LIMIT_SWITCH_ENABLE_STATUS, enabled ? "on" : "off");
}

void controller_mqtt_noise_alarm_enabled(bool enabled) {
    mqtt_publish(CONFIG_CONTROLLER_MQTT_STEPPER_NOISE_ALARM_STATUS, enabled ? "on" : "off");
}

void controller_mqtt_fm_pdu_enabled(bool enabled) {
    mqtt_publish(CONFIG_CONTROLLER_MQTT_FM_PDU_ENABLE_STATUS, enabled ? "on" : "off");
}

void controller_mqtt_stepper_position_updated(uint8_t percent) {
	cJSON *root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "value", (percent > 100 ? 0 : percent));
	cJSON_AddBoolToObject(root, "ok", (percent <= 100));

	char * json = cJSON_Print(root);
	mqtt_publish(CONFIG_CONTROLLER_MQTT_STEPPER_POSITION, json);
	cJSON_free(json);

	cJSON_Delete(root);
}

void controller_mqtt_init() {
	mqtt_subscribe(CONFIG_CONTROLLER_MQTT_COMMANDS_TOPIC, controller_mqtt_stepper_callback);
}
