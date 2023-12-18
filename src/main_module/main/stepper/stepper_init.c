#include "stepper_init.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_attr.h"
#include "../log/log.h"
#include "sdkconfig.h"
#include "../common/nvs_rw.h"
#include "../controller/controller.h"
#include "../controller/controller_mqtt.h"
#include "stepper_commands_def.h"
#include "../charger/charger_init.h"
#include "esp_timer.h"
#include "time.h"
#include "sdkconfig.h"

#define STEPPER_COMMAND_TASK_STACK_SIZE 2048

#define STEPPER_DIR_CLOSE (1)
#define STEPPER_DIR_OPEN  (0)

#define STEPPER_NVS_FULL_OPEN_STEPS "stepper_full_open_steps"
#define STEPPER_DEFAULT_FULL_OPEN_STEPS 1000
#define STEPPER_MOVE_TO_POS_RECHECK_QUEUE_EVERY 10

#define STEPPER_MOTOR_OFF_DELAY_SECS  60

#define STEPPER_SYGNALS_PER_ONE_STEP  100
#define STEPPER_SYGNAL_FREQUENCY      2000

#define STEPPER_ADC_MAXVALUE       4095
#define STEPPER_ADC_VALUE_DELTA    (STEPPER_ADC_MAXVALUE / CONFIG_ADC_STEPPER_DELTA_PC)


#define STEPPER_IS_ALLOWED(x) ((x) >= ((CONFIG_ADC_STEPPER_STEPPER_NOT_ALLOWED_VALUE * STEPPER_ADC_MAXVALUE / 100) + STEPPER_ADC_VALUE_DELTA))
#define STEPPER_IS_OPENED(x)  ((x) >= ((CONFIG_ADC_STEPPER_OPEN_VALUE * STEPPER_ADC_MAXVALUE / 100) - STEPPER_ADC_VALUE_DELTA) && (x) <= ((CONFIG_ADC_STEPPER_OPEN_VALUE * STEPPER_ADC_MAXVALUE / 100) + STEPPER_ADC_VALUE_DELTA))
#define STEPPER_IS_CLOSED(x)  ((x) >= ((CONFIG_ADC_STEPPER_CLOSE_VALUE * STEPPER_ADC_MAXVALUE / 100) - STEPPER_ADC_VALUE_DELTA) && (x) <= ((CONFIG_ADC_STEPPER_CLOSE_VALUE * STEPPER_ADC_MAXVALUE / 100) + STEPPER_ADC_VALUE_DELTA))

#define STEPPER_ENABLE_LIMIT_SWITCH true

typedef struct {
	uint32_t current_position;
	t_stepper_command command;
} t_stepper_context;

adc_oneshot_unit_handle_t adc_limit_sw_handle;

uint32_t stepper_full_open_steps_count = STEPPER_DEFAULT_FULL_OPEN_STEPS;
uint32_t stepper_motor_off_timeout = 0;

QueueHandle_t stepper_commands_queue;

esp_timer_handle_t stepper_timer;
uint32_t stepper_timer_counter;
QueueHandle_t stepper_end_of_timer_queue;

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

static void stepper_timer_callback(void* arg) {
	if (stepper_timer_counter > 0) {
		gpio_set_level(CONFIG_PIN_STEPPER_STEP, (stepper_timer_counter % 2));
		stepper_timer_counter--;

		if (stepper_timer_counter == 0) {
			uint8_t x;
			xQueueSend(stepper_end_of_timer_queue, &x, 0);
		}
	}
}

void stepper_do_one_step() {
	stepper_timer_counter = STEPPER_SYGNALS_PER_ONE_STEP;
    ESP_ERROR_CHECK(esp_timer_start_periodic(stepper_timer, (1000000 / STEPPER_SYGNAL_FREQUENCY / 2)));

    uint8_t x;
	xQueueReceive(stepper_end_of_timer_queue, &x, portMAX_DELAY);

	esp_timer_stop(stepper_timer);
}

bool stepper_is_close_position_reached() {
#if STEPPER_ENABLE_LIMIT_SWITCH
	int value = 0;
	esp_err_t res = adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
	if (res != ESP_OK) {
		return true;
	}

	if (!STEPPER_IS_ALLOWED(value)) {
		return true;
	}

	return STEPPER_IS_CLOSED(value);
#else
	return true;
#endif
}

