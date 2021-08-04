#include "touchpad_api.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/touch_pad.h"
#include "soc/rtc_periph.h"
#include "soc/sens_periph.h"

#include "string.h"

#include "../log.h"

// based on https://github.com/espressif/esp-idf/blob/master/examples/peripherals/touch_pad_interrupt/main/esp32/tp_interrupt_main.c

#define TOUCHPAD_THRESH_NO_USE   (0)
#define TOUCHPAD_FILTER_TOUCH_PERIOD (10)
#define TOUCHPAD_THRESHOLD_CALC(value) (uint16_t) (((value) * 5) / 10.0)
#define TOUCHPAD_LOG_VALUES false
#define TOUCHPAD_FIRE_EVENT(touch_pad_index, last_state_variable, new_state) \
	last_state_variable[touch_pad_index] = new_state; \
	touchpad_callback(touch_pad_index, new_state);

#define TOUCHPAD_ERROR        0xFF

static touch_pad_t * touchpad_pads = NULL;
static uint8_t touchpad_count = 0;
static touchpad_callback_t touchpad_callback = NULL;
static uint16_t * touchpad_threshold = NULL;
static uint32_t * touchpad_calibration_val = NULL;
static uint8_t * touchpad_calibration_cnt = NULL;


static void touchpad_process_autocalibration(uint8_t touchpad_index, uint16_t value, bool untouched) {
	if (untouched) {
		touchpad_calibration_val[touchpad_index] += value;
		touchpad_calibration_cnt[touchpad_index] ++;

		if (touchpad_calibration_cnt[touchpad_index] >= 100) {
			touchpad_threshold[touchpad_index] = TOUCHPAD_THRESHOLD_CALC(touchpad_calibration_val[touchpad_index] / touchpad_calibration_cnt[touchpad_index]);
			touchpad_calibration_val[touchpad_index] = 0;
			touchpad_calibration_cnt[touchpad_index] = 0;

#if TOUCHPAD_LOG_VALUES
			ESP_LOGI(TOUCH_LOG, "Recalibrated %d to %d", touchpad_index, touchpad_threshold[touchpad_index]);
#endif
		}
	} else {
		touchpad_calibration_val[touchpad_index] = 0;
		touchpad_calibration_cnt[touchpad_index] = 0;
	}
}

static uint8_t touchpad_read_value(uint8_t touchpad_index) {
	uint16_t value = 0;
	esp_err_t res = touch_pad_read_filtered(touchpad_pads[touchpad_index], &value);
	if (res) {
#if TOUCHPAD_LOG_VALUES
		ESP_LOGE(TOUCH_LOG, "touchpad_read_value::touch_pad_read_filtered for#%d %d error: %d", touchpad_index, touchpad_pads[touchpad_index], res);
#endif
		return TOUCHPAD_ERROR;
	}

#if TOUCHPAD_LOG_VALUES
	ESP_LOGI(TOUCH_LOG, "touch_pad_read_filtered == %d", value);
#endif

	if (value > touchpad_threshold[touchpad_index]) {
		touchpad_process_autocalibration(touchpad_index, value, true);
		return TOUCHPAD_ON_KEY_UP;
	} else {
		touchpad_process_autocalibration(touchpad_index, value, false);
		return TOUCHPAD_ON_KEY_DOWN;
	}
}

