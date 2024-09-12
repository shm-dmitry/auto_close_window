#include "stepper_executor.h"

#include "../controller/controller.h"

#include "stepper_one_step.h"
#include "../log/log.h"
#include "../common/delay_timer.h"
#include "../common/nvs_rw.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "math.h"

#define STEPPER_COMMAND_TASK_STACK_SIZE 2048

// exec commmand:
// 0...100 - open to this percent
// > 100 - special codes
#define STEPPER_EXEC_CMD__MAX_MOVETO 100
#define STEPPER_EXEC_CMD__CALIBRATE  150
#define STEPPER_EXEC_CMD__IDLE       200
#define STEPPER_EXEC_CMD__CANCEL     201

#define STEPPER_MOTOR_OFF_DELAY_MILLIS  (60 * 1000)
#define STEPPER_EXEC_CURRENT_POSITION_UNKNOWN  0xFFFFFFFF

#define STEPPER_EXEC_REPORT_POSITION_MILLIS (2 * 1000)

#define STEPPER_EXEC_CORRECT_POSITION_TIMEOUT  1000

#define STEPPER_NVS_FULL_OPEN_STEPS "stp_full_open"
#define STEPPER_DEFAULT_FULL_OPEN_STEPS 1000

volatile uint8_t stepper_exec_command = STEPPER_EXEC_CMD__IDLE;
volatile bool stepper_executor_is_in_error_now = false;

t_endstops * endstops;
t_delay_timer * stepper_exec_stop_timer = NULL;
t_delay_timer * stepper_exec_report_position = NULL;
uint32_t stepper_exec_current_position = STEPPER_EXEC_CURRENT_POSITION_UNKNOWN;
uint32_t stepper_exec_max_position = STEPPER_EXEC_CURRENT_POSITION_UNKNOWN;

static void stepper_executor_on_execute_command_task(void*);

void stepper_executor_do_calibrate(uint8_t);
void stepper_executor_do_locate_position(uint8_t, bool);
void stepper_executor_do_moveto(uint8_t);

