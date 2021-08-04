#include "servo_control_nvs.h"

#include "../init/nvs_rw.h"

#define SERVO_CONTROL_NVS "servo_ctrl"

void servo_control_nvs_read(uint8_t * open_angle, uint8_t * close_angle) {
	uint8_t * buffer = NULL;
	size_t buffer_size = 0;

	*open_angle = 0;
	*close_angle = 180;

	esp_err_t res = nvs_read_buffer(SERVO_CONTROL_NVS, &buffer, &buffer_size);
	if (res == ESP_OK) {
		if (buffer) {
			if (buffer_size == 2 && buffer[0] < buffer[1]) {
				*open_angle = buffer[0];
				*close_angle = buffer[1];
			}

			free(buffer);
		}
	}
}

void servo_control_nvs_write(uint8_t open_angle, uint8_t close_angle) {
	uint8_t buffer[2] = { open_angle, close_angle };
	nvs_write_buffer(SERVO_CONTROL_NVS, buffer, 2);
}
