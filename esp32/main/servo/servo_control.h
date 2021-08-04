#ifndef MAIN_SERVO_SERVO_CONTROL_H_
#define MAIN_SERVO_SERVO_CONTROL_H_

#include "esp_err.h"
#include "stdbool.h"

typedef void (* servo_control_calibrate_t)(uint8_t open_angle, uint8_t close_angle);

esp_err_t servo_control_init(int gpio);

esp_err_t servo_control_rotate(uint8_t percent);

esp_err_t servo_control_calibrate_auto(uint8_t initial_angle, servo_control_calibrate_t calibrate_success_callback);

void servo_control_calibrate_manual(uint8_t open_angle, uint8_t close_angle);

bool servo_control_calibrate_onaction();

#endif /* MAIN_SERVO_SERVO_CONTROL_H_ */
