#ifndef MAIN_COMMON_MQTT_H_
#define MAIN_COMMON_MQTT_H_

typedef void (* mqtt_topic_callback_t)(const char * topic, const char * data);

void mqtt_start();

void mqtt_subscribe(const char * topic, mqtt_topic_callback_t callback);
void mqtt_publish(const char * topic, const char * message);
void mqtt_publish_sync(const char * topic, const char * message);

#endif /* MAIN_COMMON_MQTT_H_ */
