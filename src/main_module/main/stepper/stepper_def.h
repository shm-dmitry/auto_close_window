#ifndef MAIN_STEPPER_STEPPER_DEF_H_
#define MAIN_STEPPER_STEPPER_DEF_H_

#include "stdbool.h"

typedef bool (*t_is_endstop_fired)();

typedef struct {
	t_is_endstop_fired is_stepper_allowed;
	t_is_endstop_fired is_close_fired;
	t_is_endstop_fired is_open_fired;
} t_endstops;

#endif /* MAIN_STEPPER_STEPPER_DEF_H_ */
