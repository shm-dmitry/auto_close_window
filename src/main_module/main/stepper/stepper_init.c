#include "stepper_init.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "../log/log.h"
#include "sdkconfig.h"
#include "../common/nvs_rw.h"
#include "stepper_commands.h"
#include "../controller/controller.h"

#define STEPPER_NVS_FULL_OPEN_STEPS "stepper_full_open_steps"
#define STEPPER_DIR_OPEN  1
#define STEPPER_DIR_CLOSE 0
#define STEPPER_DEFAULT_FULL_OPEN_STEPS 10
#define STEPPER_COMMAND_TASK_STACK_SIZE 2048
#define STEPPER_CURRENT_STEPS_UNKNOWN_POSITION 0xFFFFFFFF
#define STEPPER_ONE_STEP_SIZE (stepper_full_open_steps_count / 10)

uint32_t stepper_full_open_steps_count = STEPPER_DEFAULT_FULL_OPEN_STEPS;

uint8_t stepper_next_command = STEPPER_COMMAND_NOCOMMAND;
uint32_t stepper_current_steps = STEPPER_CURRENT_STEPS_UNKNOWN_POSITION;

void stepper_motor_on() {
	if (gpio_get_level(CONFIG_PIN_STEPPER_POWER_ON) == 0) {
		gpio_set_level(CONFIG_PIN_STEPPER_POWER_ON, 1);
		vTaskDelay(10 / portTICK_PERIOD_MS);
		gpio_set_level(CONFIG_PIN_STEPPER_ENABLE, 0);
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void stepper_motor_off() {
	gpio_set_level(CONFIG_PIN_STEPPER_ENABLE, 1);
	gpio_set_level(CONFIG_PIN_STEPPER_POWER_ON, 0);
}

void stepper_do_one_step() {
	gpio_set_level(CONFIG_PIN_STEPPER_STEP, 1);
	vTaskDelay(10 / portTICK_PERIOD_MS);
	gpio_set_level(CONFIG_PIN_STEPPER_STEP, 0);
	vTaskDelay(10 / portTICK_PERIOD_MS);
}

static void stepper_on_execute_command_task(void* arg) {
	uint8_t stepper_current_command = STEPPER_COMMAND_NOCOMMAND;
	uint32_t stepper_step_command_move_to = STEPPER_CURRENT_STEPS_UNKNOWN_POSITION;

	while(true) {
		if (stepper_next_command == STEPPER_COMMAND_NOCOMMAND &&
			stepper_current_command == STEPPER_COMMAND_NOCOMMAND) {
			vTaskDelay(100 / portTICK_PERIOD_MS);
			continue;
		}

		if (stepper_current_steps == STEPPER_CURRENT_STEPS_UNKNOWN_POSITION) {
			controller_on_status(CONTROLLER_STATUS_START_FIND_POSITION);
			stepper_current_command = STEPPER_COMMAND_FULL_CLOSE;
		} else {
			stepper_current_command = stepper_next_command;
			stepper_next_command = STEPPER_COMMAND_NOCOMMAND;

			if (stepper_current_command == STEPPER_COMMAND_STEP_CLOSE ||
				stepper_current_command == STEPPER_COMMAND_FULL_CLOSE) {
				controller_on_status(CONTROLLER_STATUS_START_EXECUTE_CLOSE);
			}

			if (stepper_current_command == STEPPER_COMMAND_STEP_OPEN ||
				stepper_current_command == STEPPER_COMMAND_FULL_OPEN) {
				controller_on_status(CONTROLLER_STATUS_START_EXECUTE_OPEN);
			}

			if (stepper_current_command == STEPPER_COMMAND_STEP_OPEN) {
				uint32_t inc = STEPPER_ONE_STEP_SIZE;
				if (stepper_current_steps + inc > stepper_full_open_steps_count) {
					stepper_step_command_move_to = stepper_full_open_steps_count;
				} else {
					stepper_step_command_move_to = stepper_current_steps + inc;
				}
			} else if (stepper_current_command == STEPPER_COMMAND_STEP_CLOSE) {
				uint32_t inc = STEPPER_ONE_STEP_SIZE;
				if (stepper_current_steps <= inc) {
					stepper_step_command_move_to = 0;
				} else {
					stepper_step_command_move_to = stepper_current_steps - inc;
				}
			}
		}

		stepper_motor_on();

		while(stepper_current_command != STEPPER_COMMAND_NOCOMMAND) {
			if (stepper_current_command != stepper_next_command &&
				stepper_current_steps != STEPPER_CURRENT_STEPS_UNKNOWN_POSITION &&
				stepper_next_command != STEPPER_COMMAND_NOCOMMAND) {

				if (stepper_current_command == STEPPER_COMMAND_CALIBRATE_DO_OPEN &&
					stepper_next_command != STEPPER_COMMAND_CALIBRATE) {
					// end of calibration!
					stepper_current_command = STEPPER_COMMAND_NOCOMMAND;
					stepper_next_command = STEPPER_COMMAND_NOCOMMAND;
					stepper_full_open_steps_count = stepper_current_steps;
					nvs_write_32t(STEPPER_NVS_FULL_OPEN_STEPS, stepper_full_open_steps_count);

					controller_on_status(CONTROLLER_STATUS_END_CALIBRATION);
					break;
				}

				if (stepper_current_command == STEPPER_COMMAND_CALIBRATE_DO_CLOSE &&
					stepper_next_command != STEPPER_COMMAND_CALIBRATE) {
					// something went wrong, stop
					stepper_current_command = STEPPER_COMMAND_NOCOMMAND;
					stepper_next_command = STEPPER_COMMAND_NOCOMMAND;

					controller_on_status(CONTROLLER_STATUS_FAIL_CALIBRATION);
					break;
				}

				if (stepper_current_command == STEPPER_COMMAND_FULL_OPEN  ||
					stepper_current_command == STEPPER_COMMAND_FULL_CLOSE ||
					stepper_current_command == STEPPER_COMMAND_STEP_OPEN  ||
					stepper_current_command == STEPPER_COMMAND_STEP_CLOSE) {
					stepper_current_command = STEPPER_COMMAND_NOCOMMAND;
				}
			}

			switch (stepper_current_command) {
				case STEPPER_COMMAND_FULL_OPEN:
				case STEPPER_COMMAND_STEP_OPEN:
				case STEPPER_COMMAND_CALIBRATE_DO_OPEN:
					gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_OPEN);
					stepper_do_one_step();
					stepper_current_steps++;
					if (stepper_current_command == STEPPER_COMMAND_FULL_OPEN &&
						stepper_current_steps >= stepper_full_open_steps_count) {
						stepper_current_command = STEPPER_COMMAND_NOCOMMAND;

						controller_on_status(CONTROLLER_STATUS_END_EXECUTE_OPEN);
					} else if (stepper_current_command == STEPPER_COMMAND_STEP_OPEN &&
						stepper_current_steps >= stepper_step_command_move_to) {
						stepper_current_command = STEPPER_COMMAND_NOCOMMAND;

						controller_on_status(CONTROLLER_STATUS_END_EXECUTE_OPEN);
					}
					break;
				case STEPPER_COMMAND_FULL_CLOSE:
				case STEPPER_COMMAND_STEP_CLOSE:
				case STEPPER_COMMAND_CALIBRATE_DO_CLOSE:
					gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_CLOSE);
					stepper_do_one_step();
					if (stepper_current_steps != STEPPER_CURRENT_STEPS_UNKNOWN_POSITION) {
						if (stepper_current_steps > 0) {
							stepper_current_steps--;
						}
					}

					if (gpio_get_level(CONFIG_PIN_STEPPER_LIMITSWITCH) == 0) {
						stepper_current_steps = 0;
						if (stepper_current_command == STEPPER_COMMAND_CALIBRATE_DO_CLOSE) {
							stepper_current_command = STEPPER_COMMAND_CALIBRATE;
						} else {
							stepper_current_command = STEPPER_COMMAND_NOCOMMAND;

							controller_on_status(CONTROLLER_STATUS_END_EXECUTE_CLOSE);
						}
					} else if (stepper_current_command == STEPPER_COMMAND_STEP_CLOSE &&
						stepper_current_steps <= stepper_step_command_move_to) {
						stepper_current_command = STEPPER_COMMAND_NOCOMMAND;

						controller_on_status(CONTROLLER_STATUS_END_EXECUTE_CLOSE);
					}
					break;
				case STEPPER_COMMAND_CALIBRATE:
					if (stepper_current_steps != 0) {
						stepper_current_command = STEPPER_COMMAND_CALIBRATE_DO_CLOSE;
					} else {
						stepper_current_command = STEPPER_COMMAND_CALIBRATE_DO_OPEN;

						controller_on_status(CONTROLLER_STATUS_START_CALIBRATION);
					}
					break;
				default:
					break;
			}
		}
	}
}

