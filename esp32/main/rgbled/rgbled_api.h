#ifndef MAIN_RGBLED_RGBLED_API_H_
#define MAIN_RGBLED_RGBLED_API_H_

#include "rgbled_def.h"
#include "stdint.h"
#include "esp_err.h"

esp_err_t rgbled_init(const rgbled_config_t * config);

esp_err_t rgbled_calibrate(uint32_t value);
esp_err_t rgbled_set_color(uint32_t rgb);
esp_err_t rgbled_set_override_color(uint32_t rgb);
esp_err_t rgbled_reset_override_color();

#endif /* MAIN_RGBLED_RGBLED_API_H_ */
