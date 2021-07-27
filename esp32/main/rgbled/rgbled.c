#include "rgbled.h"

#include "string.h"

#include "rgbled_api.h"
#include "../cjson/cjson_helper.h"
#include "../init/mqtt.h"
#include "../init/init_logger.h"
#include "../log.h"

void rgbled_commands(const char * topic, const char * data) {
	cJSON *root = cJSON_Parse(data);
	if (root == NULL) {
		return;
	}

	char * type = cJSON_GetStringValue(cJSON_GetObjectItem(root, "type"));
	if (strcmp(type, "set_color") == 0) {
		char * rgbs = cJSON_GetStringValue(cJSON_GetObjectItem(root, "rgb"));
		if (strlen(rgbs) == 0) {
			return;
		}

		char* invptr = NULL;
		uint32_t rgb = strtol(rgbs, &invptr, 16);
		if (invptr == NULL || invptr == rgbs + strlen(rgbs)) {
			rgbled_set_color(rgb);
		} else {
			ESP_LOGE(RGBLED_LOG, "Cant parse RGB color %s. Bad char at position %d", rgbs, (uint32_t)(invptr - rgbs));
		}
	} else if (strcmp(type, "calibrate") == 0) {
		char * rgbs = cJSON_GetStringValue(cJSON_GetObjectItem(root, "rgb"));
		if (strlen(rgbs) == 0) {
			return;
		}

		char* invptr = NULL;
		uint32_t rgb = strtol(rgbs, &invptr, 16);
		if (invptr == NULL || invptr == rgbs + strlen(rgbs)) {
			rgbled_calibrate(rgb);
		} else {
			ESP_LOGE(RGBLED_LOG, "Cant parse RGB color %s. Bad char at position %d", rgbs, (uint32_t)(invptr - rgbs));
		}
	}

	cJSON_Delete(root);
}

void rgbled_startup(const rgbled_config_t * config, const char * command_topic) {
	INIT_DRIVER_AND_LOG_OR_RETURN(rgbled_init(config), "RGBLED Driver initialized", "Cant initialize RGBLED driver: %d");

	mqtt_subscribe(command_topic, rgbled_commands);
}
