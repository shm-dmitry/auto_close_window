#ifndef MAIN_COMMON_DELAY_TIMER_H_
#define MAIN_COMMON_DELAY_TIMER_H_

#include "stdint.h"
#include "stdbool.h"

typedef struct {
	int64_t timeout;
	int64_t started_at;
	bool started;
} t_delay_timer;

t_delay_timer * delay_timer_allocate(uint32_t timeout_msec);
bool delay_timer_start_or_check(t_delay_timer * timerdata);
void delay_timer_stop(t_delay_timer * timerdata);
void delay_timer_release(t_delay_timer ** timerdata);

#endif /* MAIN_COMMON_DELAY_TIMER_H_ */
