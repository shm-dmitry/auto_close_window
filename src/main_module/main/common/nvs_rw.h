#ifndef MAIN_COMMON_NVS_RW_H_
#define MAIN_COMMON_NVS_RW_H_

#include "esp_err.h"
#include "stdint.h"

esp_err_t nvs_read_buffer(const char* name, uint8_t** buffer, size_t * buffer_size);
esp_err_t nvs_write_buffer(const char* name, const uint8_t* buffer, size_t buffer_size);

uint32_t nvs_read_32t(const char* name, uint32_t default_value);
esp_err_t nvs_write_32t(const char* name, uint32_t value);

#endif /* MAIN_COMMON_NVS_RW_H_ */