bool stepper_is_open_position_reached() {
#if STEPPER_ENABLE_LIMIT_SWITCH
	int value = 0;
	esp_err_t res = adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
	if (res != ESP_OK) {
		return true;
	}

	if (!STEPPER_IS_ALLOWED(value)) {
		return true;
	}

	return STEPPER_IS_OPENED(value);
#else
	return true;
#endif
}

bool stepper_is_stepper_allowed() {
#if STEPPER_ENABLE_LIMIT_SWITCH
	int value = 0;
	esp_err_t res = adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
	if (res != ESP_OK) {
		return true;
	}

	return STEPPER_IS_ALLOWED(value);
#else
	return true;
#endif
}

void stepper_on_execute_locateposition(t_stepper_context * context, bool sendnotify) {
	if (sendnotify) {
		controller_on_status(CONTROLLER_STATUS_START_FIND_POSITION);
	}

	if (!stepper_is_close_position_reached()) {
		gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_CLOSE);
		while(!stepper_is_close_position_reached()) {
			stepper_do_one_step();
		}
	}
	context->current_position = 0;
}

void stepper_on_execute_calibrate(t_stepper_context * context) {
	controller_on_status(CONTROLLER_STATUS_START_CALIBRATION);

	// 1. close
	gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_CLOSE);
	while(!stepper_is_close_position_reached()) {
		stepper_do_one_step();
	}

	context->current_position = 0;

	// 2. open
	gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_OPEN);
	while(!stepper_is_open_position_reached()) {
		stepper_do_one_step();
		context->current_position++;
	}

	stepper_full_open_steps_count = context->current_position;
	nvs_write_32t(STEPPER_NVS_FULL_OPEN_STEPS, stepper_full_open_steps_count);

	controller_on_status(CONTROLLER_STATUS_END_CALIBRATION);
}

void stepper_on_execute_move_to_position(t_stepper_context * context) {
	uint32_t newposition = context->command.move_to_percent * stepper_full_open_steps_count / 100;
	if (newposition > stepper_full_open_steps_count) {
		newposition = stepper_full_open_steps_count;
	}

	if (newposition == context->current_position) {
		return;
	}

	int8_t diff = 0;
	if (newposition > context->current_position) {
		diff = +1;
		gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_OPEN);
		controller_on_status(CONTROLLER_STATUS_START_EXECUTE_OPEN);
	} else {
		diff = -1;
		gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_CLOSE);
		controller_on_status(CONTROLLER_STATUS_START_EXECUTE_CLOSE);
	}

	while(newposition != context->current_position) {
		stepper_do_one_step();

		if ((diff > 0 && context->current_position < stepper_full_open_steps_count) ||
			(diff < 0 && context->current_position > 0)) {
			context->current_position += diff;
		}

		if (!stepper_is_stepper_allowed()) {
			return;
		}

		if (diff > 0 && stepper_is_open_position_reached()) {
			// adjust full-open value
			stepper_full_open_steps_count = context->current_position;
			break;
		} else if (diff < 0 && stepper_is_close_position_reached()) {
			// adjust current position to 'closed'
			context->current_position = 0;
			break;
		}

		if ((context->current_position % STEPPER_MOVE_TO_POS_RECHECK_QUEUE_EVERY) == 0) {
			t_stepper_command temp;
			if (xQueueReceive(stepper_commands_queue, &temp, 0) != errQUEUE_EMPTY) {
				if (temp.calibrate == context->command.calibrate &&
					temp.move_to_percent == context->command.move_to_percent) {
					// we allready executing it, lets continue work
					continue;
				} else {
					// stop! cleanup queue and receive last message from it.
					t_stepper_command v;
					while(xQueueReceive(stepper_commands_queue, &v, 0) != errQUEUE_EMPTY) {
						temp.calibrate = v.calibrate;
						temp.move_to_percent = v.move_to_percent;
					}

					// return last message back to queue
					xQueueSend(stepper_commands_queue, &temp, ( TickType_t ) 10);

					controller_on_status(diff > 0 ? CONTROLLER_STATUS_END_EXECUTE_OPEN :
													CONTROLLER_STATUS_END_EXECUTE_CLOSE);

					// and return back to execute it on next loop step
					return;
				}
			}
		}
	}

	if (context->current_position == 0 && !stepper_is_close_position_reached()) {
		stepper_on_execute_locateposition(context, false);
	} else if (context->current_position == stepper_full_open_steps_count && !stepper_is_open_position_reached()) {
		while(!stepper_is_open_position_reached()) {
			stepper_do_one_step();
		}
	}

	controller_on_status(diff > 0 ? CONTROLLER_STATUS_END_EXECUTE_OPEN :
									CONTROLLER_STATUS_END_EXECUTE_CLOSE);
}

