#include "init_logger.h"

#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "mqtt.h"
#include "../cjson/cJSON.h"

static char ** init_logger_messages = NULL;
static size_t init_logger_messages_count = 0;
static bool init_logger_enabled = false;

void init_logger_enable() {
	init_logger_enabled = true;
}

void init_logger_add(const char * message) {
	if (init_logger_enabled == false) {
		return;
	}

	char ** newmessages = malloc(sizeof(char *) * (init_logger_messages_count + 1));
	if (init_logger_messages_count > 0) {
		memcpy(newmessages, init_logger_messages, sizeof(char *) *init_logger_messages_count );
	}

	newmessages[init_logger_messages_count] = malloc(strlen(message) + 1);///
	memcpy(newmessages[init_logger_messages_count], message, strlen(message) + 1);

	free(init_logger_messages);
	init_logger_messages = newmessages;
	init_logger_messages_count++;
}

void init_logger_add_success(const char * message) {
	init_logger_add(message);
}

void init_logger_add_fail(const char * message, esp_err_t error) {
	char * withparam = malloc(strlen(message) + 50);
	snprintf(withparam, strlen(message) + 50, message, error);
	init_logger_add(withparam);
	free(withparam);
}

void init_logger_dump_messages(const char * topic) {
	if (init_logger_enabled == false || init_logger_messages_count == 0) {
		return;
	}

	cJSON *root = cJSON_CreateArray();

	for (size_t i = 0; i<init_logger_messages_count; i++) {
		cJSON_AddItemToArray(root, cJSON_CreateString(init_logger_messages[i]));
	}

	char * json = cJSON_Print(root);
	mqtt_publish(topic, json);
	cJSON_free(json);

	cJSON_Delete(root);

	for (size_t i = 0; i<init_logger_messages_count; i++) {
		free(init_logger_messages[i]);
	}

	free(init_logger_messages);
	init_logger_messages_count = 0;
}
