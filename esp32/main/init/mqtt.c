#include "mqtt.h"

#include "mqtt_client.h"
#include "nvs_rw.h"

#include "../log.h"

#define MAX_MQTT_URI_LEN 100
#define MAX_MQTT_USER_PASS 20

typedef struct mqtt_callback_mapping_t {
	char * topic;
	mqtt_topic_callback_t function;
} mqtt_callback_mapping_t;

mqtt_callback_mapping_t* callbacks = NULL;
uint8_t callbacks_count = 0;
esp_mqtt_client_handle_t client;

static void mqtt_event_handler_cb(esp_mqtt_event_handle_t event) {
	if (callbacks_count == 0 || event == NULL) {
		return;
	}

	switch (event->event_id) {
	case MQTT_EVENT_CONNECTED:
		for (int i = 0; i<callbacks_count; i++) {
			esp_mqtt_client_subscribe(event->client, callbacks[i].topic, 0);
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

			ESP_LOGI(MQTT_LOG, "Received message in topic %s : %s", topic, data);

			for (int i = 0; i<callbacks_count; i++) {
				if (strcmp(topic, callbacks[i].topic) == 0) {
					callbacks[i].function(topic, data);
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

void mqtt_publish_sync(const char * topic, const char * message) {
	if (client) {
		if (esp_mqtt_client_publish(client, topic, message, 0, 0, 1) >= 0) {
	    	ESP_LOGI(MQTT_LOG, "MQTT publish OK topic = %s, message = %s", topic, message);
		} else {
			mqtt_publish(topic, message);
		}
	}
}

void mqtt_publish(const char * topic, const char * message) {
	if (client) {
		if (esp_mqtt_client_enqueue(client, topic, message, 0, 0, 1, 1) >= 0) {
	    	ESP_LOGI(MQTT_LOG, "MQTT enqueue OK topic = %s, message = %s", topic, message);
		} else {
	    	ESP_LOGE(MQTT_LOG, "MQTT enqueue error: topic = %s, message = %s", topic, message);
		}
	}
}

void mqtt_subscribe(const char * topic, mqtt_topic_callback_t callback) {
	if (callback == NULL) {
		ESP_LOGW(MQTT_LOG, "Cant subscribe for a topic %s. Callback is NULL.", topic);
		return;
	}

	mqtt_callback_mapping_t* newtable = (mqtt_callback_mapping_t*) malloc(sizeof(mqtt_callback_mapping_t) * (callbacks_count + 1));
	memset(newtable, 0, sizeof(mqtt_callback_mapping_t) * (callbacks_count + 1));

	if (callbacks_count > 0) {
		memcpy(newtable, callbacks, sizeof(mqtt_callback_mapping_t) * callbacks_count);
		free(callbacks);
		callbacks = NULL;
	}

	callbacks = newtable;

	callbacks[callbacks_count].topic = (char *) malloc(strlen(topic) + 1);
	memset(callbacks[callbacks_count].topic, 0, strlen(topic) + 1);
	strcpy(callbacks[callbacks_count].topic, topic);

	callbacks[callbacks_count].function = callback;

	callbacks_count++;

	ESP_LOGI(MQTT_LOG, "Client subscribed on topic %s", topic);
}

void mqtt_start() {
	esp_mqtt_client_config_t mqtt_cfg = {
		.uri = CONFIG_MQTT_BROKER_URI,
		.username = CONFIG_MQTT_BROKER_USERNAME,
		.password = CONFIG_MQTT_BROKER_PASSWORD,
	};

	client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    if (esp_mqtt_client_start(client)) {
    	client = NULL;
    	ESP_LOGE(MQTT_LOG, "Cant start MQTT client!");
    } else {
    	ESP_LOGI(MQTT_LOG, "MQTT started");
    }
}