static void touchpad_listener(void* arg) {
	uint8_t * last_touchpad_pressed = malloc(touchpad_count * sizeof(uint8_t));
	memset(last_touchpad_pressed, TOUCHPAD_IDLE, touchpad_count * sizeof(uint8_t));
	for (;;) {
		vTaskDelay(50 / portTICK_PERIOD_MS);

		for (uint8_t i = 0; i<touchpad_count; i++) {
			uint8_t touchpad_pressed = touchpad_read_value(i);
			if (touchpad_pressed == TOUCHPAD_ERROR) {
				continue;
			}

			switch (last_touchpad_pressed[i]) {
			case TOUCHPAD_IDLE: {
				if (touchpad_pressed == TOUCHPAD_ON_KEY_UP) {
					// do nothing, idle mode
				} else {
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_ON_KEY_DOWN);
				}
				break;
			}
			case TOUCHPAD_ON_CLICK: {
				if (touchpad_pressed == TOUCHPAD_ON_KEY_UP) {
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_IDLE);
				} else {
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_IDLE);
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_ON_KEY_DOWN);
				}
				break;
			}
			case TOUCHPAD_ON_KEY_DOWN: {
				if (touchpad_pressed == TOUCHPAD_ON_KEY_UP) {
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_ON_KEY_UP);
				} else {
					// do nothing, key-down mode
				}
				break;
			}
			case TOUCHPAD_ON_KEY_UP: {
				if (touchpad_pressed == TOUCHPAD_ON_KEY_UP) {
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_ON_CLICK);
				} else {
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_ON_CLICK);
					TOUCHPAD_FIRE_EVENT(i, last_touchpad_pressed, TOUCHPAD_ON_KEY_DOWN);
				}
				break;
			}
			default:
				// do nothing
				break;
			}
		}
	}
}

esp_err_t touchpad_setup(touch_pad_t * pad, uint8_t pads_count, touchpad_callback_t callback) {
	touchpad_count = pads_count;

	touchpad_pads = malloc(touchpad_count * sizeof(touch_pad_t));
	memcpy(touchpad_pads, pad, touchpad_count * sizeof(touch_pad_t));

	touchpad_threshold = malloc(touchpad_count * sizeof(uint16_t));
	memset(touchpad_threshold, 0, touchpad_count * sizeof(uint16_t));
	touchpad_calibration_val = malloc(touchpad_count * sizeof(uint32_t));
	memset(touchpad_calibration_val, 0, touchpad_count * sizeof(uint32_t));
	touchpad_calibration_cnt = malloc(touchpad_count * sizeof(uint8_t));
	memset(touchpad_calibration_cnt, 0, touchpad_count * sizeof(uint8_t));

	touchpad_callback = callback;

	esp_err_t res = touch_pad_init();
	if (res) {
		ESP_LOGE(TOUCH_LOG, "touch_pad_init error %d", res);
		return res;
	}

	res = touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
	if (res) {
		ESP_LOGE(TOUCH_LOG, "touch_pad_set_fsm_mode error %d", res);
		return res;
	}

	res = touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
	if (res) {
		ESP_LOGE(TOUCH_LOG, "touch_pad_set_voltage error %d", res);
		return res;
	}

	for (uint8_t i = 0; i<touchpad_count; i++) {
		res = touch_pad_config(touchpad_pads[i], TOUCHPAD_THRESH_NO_USE);
		if (res) {
			ESP_LOGE(TOUCH_LOG, "touch_pad_config for %d error %d", touchpad_pads[i], res);
			return res;
		}
	}

	res = touch_pad_filter_start(TOUCHPAD_FILTER_TOUCH_PERIOD);
	if (res) {
		ESP_LOGE(TOUCH_LOG, "touch_pad_filter_start error %d", res);
		return res;
	}

	for (uint8_t i = 0; i<touchpad_count; i++) {
		uint16_t touch_value = 0;
		res = touch_pad_read_filtered(touchpad_pads[i], &touch_value);
		if (res) {
			ESP_LOGE(TOUCH_LOG, "touch_pad_read_filtered for %d error %d", touchpad_pads[i], res);
			return res;
		}

		ESP_LOGI(TOUCH_LOG, "touch_pad_read_filtered: readed value %d", touch_value);
		touchpad_threshold[i] = TOUCHPAD_THRESHOLD_CALC(touch_value);
	}

	xTaskCreate(touchpad_listener, "on touch pad listener", 2048, NULL, 10, NULL);

	return ESP_OK;
}
