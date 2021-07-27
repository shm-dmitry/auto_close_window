#include "rgbled_calibration.h"

#include "../init/nvs_rw.h"

#define RGBLED_NVS_SETTINGS_NAME "rgbled_calb"
#define RGBLED_CALIBRATION_PUBLISH_COLOR \
		*r = vr; \
		*g = vg; \
		*b = vb;
#define RGBLED_CALIBRATION_CALC_MIN_MAX(color, cvalue) \
		if (color != 0x00) {   \
			if (cvalue > max) {\
				max = cvalue;  \
			}                  \
			if (cvalue < min) {\
				min = cvalue;  \
			}                  \
		}
#define RGBLED_CALIBRATION_APPLY(color, cvalue, max) \
		if (color != 0x00) {   \
			color = (uint8_t) (((double)color * (double)cvalue) / (double)max); \
		}


static uint8_t rgbled_calibration_value[3] = { 0xFF, 0xFF, 0xFF };

esp_err_t rgbled_nvs_calibration_load(uint8_t * value) {
	uint8_t * buffer = NULL;
	size_t size = 0;

	esp_err_t res = nvs_read_buffer(RGBLED_NVS_SETTINGS_NAME, &buffer, &size);
	if (res || buffer == NULL || size != 3) {
		value[0] = 0xFF;
		value[1] = 0xFF;
		value[2] = 0xFF;

		return res;
	}

	value[0] = buffer[0];
	value[1] = buffer[1];
	value[2] = buffer[2];

	if (value[0] == 0x00 && value[1] == 0x00 && value[2] == 0x00) {
		value[0] = 0xFF;
		value[1] = 0xFF;
		value[2] = 0xFF;
	}

	free(buffer);

	return ESP_OK;
}

esp_err_t rgbled_nvs_calibration_save(uint8_t * value) {
	if (value == NULL ||
			(value[0] == 0xFF && value[1] == 0xFF && value[2] == 0xFF) ||
			(value[0] == 0x00 && value[1] == 0x00 && value[2] == 0x00)) {
		return nvs_write_buffer(RGBLED_NVS_SETTINGS_NAME, NULL, 0);
	} else {
		return nvs_write_buffer(RGBLED_NVS_SETTINGS_NAME, value, 3);
	}
}

esp_err_t rgbled_calibration_init() {
	return rgbled_nvs_calibration_load(rgbled_calibration_value);
}

esp_err_t rgbled_calibration_calibrate(uint32_t value) {
	uint32_t rgb = value & 0x00FFFFFF;

	uint8_t vr = ((rgb >> 16) & 0xFF);
	uint8_t vg = ((rgb >> 8) & 0xFF);
	uint8_t vb = (rgb & 0xFF);

	if (vr == 0x00 && vg == 0x00 && vb == 0x00) {
		rgbled_calibration_value[0] = 0xFF;
		rgbled_calibration_value[1] = 0xFF;
		rgbled_calibration_value[2] = 0xFF;
	} else {
		rgbled_calibration_value[0] = vr;
		rgbled_calibration_value[1] = vg;
		rgbled_calibration_value[2] = vb;
	}

	return rgbled_nvs_calibration_save(rgbled_calibration_value);
}

void rgbled_calibration_parsecolor(uint32_t rgb, uint8_t * r, uint8_t * g, uint8_t * b) {
	uint8_t vr = ((rgb >> 16) & 0xFF);
	uint8_t vg = ((rgb >> 8) & 0xFF);
	uint8_t vb = (rgb & 0xFF);

	if (vr == 0x00 && vg == 0x00 && vb == 0x00) {
		RGBLED_CALIBRATION_PUBLISH_COLOR;

		return;
	}

	if (rgbled_calibration_value[0] == 0xFF && rgbled_calibration_value[1] == 0xFF && rgbled_calibration_value[2] == 0xFF) {
		RGBLED_CALIBRATION_PUBLISH_COLOR;

		return;
	} else {
		// check is need apply calibration
		uint8_t max = 0x00;
		uint8_t min = 0xFF;

		RGBLED_CALIBRATION_CALC_MIN_MAX(vr, rgbled_calibration_value[0]);
		RGBLED_CALIBRATION_CALC_MIN_MAX(vg, rgbled_calibration_value[1]);
		RGBLED_CALIBRATION_CALC_MIN_MAX(vb, rgbled_calibration_value[2]);

		if (min >= max || max == 0x00) {
			RGBLED_CALIBRATION_PUBLISH_COLOR;

			return;
		} else {
			RGBLED_CALIBRATION_APPLY(vr, rgbled_calibration_value[0], max);
			RGBLED_CALIBRATION_APPLY(vg, rgbled_calibration_value[1], max);
			RGBLED_CALIBRATION_APPLY(vb, rgbled_calibration_value[2], max);

			RGBLED_CALIBRATION_PUBLISH_COLOR;

			return;
		}
	}
}
