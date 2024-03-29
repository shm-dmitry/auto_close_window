#ifndef MAIN_CONTROLLER_CONTROLLER_MQTT_H_
#define MAIN_CONTROLLER_CONTROLLER_MQTT_H_

#include "stdint.h"
#include "stdbool.h"

void controller_mqtt_init();

void controller_mqtt_process_om_air_data(int8_t temperature, uint8_t humidity, uint32_t pressure);
void controller_mqtt_process_om_noise_alarm(bool alarm);
void controller_mqtt_process_om_noise_data(uint8_t freq1, uint8_t level1, uint8_t freq2, uint8_t level2, uint8_t freq3, uint8_t level3, uint8_t freq4, uint8_t level4, uint8_t freq5, uint8_t level5);
void controller_mqtt_on_stepper_current_open(uint8_t percent);

#endif /* MAIN_CONTROLLER_CONTROLLER_MQTT_H_ */
