#include "mqtt_logger.h"

#include "string.h"
#include "stdlib.h"
#include "../cjson/cjson_helper.h"
#include "mqtt.h"
#include "stdarg.h"
#include "stdio.h"
#include "nvs_rw.h"

#include "sdkconfig.h"

#define MQTT_LOGGER_PARAM "mqtt_logger"

static bool mqtt_logger_enabled = true;

void mqtt_logger_commands(const char * topic, const char * data) {
	cJSON *root = cJSON_Parse(data);
	if (root == NULL) {
		return;
	}

	uint8_t value = get_boolean_from_json(cJSON_GetObjectItem(root, "enabled"), 1, 0, 2);
	if (value != 2) {
		mqtt_logger_enabled = (value == 1);
		nvs_write_buffer(MQTT_LOGGER_PARAM, &value, 1);
	}
}

char * append_mqtt_toic(const char * subtopic) {
	char * topic = malloc(strlen(CONFIG_MQTT_LIVE_LOGGER_TOPIC) + 1 + strlen(subtopic) + 1);
	memcpy(topic, CONFIG_MQTT_LIVE_LOGGER_TOPIC, strlen(CONFIG_MQTT_LIVE_LOGGER_TOPIC));
	topic[strlen(CONFIG_MQTT_LIVE_LOGGER_TOPIC)] = '/';
	strcpy(topic + strlen(CONFIG_MQTT_LIVE_LOGGER_TOPIC) + 1, subtopic);
	return topic;
}

void mqtt_logger_start() {
#if CONFIG_MQTT_LIVE_LOGGER_ENABLED
	char * topic = append_mqtt_toic("commands");

	mqtt_subscribe(topic, mqtt_logger_commands);

	uint8_t * buffer = NULL;
	size_t buffer_size = 0;
	if (nvs_read_buffer(MQTT_LOGGER_PARAM, &buffer, &buffer_size) == ESP_OK) {
		if (buffer_size == 1 && buffer != NULL) {
			mqtt_logger_enabled = (buffer[0] == 1);
		}
	}

	if (buffer) {
		free(buffer);
	}
#endif
}

mqtt_logger_data_t * mqtt_logger_init(const char * logname) {
#if CONFIG_MQTT_LIVE_LOGGER_ENABLED
	if (!mqtt_logger_enabled) {
		return NULL;
	}

	mqtt_logger_data_t * tmp = malloc(sizeof(mqtt_logger_data_t));
	if (tmp == NULL) {
		return NULL;
	}

	memset(tmp, 0, sizeof(mqtt_logger_data_t));

	tmp->logname = malloc(strlen(logname) + 1);
	if (tmp->logname == NULL) {
		free(tmp);
		return NULL;
	}

	strcpy(tmp->logname, logname);

	return tmp;
#else
	return NULL;
#endif
}

void mqtt_logger_append(mqtt_logger_data_t * data, const char * message, ...) {
	if (data == NULL) {
		return;
	}

	if (data->messages_count > 0) {
		char ** copy = malloc(sizeof(char *) * (data->messages_count + 1));
		if (copy == NULL) {
			return;
		}

		memcpy(copy, data->messages, sizeof(char *) * data->messages_count);
		free(data->messages);
		data->messages = copy;
	} else {
		data->messages = malloc(sizeof(char *));
		if (data->messages == NULL) {
			return;
		}
	}

	char * buff = malloc(strlen(message) + 1024);
	va_list args;
	va_start(args, message);
	vsnprintf(buff, strlen(message) + 1024, message, args);
	va_end(args);

	data->messages[data->messages_count] = malloc(strlen(buff) + 1);
	memcpy(data->messages[data->messages_count], buff, strlen(buff) + 1);

	free(buff);

	data->messages_count++;
}

void mqtt_logger_append_hexdump(mqtt_logger_data_t * data, const uint8_t *buffer, uint16_t buff_len) {
	if (data == NULL || buff_len == 0) {
		return;
	}

	char * tmp = malloc(buff_len * 3 + 1);
	if (tmp == NULL) {
		return;
	}

	for (uint16_t i = 0; i<buff_len; i++) {
		if (i % 16 == 0 && i > 0) {
			sprintf(tmp + i*3, "%.2x\n", buffer[i]);
		} else {
			sprintf(tmp + i*3, "%.2x ", buffer[i]);
		}
	}

	if (data->messages_count > 0) {
		char ** copy = malloc(sizeof(char *) * (data->messages_count + 1));
		if (copy == NULL) {
			free(tmp);
			return;
		}

		memcpy(copy, data->messages, sizeof(char *) * data->messages_count);
		free(data->messages);
		data->messages = copy;
	}

	data->messages[data->messages_count] = tmp;
	data->messages_count++;
}

void mqtt_logger_done(mqtt_logger_data_t ** data) {
	if (data == NULL || *data == NULL) {
		return;
	}

#if CONFIG_MQTT_LIVE_LOGGER_ENABLED
	cJSON *arr = cJSON_CreateArray();

	for (size_t i = 0; i<(*data)->messages_count; i++) {
		cJSON_AddItemToArray(arr, cJSON_CreateString((*data)->messages[i]));
	}

	char * topic = append_mqtt_toic((*data)->logname);

	char * json = cJSON_Print(arr);
	mqtt_publish(topic, json);
	cJSON_free(json);

	cJSON_Delete(arr);

	free(topic);

	for (size_t i = 0; i<(*data)->messages_count; i++) {
		free((*data)->messages[i]);
	}

	free(*data);
	*data = NULL;
#endif
}
