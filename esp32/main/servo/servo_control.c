#include "servo_control.h"

#include "servo_control_api.h"
#include "servo_control_nvs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

typedef struct servo_calibrate_data_t {
	servo_control_calibrate_t success_callback;
	uint8_t onevent;
	uint8_t open_angle;
	uint8_t close_angle;
	uint8_t initial_angle;
} servo_calibrate_data_t;

#define SERVO_CALIBRATE_INVALID_ANGLE 0xFF

static uint8_t servo_control_open_angle = 0;
static uint8_t servo_control_close_angle = 180;
static servo_calibrate_data_t * servo_calibrate_data = NULL;

esp_err_t servo_control_init(int gpio) {
	esp_err_t res = servo_control_api_init(gpio);
	if (res) {
		return res;
	}

	servo_control_nvs_read(&servo_control_open_angle, &servo_control_close_angle);

	return ESP_OK;
}

esp_err_t servo_control_rotate(uint8_t percent) {
	uint8_t angle = (uint8_t) ((float)servo_control_open_angle + (float) (servo_control_close_angle - servo_control_open_angle) * ((float) percent) / 100.0);
	return servo_control_api_rotate_to(angle);
}

static void servo_control_calibration_task(void* arg) {
	for (uint8_t angle = servo_calibrate_data->initial_angle; angle <= 180; angle += 5) {
		servo_control_api_rotate_to(angle);

		for (uint8_t x = 0; x < 20; x++) {
			vTaskDelay(100 / portTICK_PERIOD_MS);

			if (servo_calibrate_data->onevent) {
				servo_calibrate_data->open_angle = angle;
				break;
			}
		}

		if (servo_calibrate_data->onevent) {
			servo_calibrate_data->onevent = 0;
			break;
		}
	}

	if (servo_calibrate_data->open_angle == SERVO_CALIBRATE_INVALID_ANGLE) {
		servo_calibrate_data->open_angle = 180;
	}

	for (uint8_t angle = servo_calibrate_data->initial_angle; angle < servo_calibrate_data->initial_angle; angle -= 5) {
		servo_control_api_rotate_to(angle);

		for (uint8_t x = 0; x < 20; x++) {
			vTaskDelay(100 / portTICK_PERIOD_MS);

			if (servo_calibrate_data->onevent) {
				servo_calibrate_data->close_angle = angle;
				break;
			}
		}

		if (servo_calibrate_data->onevent) {
			servo_calibrate_data->onevent = 0;
			break;
		}
	}

	if (servo_calibrate_data->close_angle == SERVO_CALIBRATE_INVALID_ANGLE) {
		servo_calibrate_data->close_angle = 0;
	}

	servo_control_calibrate_manual(servo_calibrate_data->open_angle, servo_calibrate_data->close_angle);

	servo_calibrate_data->success_callback(servo_calibrate_data->open_angle, servo_calibrate_data->close_angle);

	free(servo_calibrate_data);
	servo_calibrate_data = NULL;

	vTaskDelete(NULL);
}

esp_err_t servo_control_calibrate_auto(uint8_t initial_angle, servo_control_calibrate_t calibrate_success_callback) {
	if (servo_calibrate_data) {
		return ESP_FAIL;
	}

	if (initial_angle >= 180) {
		return ESP_ERR_INVALID_ARG;
	}

	servo_calibrate_data = (servo_calibrate_data_t *) malloc(sizeof(servo_calibrate_data_t));

	servo_calibrate_data->success_callback = calibrate_success_callback;
	servo_calibrate_data->initial_angle = initial_angle;
	servo_calibrate_data->onevent = 0;
	servo_calibrate_data->open_angle = SERVO_CALIBRATE_INVALID_ANGLE;
	servo_calibrate_data->close_angle = SERVO_CALIBRATE_INVALID_ANGLE;

	xTaskCreate(servo_control_calibration_task, "servo_control_calibration_task", 2048, NULL, 10, NULL);

	return ESP_OK;
}

void servo_control_calibrate_manual(uint8_t open_angle, uint8_t close_angle) {
	servo_control_nvs_write(open_angle, close_angle);

	servo_control_open_angle = open_angle;
	servo_control_close_angle = close_angle;
}

void servo_control_calibrate_onaction() {
	if (servo_calibrate_data) {
		servo_calibrate_data->onevent = 1;
	}
}
