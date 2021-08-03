#ifndef MAIN_LED_LED_CONTROL_H_
#define MAIN_LED_LED_CONTROL_H_

#define LED_CONTROL_ON_OFF  0x01
#define LED_CONTROL_BLINK   0x02
#define LED_CONTROL_BLINK_2 0x03
#define LED_CONTROL_BLINK_3 0x04

#include "esp_err.h"

esp_err_t led_control_init(int gpio);

void led_control_submit(uint8_t code);

#endif /* MAIN_LED_LED_CONTROL_H_ */
