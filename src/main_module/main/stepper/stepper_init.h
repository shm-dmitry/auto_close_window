#ifndef MAIN_STEPPER_STEPPER_INIT_H_
#define MAIN_STEPPER_STEPPER_INIT_H_

#include "stdint.h"

void stepper_init();
void stepper_execute_command(uint8_t command);

#endif /* MAIN_STEPPER_STEPPER_INIT_H_ */
