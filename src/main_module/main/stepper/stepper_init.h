#ifndef MAIN_STEPPER_STEPPER_INIT_H_
#define MAIN_STEPPER_STEPPER_INIT_H_

#include "stdint.h"
#include "stdbool.h"

void stepper_init();

void stepper_calibrate();
void stepper_move_to(uint8_t percent);
bool stepper_is_now_executing_move_to(uint8_t percent);
void stepper_cancel();
void stepper_cancel_error();
void stepper_noise_alarm_enable(bool enable);
void stepper_limit_switch_enable(bool enable);
void stepper_allow_unlock_on_endpos(bool value);
void stepper_publish_status();

#endif /* MAIN_STEPPER_STEPPER_INIT_H_ */