static void stepper_on_execute_command_task(void* arg) {
	t_stepper_context context = {
		.current_position = 0xFFFFFFFF,
		.command = {
			.calibrate = false,
			.move_to_percent = 0xFF
		}
	};

	while(true) {
		if (xQueueReceive(stepper_commands_queue, &(context.command), (context.current_position == 0xFFFFFFFF ? portMAX_DELAY : 10)) == errQUEUE_EMPTY) {
			if (context.current_position != 0xFFFFFFFF) {
				if (context.current_position == 0 || context.current_position == stepper_full_open_steps_count) {
					if (stepper_motor_off_timeout == 0) {
						stepper_motor_off_timeout = time(NULL) + STEPPER_MOTOR_OFF_DELAY_SECS;
					} else if (time(NULL) > stepper_motor_off_timeout) {
						stepper_motor_off();
						stepper_motor_off_timeout = 0;
						context.current_position = 0xFFFFFFFF;
					}
				}
			}

			continue;
		}

		if (!stepper_is_stepper_allowed()) {
			stepper_motor_off();
			stepper_motor_off_timeout = 0;
			context.current_position = 0xFFFFFFFF;
			continue;
		}

		stepper_motor_on();

		if (context.current_position == 0xFFFFFFFF) {
			stepper_on_execute_locateposition(&context, true);
		}

		if (context.command.calibrate) {
			stepper_on_execute_calibrate(&context);
		} else if (context.command.move_to_percent <= 100) {
			stepper_on_execute_move_to_position(&context);
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
	gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_CLOSE);

	ESP_LOGI(LOG_STEPPER, "Init timer");

    esp_timer_create_args_t stepper_timer_args = {
            .callback = &stepper_timer_callback,
            .name = "stepper-timer"
    };
    ESP_ERROR_CHECK(esp_timer_create(&stepper_timer_args, &stepper_timer));

    stepper_end_of_timer_queue = xQueueCreate(1, sizeof(uint8_t));

	ESP_LOGI(LOG_STEPPER, "Initializing limit switch channel...");

    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc_limit_sw_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &config));

#if CONFIG_ADC_STEPPER_CALIBRATION_MODE
    while(true) {
    	int value = 0;
    	adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
    	ESP_LOGI(LOG_STEPPER, "Value: %d / %d%%", value, ((value * 100) / 4095));

    	if (!stepper_is_stepper_allowed()) {
    		ESP_LOGI(LOG_STEPPER, "Stepper disabled!");
    	} else if (stepper_is_close_position_reached()) {
    		ESP_LOGI(LOG_STEPPER, "CLose position reached!");
    	} else if (stepper_is_open_position_reached()) {
    		ESP_LOGI(LOG_STEPPER, "Open position reached!");
    	}

    	vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
#endif

	ESP_LOGI(LOG_STEPPER, "Reading NVS");

	stepper_full_open_steps_count = nvs_read_32t(STEPPER_NVS_FULL_OPEN_STEPS, STEPPER_DEFAULT_FULL_OPEN_STEPS);
	ESP_LOGI(LOG_STEPPER, "Full-open-steps value : %li", stepper_full_open_steps_count);

	ESP_LOGI(LOG_STEPPER, "Starting jobs....");
	stepper_commands_queue = xQueueCreate(10, sizeof(t_stepper_command));
	xTaskCreate(stepper_on_execute_command_task, "stepper on execute command task", STEPPER_COMMAND_TASK_STACK_SIZE, NULL, 10, NULL);

	ESP_LOGI(LOG_STEPPER, "Stepper initialied");
}

void stepper_calibrate() {
	t_stepper_command cmd = {
		.calibrate = true,
		.move_to_percent = 0xFF
	};

	if (xQueueSend(stepper_commands_queue, &cmd, ( TickType_t ) 10) == errQUEUE_FULL) {
		ESP_LOGE(LOG_STEPPER, "Command queue full; calibrate skipped");
	}
}

void stepper_move_to(uint8_t percent) {
	t_stepper_command cmd = {
		.calibrate = false,
		.move_to_percent = ((percent > 100) ? 100 : percent)
	};

	if (xQueueSend(stepper_commands_queue, &cmd, ( TickType_t ) 10) == errQUEUE_FULL) {
		ESP_LOGE(LOG_STEPPER, "Command queue full; move-to %d%% skipped", percent);
	}
}
