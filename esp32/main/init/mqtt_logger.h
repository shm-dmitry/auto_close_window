#ifndef MAIN_INIT_MQTT_LOGGER_H_
#define MAIN_INIT_MQTT_LOGGER_H_

#include "stddef.h"
#include "stdint.h"

typedef struct mqtt_logger_data_t {
	char ** messages;
	size_t messages_count;
	char * logname;
} mqtt_logger_data_t;

void mqtt_logger_start();

mqtt_logger_data_t * mqtt_logger_init(const char * logname);

void mqtt_logger_append(mqtt_logger_data_t * data, const char * message, ...);

void mqtt_logger_append_hexdump(mqtt_logger_data_t * data, const uint8_t *buffer, uint16_t buff_len);

void mqtt_logger_done(mqtt_logger_data_t ** data);

#define MQTT_LOG_INIT(tag) \
	mqtt_logger_data_t * __mqtt_logger_data = mqtt_logger_init(tag);

#define MQTT_LOGI(tag, data, ...) \
	if (__mqtt_logger_data) { \
		mqtt_logger_append(__mqtt_logger_data, data, ##__VA_ARGS__); \
	} else { \
		ESP_LOGI(tag, data, ##__VA_ARGS__); \
	}

#define MQTT_LOGE(tag, data, ...) \
	if (__mqtt_logger_data) { \
		mqtt_logger_append(__mqtt_logger_data, data, ##__VA_ARGS__); \
	} else { \
		ESP_LOGE(tag, data, ##__VA_ARGS__); \
	}

#define MQTT_LOG_BUFFER_HEXDUMP( tag, buffer, buff_len, level ) \
	if (__mqtt_logger_data) { \
		mqtt_logger_append_hexdump(__mqtt_logger_data, buffer, buff_len); \
	} else { \
		ESP_LOG_BUFFER_HEXDUMP(tag, buffer, buff_len, level); \
	}

#define MQTT_LOG_DONE \
	if (__mqtt_logger_data) { \
		mqtt_logger_done(&__mqtt_logger_data); \
	}

#endif /* MAIN_INIT_MQTT_LOGGER_H_ */
