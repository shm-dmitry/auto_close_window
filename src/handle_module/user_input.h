#ifndef USER_INPUT_H_
#define USER_INPUT_H_

#define USER_INPUT__NOEVENT             0
#define USER_INPUT__OPEN                1
#define USER_INPUT__CLOSE               2
#define USER_INPUT__PREPARE_CALIBRATE   3
#define USER_INPUT__CALIBRATE           4

#include "stdint.h"

void user_input_init();
uint8_t user_input_get_event();

#endif /* #define USER_INPUT_H_ */
