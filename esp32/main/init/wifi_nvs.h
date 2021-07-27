#ifndef MAIN_INIT_WIFI_NVS_H_
#define MAIN_INIT_WIFI_NVS_H_

#include "stdbool.h"
#include "strings.h"
#include "esp_err.h"

#define WIFI_NVS_FAILS_UNEXPECTED 0xF0

void wifi_nvs_get_ssid_password(const char * default_ssid, const char * default_password,
								uint8_t * store_sid_to, size_t store_sid_to_size,
								uint8_t * store_password_to, size_t store_password_to_size);

bool wifi_nvs_set_ssid_password(const char * ssid, const char * password);

#endif /* MAIN_INIT_WIFI_NVS_H_ */
