#ifndef LED_H_
#define LED_H_

#include "stdint.h"

#define LED_NO_COMMAND          0xFF

#define LED_START_OPEN          0x00
#define LED_END_OPEN            0x05
#define LED_START_CLOSE         0x01
#define LED_END_CLOSE           0x05
#define LED_PREENTER_CALLIBRATE 0x03
#define LED_CALIBRATE           0x02
#define LED_END_CALIBRATE       0x04
#define LED_FAIL_CALIBRATE      LED_NO_COMMAND
#define LED_START_FIND_POS      0x06

void led_init();
void led_on_main_loop();

void led_run_inform(uint8_t type);

#endif /* #define LED_H_ */
