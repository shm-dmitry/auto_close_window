#ifndef MAIN_OUTDOOR_MODULE_OUTDOOR_MODULE_API_H_
#define MAIN_OUTDOOR_MODULE_OUTDOOR_MODULE_API_H_

#include "outdoor_module_def.h"

esp_err_t outdoor_module_api_init(int gpio, outdoor_module_callback_t callback);

#endif /* MAIN_OUTDOOR_MODULE_OUTDOOR_MODULE_API_H_ */
