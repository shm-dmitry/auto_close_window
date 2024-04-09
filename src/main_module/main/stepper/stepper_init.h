#ifndef MAIN_STEPPER_STEPPER_INIT_H_
#define MAIN_STEPPER_STEPPER_INIT_H_

#include "stdint.h"

void stepper_init();

void stepper_calibrate();
void stepper_move_to(uint8_t percent);
void stepper_cancel();

#endif /* MAIN_STEPPER_STEPPER_INIT_H_ */
