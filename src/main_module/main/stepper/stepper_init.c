#include "stepper_init.h"

#include "stepper_adc.h"

#include "stepper_executor.h"

#include "esp_attr.h"
#include "../log/log.h"
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"

#include "string.h"

#define STEPPER_COMMAND_TASK_STACK_SIZE 4096

#define STEPPER_ENABLE_NOISE_ALARM  		true
#define STEPPER_ENABLE_NOISE_AUTO_DEALARM	true

#define STEPPER_NOISE_ALARM_DEGLICH   		2
#define STEPPER_NOISE_AUTO_DEALARM_DEGLICH	(60*1000/10)

#if STEPPER_ENABLE_NOISE_ALARM
static void stepper_noise_alarm_task(void*);
#endif

void stepper_init() {
	_ESP_LOGI(LOG_STEPPER, "Initializing ADC channels...");

	t_endstops * endstops = stepper_adc_init();

	_ESP_LOGI(LOG_STEPPER, "Initializing stepper executor controller");

    stepper_executor_init(endstops);

#if STEPPER_ENABLE_NOISE_ALARM
	_ESP_LOGI(LOG_STEPPER, "Starting check noise alarm thread");

	xTaskCreate(stepper_noise_alarm_task, "noise alarm task", STEPPER_COMMAND_TASK_STACK_SIZE, NULL, 10, NULL);
#endif

	_ESP_LOGI(LOG_STEPPER, "Stepper initialied");
}

#if STEPPER_ENABLE_NOISE_ALARM
static void stepper_noise_alarm_task(void*) {
	uint8_t deglichON = 0;
#if STEPPER_ENABLE_NOISE_AUTO_DEALARM
	uint16_t deglichOFF = 0;
#endif

	while(true) {
		if (stepper_adc_is_noise_alarm_fired()) {
			if (deglichON >= STEPPER_NOISE_ALARM_DEGLICH) {
				stepper_executor_on_alarm();
			} else {
				deglichON++;
			}
		} else {
			deglichON = 0;
#if STEPPER_ENABLE_NOISE_AUTO_DEALARM
			if (stepper_executor_is_in_error()) {
				if (deglichOFF >= STEPPER_NOISE_AUTO_DEALARM_DEGLICH) {
					stepper_executor_cancel_error();
				} else {
					deglichOFF++;
				}
			} else {
				deglichOFF = 0;
			}
#endif
		}

    	vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
#endif

void stepper_calibrate() {
	stepper_executor_calibrate();
}

void stepper_cancel_error() {
	stepper_executor_cancel_error();
}

bool stepper_is_now_executing_move_to(uint8_t percent) {
	if (percent > 100) {
		return false;
	}

	return stepper_executor_is_now_executing_move_to(percent);
}

void stepper_move_to(uint8_t percent) {
	if (percent > 100) {
		percent = 100;
	}

	stepper_executor_moveto(percent);
}

void stepper_cancel() {
	stepper_executor_cancel();
}