void stepper_executor_motor_on() {
	if (gpio_get_level(CONFIG_PIN_STEPPER_POWER_ON) == 0) {
		gpio_set_level(CONFIG_PIN_STEPPER_POWER_ON, 1);
		vTaskDelay(10 / portTICK_PERIOD_MS);
		gpio_set_level(CONFIG_PIN_STEPPER_ENABLE, 0);
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void stepper_executor_motor_off() {
	gpio_set_level(CONFIG_PIN_STEPPER_ENABLE, 1);
	gpio_set_level(CONFIG_PIN_STEPPER_POWER_ON, 0);

	controller_on_stepper_position_updated(0xFF);
}

bool stepper_executor_is_motor_on() {
	return gpio_get_level(CONFIG_PIN_STEPPER_POWER_ON) == 1;
}

void stepper_executor_init(t_endstops * _endstops) {
	endstops = _endstops;

	gpio_config_t chargerEnableConfig = {
		.intr_type = GPIO_INTR_DISABLE,
	    .mode = GPIO_MODE_INPUT_OUTPUT,
		.pin_bit_mask = BIT64(CONFIG_PIN_STEPPER_ENABLE) |
		                BIT64(CONFIG_PIN_STEPPER_POWER_ON),
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE,
	};

	esp_err_t res = gpio_config(&chargerEnableConfig);
	if (res) {
		_ESP_LOGE(LOG_STEPPER_EXEC, "gpio_config error: %d", res);
		return;
	}

	stepper_one_step_init();

	stepper_exec_stop_timer = delay_timer_allocate(STEPPER_MOTOR_OFF_DELAY_MILLIS);
	stepper_exec_report_position = delay_timer_allocate(STEPPER_EXEC_REPORT_POSITION_MILLIS);

	_ESP_LOGI(LOG_STEPPER_EXEC, "Reading NVS");

	stepper_exec_max_position = nvs_read_32t(STEPPER_NVS_FULL_OPEN_STEPS, STEPPER_DEFAULT_FULL_OPEN_STEPS);
	_ESP_LOGI(LOG_STEPPER_EXEC, "Full-open-steps value : %li", stepper_exec_max_position);

	xTaskCreate(stepper_executor_on_execute_command_task, "stepper on execute command task", STEPPER_COMMAND_TASK_STACK_SIZE, NULL, 10, NULL);
}

static void stepper_executor_on_execute_command_task(void*) {
	_ESP_LOGI(LOG_STEPPER_EXEC, "Stepper execution task started");

	while(true) {
		if (stepper_executor_is_in_error_now) {
			if (stepper_exec_command != STEPPER_EXEC_CMD__IDLE) {
				controller_on_status(CONTROLLER_STATUS_ERROR_RAISED);
				stepper_exec_command = STEPPER_EXEC_CMD__IDLE;
			}

			if (stepper_exec_current_position != STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
				stepper_exec_current_position = STEPPER_EXEC_CURRENT_POSITION_UNKNOWN;
			}

			if (stepper_executor_is_motor_on()) {
				stepper_executor_motor_off();
			}

			vTaskDelay(10 / portTICK_PERIOD_MS);
			continue;
		}

		if (stepper_exec_command == STEPPER_EXEC_CMD__IDLE) {
			if (stepper_exec_current_position != STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
				if (stepper_exec_max_position != STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
					if (stepper_exec_current_position == stepper_exec_max_position ||
						stepper_exec_current_position == 0) {
						if (delay_timer_start_or_check(stepper_exec_stop_timer)) {
							stepper_exec_current_position = STEPPER_EXEC_CURRENT_POSITION_UNKNOWN;
							stepper_executor_motor_off();
						}
					}
				}

				if (!endstops->is_stepper_allowed()) {
					stepper_exec_current_position = STEPPER_EXEC_CURRENT_POSITION_UNKNOWN;
					stepper_executor_motor_off();
				}
			}

			vTaskDelay(10 / portTICK_PERIOD_MS);

			continue;
		}

		delay_timer_stop(stepper_exec_stop_timer);

		if (stepper_exec_command == STEPPER_EXEC_CMD__CANCEL) {
			_ESP_LOGW(LOG_STEPPER_EXEC, "Stepper execution cancelled");

			controller_on_status(
					stepper_executor_is_in_error_now ?
							CONTROLLER_STATUS_ERROR_RAISED :
							CONTROLLER_STATUS_TASK_CANCELLED);

			stepper_exec_command = STEPPER_EXEC_CMD__IDLE;

			if (stepper_exec_max_position == STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
				stepper_exec_current_position = STEPPER_EXEC_CURRENT_POSITION_UNKNOWN;
			}

			if (stepper_exec_current_position == STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
				stepper_executor_motor_off();
			}

			continue;
		}

		if (!endstops->is_stepper_allowed()) {
			_ESP_LOGW(LOG_STEPPER_EXEC, "Stepper execution not allowed, check limit switch");

			controller_on_status(CONTROLLER_STATUS_WINDOW_LOCK_OPENED);

			stepper_executor_motor_off();
			stepper_exec_current_position = STEPPER_EXEC_CURRENT_POSITION_UNKNOWN;

			stepper_exec_command = STEPPER_EXEC_CMD__IDLE;

			continue;
		}

		stepper_executor_motor_on();

		uint8_t currentcommand = stepper_exec_command;

		if (currentcommand == STEPPER_EXEC_CMD__CALIBRATE) {
			stepper_executor_do_calibrate(currentcommand);
		} else if (currentcommand <= STEPPER_EXEC_CMD__MAX_MOVETO) {
			stepper_executor_do_moveto(currentcommand);
		}

		if (stepper_exec_command == currentcommand) {
			stepper_exec_command = STEPPER_EXEC_CMD__IDLE;
		}
	}
}

void stepper_executor_calibrate() {
	stepper_executor_is_in_error_now = false; // calibration resets error flag
	stepper_exec_command = STEPPER_EXEC_CMD__CALIBRATE;
}

bool stepper_executor_is_now_executing_move_to(uint8_t percent) {
	if (stepper_executor_is_in_error_now) {
		return false;
	}

	return stepper_exec_command == percent;
}

void stepper_executor_moveto(uint8_t percent) {
	if (!stepper_executor_is_in_error_now) {
		stepper_exec_command = percent;
	} else {
		_ESP_LOGW(LOG_STEPPER_EXEC, "Command 'move to percent %d%%' skipped - we in error now.", percent);
		controller_on_status(CONTROLLER_STATUS_ERROR_RAISED);
	}
}

void stepper_executor_cancel() {
	if (!stepper_executor_is_in_error_now) {
		stepper_exec_command = STEPPER_EXEC_CMD__CANCEL;
	} else {
		_ESP_LOGW(LOG_STEPPER_EXEC, "Command 'cancel movement' skipped - we in error now.");
		controller_on_status(CONTROLLER_STATUS_ERROR_RAISED);
	}
}

void stepper_executor_on_alarm() {
	if (!stepper_executor_is_in_error_now) {
		_ESP_LOGE(LOG_STEPPER_EXEC, "ON NOISE ALARM");

		stepper_executor_motor_off();
		stepper_executor_is_in_error_now = true;
		stepper_exec_command = STEPPER_EXEC_CMD__CANCEL;
	}
}

void stepper_executor_cancel_error() {
	_ESP_LOGI(LOG_STEPPER_EXEC, "NOISE ALARM cancelled");
	stepper_executor_is_in_error_now = false;
	controller_on_status(CONTROLLER_STATUS_ERROR_CANCELLED);
}

bool stepper_executor_is_in_error() {
	return stepper_executor_is_in_error_now;
}


void stepper_executor_do_calibrate(uint8_t currentcommand) {
	controller_on_status(CONTROLLER_STATUS_START_CALIBRATION);

	// 1. close
	stepper_set_close();
	while(!endstops->is_close_fired() && stepper_exec_command == currentcommand) {
		if (!endstops->is_stepper_allowed()) {
			return;
		}
		stepper_do_one_step();
	}

	if (stepper_exec_command != currentcommand) {
		return;
	}

	stepper_exec_current_position = 0;

	// 2. open
	stepper_set_open();
	while(!endstops->is_open_fired() && stepper_exec_command == currentcommand) {
		if (!endstops->is_stepper_allowed()) {
			return;
		}
		stepper_do_one_step();
		stepper_exec_current_position++;
	}

	if (stepper_exec_command != currentcommand) {
		return;
	}

	stepper_exec_max_position = stepper_exec_current_position;
	nvs_write_32t(STEPPER_NVS_FULL_OPEN_STEPS, stepper_exec_max_position);

	controller_on_status(CONTROLLER_STATUS_END_CALIBRATION);
}

void stepper_executor_do_locate_position(uint8_t currentcommand, bool move_to_close) {
	_ESP_LOGI(LOG_STEPPER_EXEC, "Locate position fired for command %d. Moving to %s", currentcommand, (move_to_close ? "CLOSE" : "OPEN"));

	if (stepper_exec_max_position == STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
		stepper_executor_do_calibrate(currentcommand);
	} else if (endstops->is_close_fired()) {
		stepper_exec_current_position = 0;
	} else if (endstops->is_open_fired()) {
		stepper_exec_current_position = stepper_exec_max_position;
	} else if (move_to_close) {
		controller_on_status(CONTROLLER_STATUS_START_FIND_POSITION);

		stepper_set_close();
		while(!endstops->is_close_fired() && stepper_exec_command == currentcommand) {
			if (!endstops->is_stepper_allowed()) {
				return;
			}
			stepper_do_one_step();
		}

		if (stepper_exec_command == currentcommand) {
			stepper_exec_current_position = 0;
		}
	} else {
		controller_on_status(CONTROLLER_STATUS_START_FIND_POSITION);

		stepper_set_open();
		while(!endstops->is_open_fired() && stepper_exec_command == currentcommand) {
			if (!endstops->is_stepper_allowed()) {
				return;
			}
			stepper_do_one_step();
		}

		if (stepper_exec_command == currentcommand) {
			stepper_exec_current_position = stepper_exec_max_position;
		}
	}
}

void stepper_executor_do_moveto(uint8_t currentcommand) {
	_ESP_LOGI(LOG_STEPPER_EXEC, "Execute move-to-position: %d%% [now %ld; max %ld]", currentcommand, stepper_exec_current_position, stepper_exec_max_position);

	if (stepper_exec_max_position == STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
		stepper_executor_do_calibrate(currentcommand);
	} else if (stepper_exec_current_position == STEPPER_EXEC_CURRENT_POSITION_UNKNOWN) {
		stepper_executor_do_locate_position(currentcommand, currentcommand < 50);
	}

	uint32_t newposition = currentcommand * stepper_exec_max_position / 100;
	if (newposition > stepper_exec_max_position) {
		newposition = stepper_exec_max_position;
	}

	if (newposition == stepper_exec_current_position) {
		if ((newposition == 0 && endstops->is_close_fired()) ||
			(newposition == 100 && endstops->is_open_fired()) ||
			(newposition > 0 && newposition < 100)) {
			return;
		}
	}

	int8_t diff = 0;
	if (newposition > stepper_exec_current_position) {
		diff = +1;
		stepper_set_open();
		controller_on_status(CONTROLLER_STATUS_START_EXECUTE_OPEN);
	} else {
		diff = -1;
		stepper_set_close();
		controller_on_status(CONTROLLER_STATUS_START_EXECUTE_CLOSE);
	}

	while(newposition != stepper_exec_current_position) {
		if (stepper_exec_command != currentcommand) {
			return;
		}

		if (!endstops->is_stepper_allowed()) {
			return;
		}

		stepper_do_one_step();

		if ((diff > 0 && stepper_exec_current_position < stepper_exec_max_position) ||
			(diff < 0 && stepper_exec_current_position > 0)) {
			stepper_exec_current_position += diff;
		}

		if (delay_timer_start_or_check(stepper_exec_report_position)) {
			controller_on_stepper_position_updated((stepper_exec_current_position * 100) / stepper_exec_max_position);
		}

		if (stepper_exec_current_position != stepper_exec_max_position &&
				diff > 0 &&
				endstops->is_open_fired()) {
			_ESP_LOGW(LOG_STEPPER_EXEC, "Adjust FULL OPEN POSITION value from %li to %li", stepper_exec_max_position, stepper_exec_current_position);
			// adjust full-open value
			stepper_exec_max_position = stepper_exec_current_position;
			break;
		} else if (stepper_exec_current_position != 0 &&
					diff < 0 &&
					endstops->is_close_fired()) {
			_ESP_LOGW(LOG_STEPPER_EXEC, "Adjust FULL CLOSED POSITION from %li to 0", stepper_exec_current_position);
			// adjust current position to 'closed'
			stepper_exec_current_position = 0;
			break;
		}
	}

	if (stepper_exec_current_position == 0 && !endstops->is_close_fired()) {
		_ESP_LOGI(LOG_STEPPER_EXEC, "Move-to - END OF LOOP, correcting position via CLOSE endstop.");

		t_delay_timer * timer = delay_timer_allocate(STEPPER_EXEC_CORRECT_POSITION_TIMEOUT);

		while(!endstops->is_close_fired()) {
			if (delay_timer_start_or_check(timer)) {
				_ESP_LOGW(LOG_STEPPER_EXEC, "Move-to : after END OF LOOP - move timeout. Stopped.");
				break;
			}

			if (!endstops->is_stepper_allowed()) {
				return;
			}

			if (stepper_exec_command != currentcommand) {
				delay_timer_release(&timer);
				return;
			}

			stepper_do_one_step();
		}

		delay_timer_release(&timer);
	} else if (stepper_exec_current_position == stepper_exec_max_position && !endstops->is_open_fired()) {
		_ESP_LOGI(LOG_STEPPER_EXEC, "Move-to - END OF LOOP, correcting position via OPEN endstop.");

		t_delay_timer * timer = delay_timer_allocate(STEPPER_EXEC_CORRECT_POSITION_TIMEOUT);

		while(!endstops->is_open_fired()) {
			if (delay_timer_start_or_check(timer)) {
				_ESP_LOGW(LOG_STEPPER_EXEC, "Move-to : after END OF LOOP - move timeout. Stopped.");
				break;
			}

			if (stepper_exec_command != currentcommand) {
				delay_timer_release(&timer);
				return;
			}

			if (!endstops->is_stepper_allowed()) {
				return;
			}

			stepper_do_one_step();
			stepper_exec_current_position++;
		}

		delay_timer_release(&timer);

		if (endstops->is_open_fired()) {
			_ESP_LOGW(LOG_STEPPER_EXEC, "Adjust FULL OPEN POSITION value from %li to %li", stepper_exec_max_position, stepper_exec_current_position);
			stepper_exec_max_position = stepper_exec_current_position;
		}
	}

	controller_on_stepper_position_updated(round((stepper_exec_current_position * 100.0) / stepper_exec_max_position));

	controller_on_status(diff > 0 ? CONTROLLER_STATUS_END_EXECUTE_OPEN :
									CONTROLLER_STATUS_END_EXECUTE_CLOSE);
}

