#ifndef MAIN_SERVO_SERVO_CONTROL_API_H_
#define MAIN_SERVO_SERVO_CONTROL_API_H_

#include "esp_err.h"

esp_err_t servo_control_api_init(int gpio);

esp_err_t servo_control_api_off();

esp_err_t servo_control_api_rotate_to(uint8_t angle);

#endif /* MAIN_SERVO_SERVO_CONTROL_API_H_ */