void stepper_init() {
	ESP_LOGI(LOG_STEPPER, "Initializing output pins...");

	gpio_config_t chargerEnableConfig = {
		.intr_type = GPIO_INTR_DISABLE,
	    .mode = GPIO_MODE_INPUT_OUTPUT,
		.pin_bit_mask = BIT64(CONFIG_PIN_STEPPER_ENABLE) |
		                BIT64(CONFIG_PIN_STEPPER_POWER_ON) |
						BIT64(CONFIG_PIN_STEPPER_DIR) |
						BIT64(CONFIG_PIN_STEPPER_STEP),
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE,
	};

	esp_err_t res = gpio_config(&chargerEnableConfig);
	if (res) {
		ESP_LOGE(LOG_STEPPER, "gpio_config error: %d", res);
		return;
	}

	stepper_motor_off();
	gpio_set_level(CONFIG_PIN_STEPPER_DIR, 0);
	gpio_set_level(CONFIG_PIN_STEPPER_STEP, 0);

	ESP_LOGI(LOG_STEPPER, "Initializing input pin...");

	gpio_config_t limitswConfig = {
		.intr_type = GPIO_INTR_POSEDGE,
		.pin_bit_mask = BIT64(CONFIG_PIN_STEPPER_LIMITSWITCH),
		.mode = GPIO_MODE_INPUT,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE
	};

	res = gpio_config(&limitswConfig);
	if (res) {
		ESP_LOGE(LOG_STEPPER, "gpio_config error: %d", res);
		return;
	}

	ESP_LOGI(LOG_STEPPER, "Reading NVS");

	stepper_full_open_steps_count = nvs_read_32t(STEPPER_NVS_FULL_OPEN_STEPS, STEPPER_DEFAULT_FULL_OPEN_STEPS);
	ESP_LOGI(LOG_STEPPER, "Full-open-steps value : %li", stepper_full_open_steps_count);

	ESP_LOGI(LOG_STEPPER, "Starting jobs....");
	xTaskCreate(stepper_on_execute_command_task, "stepper on execute command task", STEPPER_COMMAND_TASK_STACK_SIZE, NULL, 10, NULL);

	ESP_LOGI(LOG_STEPPER, "Stepper initialied");
}

void stepper_execute_command(uint8_t command) {
	stepper_next_command = command;
}

