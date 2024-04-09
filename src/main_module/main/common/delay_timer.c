#include "delay_timer.h"

#include "esp_timer.h"
#include "string.h"

t_delay_timer * delay_timer_allocate(uint32_t timeout) {
	t_delay_timer * data = (t_delay_timer *)malloc(sizeof(t_delay_timer));
	if (data == NULL) {
		return NULL;
	}

	memset(data, 0, sizeof(t_delay_timer));

	data->timeout = timeout * 1000;

	return data;
}

bool delay_timer_start_or_check(t_delay_timer * timerdata) {
	if (timerdata == NULL) {
		return false;
	}

	int64_t now = esp_timer_get_time();
	if (!timerdata->started) {
		timerdata->started = true;
		timerdata->started_at = now;
		return false;
	} else {
		if ((now - timerdata->started_at) > timerdata->timeout) {
			timerdata->started = false;
			return true;
		} else {
			return false;
		}
	}
}

void delay_timer_stop(t_delay_timer * timerdata) {
	if (timerdata != NULL && timerdata->started) {
		timerdata->started = false;
	}
}

void delay_timer_release(t_delay_timer ** timerdata) {
	if (timerdata != NULL) {
		if (*timerdata != NULL) {
			free(*timerdata);
			*timerdata = NULL;
		}
	}
}

