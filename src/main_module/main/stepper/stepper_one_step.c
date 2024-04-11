#include "stepper_one_step.h"

#include "../log/log.h"

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "driver/gpio.h"

#define STEPPER_DIR_CLOSE (1)
#define STEPPER_DIR_OPEN  (0)

#define STEPPER_SYGNALS_PER_ONE_STEP  100
#define STEPPER_SYGNAL_FREQUENCY      2000

QueueHandle_t stepper_onestep_end_of_timer_queue;
esp_timer_handle_t stepper_onestep_timer;
uint32_t stepper_onestep_timer_counter;

static void stepper_executor_timer_callback(void*) {
	if (stepper_onestep_timer_counter > 0) {
		gpio_set_level(CONFIG_PIN_STEPPER_STEP, (stepper_onestep_timer_counter % 2));
		stepper_onestep_timer_counter--;

		if (stepper_onestep_timer_counter == 0) {
			uint8_t x;
			xQueueSend(stepper_onestep_end_of_timer_queue, &x, 0);
		}
	}
}

void stepper_one_step_init() {
	gpio_config_t chargerEnableConfig = {
		.intr_type = GPIO_INTR_DISABLE,
	    .mode = GPIO_MODE_INPUT_OUTPUT,
		.pin_bit_mask = BIT64(CONFIG_PIN_STEPPER_DIR) |
						BIT64(CONFIG_PIN_STEPPER_STEP),
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE,
	};

	esp_err_t res = gpio_config(&chargerEnableConfig);
	if (res) {
		_ESP_LOGE(LOG_STEPPER_STEP, "gpio_config error: %d", res);
		return;
	}

	stepper_set_close();

	stepper_onestep_end_of_timer_queue = xQueueCreate(1, sizeof(uint8_t));

    esp_timer_create_args_t stepper_timer_args = {
            .callback = &stepper_executor_timer_callback,
            .name = "stepper-exec-one-step"
    };
    ESP_ERROR_CHECK(esp_timer_create(&stepper_timer_args, &stepper_onestep_timer));
}

void stepper_do_one_step() {
	stepper_onestep_timer_counter = STEPPER_SYGNALS_PER_ONE_STEP;
    ESP_ERROR_CHECK(esp_timer_start_periodic(stepper_onestep_timer, (1000000 / STEPPER_SYGNAL_FREQUENCY / 2)));

    uint8_t x;
	xQueueReceive(stepper_onestep_end_of_timer_queue, &x, portMAX_DELAY);

	esp_timer_stop(stepper_onestep_timer);
}

void stepper_set_open() {
	gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_OPEN);
}

void stepper_set_close() {
	gpio_set_level(CONFIG_PIN_STEPPER_DIR, STEPPER_DIR_CLOSE);
}

