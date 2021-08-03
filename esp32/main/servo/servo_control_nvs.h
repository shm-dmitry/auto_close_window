#ifndef MAIN_SERVO_SERVO_CONTROL_NVS_H_
#define MAIN_SERVO_SERVO_CONTROL_NVS_H_

#include "stdint.h"

void servo_control_nvs_read(uint8_t * open_angle, uint8_t * close_angle);

void servo_control_nvs_write(uint8_t open_angle, uint8_t close_angle);

#endif /* MAIN_SERVO_SERVO_CONTROL_NVS_H_ */
