#ifndef MAIN_GPIO_RGBLED_RGBLED_CALIBRATION_H_
#define MAIN_GPIO_RGBLED_RGBLED_CALIBRATION_H_

#include "esp_err.h"

esp_err_t rgbled_calibration_init();

esp_err_t rgbled_calibration_calibrate(uint32_t value);

void rgbled_calibration_parsecolor(uint32_t value, uint8_t * r, uint8_t * g, uint8_t * b);

#endif /* MAIN_GPIO_RGBLED_RGBLED_CALIBRATION_H_ */
