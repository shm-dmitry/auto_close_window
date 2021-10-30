#ifndef MAIN_OUTDOOR_MODULE_OUTDOOR_MODULE_DEF_H_
#define MAIN_OUTDOOR_MODULE_OUTDOOR_MODULE_DEF_H_

#include "esp_err.h"

typedef struct outdoor_module_noise_data_t {
	uint16_t * freq;
	uint16_t * vol;
	uint8_t count;
} outdoor_module_noise_data_t;

typedef struct outdoor_module_data_t {
	int8_t temperature;
	uint16_t tvoc;
	outdoor_module_noise_data_t * noise;
} outdoor_module_data_t;

typedef void (* outdoor_module_callback_t)(const outdoor_module_data_t * data);

#endif /* MAIN_OUTDOOR_MODULE_OUTDOOR_MODULE_DEF_H_ */
