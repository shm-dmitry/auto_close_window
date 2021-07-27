#ifndef MAIN_INIT_NVS_RW_H_
#define MAIN_INIT_NVS_RW_H_

#include "esp_err.h"
#include "stdint.h"

esp_err_t nvs_read_buffer(const char* name, uint8_t** buffer, size_t * buffer_size);
esp_err_t nvs_write_buffer(const char* name, const uint8_t* buffer, size_t buffer_size);

#endif /* MAIN_INIT_NVS_RW_H_ */
