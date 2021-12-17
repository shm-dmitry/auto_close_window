#include "button_api.h"
#include "driver/gpio.h"
#include "../log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static int gpio_button1 = 0;
static int gpio_button2 = 0;
static xQueueHandle button_isr_queue = NULL;
button_callback_t buttons_callback;

static bool button1_was_pressed = false;
static bool button2_was_pressed = false;

#define BUTTON_FIRE_EVENT(state1, state2) { \
	ESP_LOGI(BUTTONS_LOG, "Fire event: %d / %d", (state1), (state2)); \
	buttons_callback((state1), (state2)); \
}

static void IRAM_ATTR button_isr_handler(void* arg) {
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(button_isr_queue, &gpio_num, NULL);
}

static void button_isr_task(void* arg) {
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(button_isr_queue, &io_num, portMAX_DELAY)) {
        	uint8_t state1 = gpio_get_level(gpio_button1) ? BUTTON_ON_KEY_UP : BUTTON_ON_KEY_DOWN;
        	uint8_t state2 = gpio_get_level(gpio_button2) ? BUTTON_ON_KEY_UP : BUTTON_ON_KEY_DOWN;

        	BUTTON_FIRE_EVENT(state1, state2);

			if (state1 == BUTTON_ON_KEY_DOWN) {
				button1_was_pressed = true;
			}

			if (state2 == BUTTON_ON_KEY_DOWN) {
				button2_was_pressed = true;
			}

			if (state1 == BUTTON_ON_KEY_UP && state2 == BUTTON_ON_KEY_UP) {
				BUTTON_FIRE_EVENT(button1_was_pressed ? BUTTON_ON_CLICK : BUTTON_ON_IDLE, button2_was_pressed ? BUTTON_ON_CLICK : BUTTON_ON_IDLE);
				BUTTON_FIRE_EVENT(BUTTON_ON_IDLE, BUTTON_ON_IDLE);

				button1_was_pressed = false;
				button2_was_pressed = false;
			}
        }
    }
}

esp_err_t button_setup(int gpio_button1, int gpio_button2, button_callback_t callback) {
	button_isr_queue = xQueueCreate(10, sizeof(uint32_t));
	buttons_callback = callback;

	gpio_config_t config = {
		.intr_type = GPIO_INTR_ANYEDGE,
	    .mode = GPIO_MODE_INPUT,
		.pin_bit_mask = (1ULL << gpio_button1) | (1ULL << gpio_button2),
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_ENABLE,
	};

	esp_err_t res = gpio_config(&config);
	if (res) {
		ESP_LOGE(BUTTONS_LOG, "Cant init INPUT GPIO. error %d", res);
		return res;
	}

	res = gpio_install_isr_service(0);
	if (res) {
		ESP_LOGE(HWLOCK_LOG, "Cant install isr service. error %d", res);
		return res;
	}

	gpio_isr_handler_add(gpio_button1, button_isr_handler, (void *) gpio_button1);
	gpio_isr_handler_add(gpio_button2, button_isr_handler, (void *) gpio_button2);

	xTaskCreate(button_isr_task, "button_isr_task", 2048, NULL, 10, NULL);

	return ESP_OK;
}
