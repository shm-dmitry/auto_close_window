#ifndef MAIN_STEPPER_STEPPER_EXECUTOR_H_
#define MAIN_STEPPER_STEPPER_EXECUTOR_H_

#include "stdint.h"
#include "stdbool.h"

typedef bool (*t_is_endstop_fired)();

typedef struct {
	t_is_endstop_fired is_stepper_allowed;
	t_is_endstop_fired is_close_fired;
	t_is_endstop_fired is_open_fired;
} t_endstops;

void stepper_executor_init(t_endstops * endstops);

void stepper_executor_calibrate();
void stepper_executor_moveto(uint8_t percent);
bool stepper_executor_is_now_executing_move_to(uint8_t percent);
void stepper_executor_cancel();
void stepper_executor_on_alarm();
void stepper_executor_cancel_error();
bool stepper_executor_is_in_error();

#endif /* MAIN_STEPPER_STEPPER_EXECUTOR_H_ */
