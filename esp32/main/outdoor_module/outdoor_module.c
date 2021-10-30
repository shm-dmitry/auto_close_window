#include "outdoor_module.h"

#include "outdoor_module_api.h"
#include "../cjson/cjson_helper.h"
#include "../init/mqtt.h"
#include "../log.h"
#include "string.h"

static char* outdoor_module_status_topic = NULL;

void outdoor_module_callback(const outdoor_module_data_t * data) {
	cJSON *root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "temperature",  data->temperature);
	cJSON_AddNumberToObject(root, "tvoc",  data->tvoc);
	if (data->noise != NULL) {
		cJSON *array = cJSON_AddArrayToObject(root, "noise");
		for (int i = 0; i<data->noise->count; i++) {
			cJSON * elem = cJSON_CreateObject();
			cJSON_AddNumberToObject(elem, "freq",  data->noise->freq[i]);
			cJSON_AddNumberToObject(elem, "vol",  data->noise->vol[i]);
			cJSON_AddItemToArray(array, elem);
		}
	}

	char * json = cJSON_Print(root);
	mqtt_publish(outdoor_module_status_topic, json);
	cJSON_free(json);

	cJSON_Delete(root);
}

void outdoor_module_init(int gpio, const char * status_topic) {
	outdoor_module_status_topic = malloc(strlen(status_topic) + 1);
	memset(outdoor_module_status_topic, 0, strlen(status_topic) + 1);
	memcpy(outdoor_module_status_topic, status_topic, strlen(status_topic) + 1);

	esp_err_t res = outdoor_module_api_init(gpio, outdoor_module_callback);
	if (res) {
		ESP_LOGE(OUTDOOR_MODULE_LOG, "outdoor_module_api_init error %d", res);
	} else {
		ESP_LOGI(OUTDOOR_MODULE_LOG, "outdoor module initialized on port %d", gpio);
	}
}
