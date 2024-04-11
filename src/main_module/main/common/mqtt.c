#include "mqtt.h"

#include "mqtt_client.h"
#include "nvs_rw.h"
#include "sdkconfig.h"
#include "mqtt_healthcheck.h"
#include "mqtt_ota.h"

#include "../log/log.h"

#define MAX_MQTT_URI_LEN 100
#define MAX_MQTT_USER_PASS 20

typedef struct mqtt_callback_mapping_t {
	char * topic;
	mqtt_topic_callback_t function;
	bool logmessages;
} mqtt_callback_mapping_t;

mqtt_callback_mapping_t* callbacks = NULL;
uint8_t callbacks_count = 0;
esp_mqtt_client_handle_t client;

void mqtt_subscribe_impl(const char * topic, mqtt_topic_callback_t callback, bool logmessages);
void mqtt_publish_impl(const char * topic, const char * message, bool logmessages);

static void mqtt_event_handler_cb(esp_mqtt_event_handle_t event) {
	if (callbacks_count == 0 || event == NULL) {
		return;
	}

	switch (event->event_id) {
	case MQTT_EVENT_CONNECTED:
		for (int i = 0; i<callbacks_count; i++) {
			if (callbacks[i].topic) {
				esp_mqtt_client_subscribe_single(event->client, callbacks[i].topic, 0);
			}
		}
		break;
	case MQTT_EVENT_DATA:
		if (event->data && event->topic && event->data_len && event->topic_len && event->data_len < 1024 && event->topic_len < 1024) {
			char * topic = malloc(event->topic_len + 1);
			memset(topic, 0, event->topic_len + 1);
			memcpy(topic, event->topic, event->topic_len);

			char * data = malloc(event->data_len + 1);
			memset(data, 0, event->data_len + 1);
			memcpy(data, event->data, event->data_len);

			for (int i = 0; i<callbacks_count; i++) {
				if (callbacks[i].topic && strcmp(topic, callbacks[i].topic) == 0) {
					if (callbacks[i].logmessages) {
						_ESP_LOGI(LOG_MQTT, "Received message in topic %s : %s", topic, data);
					}

					callbacks[i].function(topic, data);

					break;
				}
			}

			free(topic);
			free(data);
		}
		break;
	default:
		break;
	}
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
	mqtt_event_handler_cb(event_data);
}

char * mqtt_prepend_prefix(const char * topic) {
	if (topic == NULL) {
		return NULL;
	}

	char * str = malloc(strlen(CONFIG_MQTT_TOPICS_PREFIX) + strlen(topic) + 1);
	if (str == NULL) {
		return NULL;
	}

	strcpy(str, CONFIG_MQTT_TOPICS_PREFIX);
	strcpy(str + strlen(CONFIG_MQTT_TOPICS_PREFIX), topic);

	return str;
}

void mqtt_publish_sync(const char * topic, const char * message) {
	if (client) {
		char * temp = mqtt_prepend_prefix(topic);
		if (temp == NULL) {
			return;
		}

		if (esp_mqtt_client_publish(client, temp, message, 0, 0, 1) >= 0) {
	    	_ESP_LOGI(LOG_MQTT, "MQTT publish OK topic = %s, message = %s", temp, message);
		} else {
			mqtt_publish(topic, message);
		}

		free(temp);
		temp = NULL;
	}
}

void mqtt_publish(const char * topic, const char * message) {
	mqtt_publish_impl(topic, message, true);
}

void mqtt_publish_nolog(const char * topic, const char * message) {
	mqtt_publish_impl(topic, message, false);
}

void mqtt_publish_impl(const char * topic, const char * message, bool logmessages) {
	if (client) {
		char * temp = mqtt_prepend_prefix(topic);
		if (temp == NULL) {
			return;
		}

		if (esp_mqtt_client_enqueue(client, temp, message, 0, 0, 1, 1) >= 0) {
			if (logmessages) {
				_ESP_LOGI(LOG_MQTT, "MQTT enqueue OK topic = %s, message = %s", temp, message);
			}
		} else {
	    	_ESP_LOGE(LOG_MQTT, "MQTT enqueue error: topic = %s, message = %s", temp, message);
		}

		free(temp);
		temp = NULL;
	}
}

void mqtt_subscribe_nolog(const char * topic, mqtt_topic_callback_t callback) {
	mqtt_subscribe_impl(topic, callback, false);
}

void mqtt_subscribe(const char * topic, mqtt_topic_callback_t callback) {
	mqtt_subscribe_impl(topic, callback, true);
}

void mqtt_subscribe_impl(const char * topic, mqtt_topic_callback_t callback, bool logmessages) {
	if (callback == NULL) {
		_ESP_LOGW(LOG_MQTT, "Cant subscribe for a topic %s. Callback is NULL.", topic);
		return;
	}

	char * prepended_topic = mqtt_prepend_prefix(topic);

	if (callbacks != NULL) {
		for (uint8_t i = 0; i<callbacks_count; i++) {
			if (strcmp(callbacks[i].topic, prepended_topic) == 0) {
				if (callbacks[i].function != callback) {
					_ESP_LOGW(LOG_MQTT, "Duplicated subscription to topic %s. Callback overrided from %p to %p", prepended_topic, callbacks[i].function, callback);
					callbacks[i].function = callback;
				} else {
					_ESP_LOGW(LOG_MQTT, "Duplicated subscription to topic %s with same callback", prepended_topic);
				}

				callbacks[i].logmessages = logmessages;

				free(prepended_topic);
				prepended_topic = NULL;

				return;
			}
		}
	}

	mqtt_callback_mapping_t* newtable = (mqtt_callback_mapping_t*) malloc(sizeof(mqtt_callback_mapping_t) * (callbacks_count + 1));
	memset(newtable, 0, sizeof(mqtt_callback_mapping_t) * (callbacks_count + 1));

	if (callbacks_count > 0) {
		memcpy(newtable, callbacks, sizeof(mqtt_callback_mapping_t) * callbacks_count);
		free(callbacks);
		callbacks = NULL;
	}

	callbacks = newtable;

	callbacks[callbacks_count].topic       = prepended_topic;
	callbacks[callbacks_count].function    = callback;
	callbacks[callbacks_count].logmessages = logmessages;

	if (callbacks[callbacks_count].topic) {
		_ESP_LOGI(LOG_MQTT, "Client subscribed on topic %s", callbacks[callbacks_count].topic);
	} else {
		_ESP_LOGE(LOG_MQTT, "Cant allocate memory to subscribe on topic %s%s", CONFIG_MQTT_TOPICS_PREFIX, topic);
	}

	callbacks_count++;
}

void mqtt_start() {
	client = NULL;

	esp_mqtt_client_config_t mqtt_cfg = {
		.broker.address.uri = CONFIG_MQTT_BROKER_URI,
		.credentials = {
			.username = CONFIG_MQTT_BROKER_USERNAME,
			.authentication.password = CONFIG_MQTT_BROKER_PASSWORD,
		},
	};

#if CONFIG_MQTT_HEALTHCHECK_ENABLED
	mqtt_healthcheck_init();
#endif

#if CONFIG_MQTT_OTA_ENABLED
	mqtt_ota_init();
#endif

	client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    if (esp_mqtt_client_start(client)) {
    	client = NULL;
    	_ESP_LOGE(LOG_MQTT, "Cant start MQTT client!");
    } else {
    	_ESP_LOGI(LOG_MQTT, "MQTT started");
    }

#if CONFIG_MQTT_OTA_ENABLED
	mqtt_ota_on_started();
#endif
}
