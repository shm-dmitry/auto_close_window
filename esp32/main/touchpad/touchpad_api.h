#ifndef MAIN_GPIO_TOUCHPAD_TOUCHPAD_API_H_
#define MAIN_GPIO_TOUCHPAD_TOUCHPAD_API_H_


#include "esp_err.h"
#include "driver/touch_sensor.h"
#include "touchpad_def.h"

esp_err_t touchpad_setup(touch_pad_t * pad, uint8_t touchpad_count, touchpad_callback_t callback);

#endif /* MAIN_GPIO_TOUCHPAD_TOUCHPAD_API_H_ */
