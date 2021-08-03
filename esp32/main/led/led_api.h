#ifndef MAIN_FAN_FAN_API_H_
#define MAIN_FAN_FAN_API_H_

#include "esp_err.h"

esp_err_t led_init(int gpio);

esp_err_t led_on();

esp_err_t led_off();

#endif /* MAIN_FAN_FAN_API_H_ */
