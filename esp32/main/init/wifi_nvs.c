#include "wifi_nvs.h"

#include "nvs_rw.h"
#include "string.h"

#define WIFI_NVS_SSID     "wifi_ssid"
#define WIFI_NVS_PASSWORD "wifi_password"

void wifi_nvs_get_ssid_password(const char * default_ssid, const char * default_password,
								uint8_t * store_sid_to, size_t store_sid_to_size,
								uint8_t * store_password_to, size_t store_password_to_size) {
	char* ssid = NULL;
	char* password = NULL;
	size_t ssid_size = 0;
	size_t password_size = 0;

	nvs_read_buffer(WIFI_NVS_SSID, (uint8_t**)&ssid, &ssid_size);
	nvs_read_buffer(WIFI_NVS_PASSWORD, (uint8_t**)&password, &password_size);

	if (ssid && password && (strcmp(ssid, default_ssid) != 0 || strcmp(password, default_password) != 0)) {
		strncpy((char*)store_sid_to,      ssid,     store_sid_to_size);
		strncpy((char*)store_password_to, password, store_password_to_size);
	} else {
		strncpy((char*)store_sid_to,      default_ssid,     store_sid_to_size);
		strncpy((char*)store_password_to, default_password, store_password_to_size);
	}

	if (ssid) {
		free(ssid);
	}

	if (password) {
		free(password);
	}
}

bool wifi_nvs_store(const char * ssid, const char * password) {
	char* current_ssid = NULL;
	char* current_password = NULL;
	size_t current_ssid_size = 0;
	size_t current_password_size = 0;

	nvs_read_buffer(WIFI_NVS_SSID, (uint8_t **)&current_ssid, &current_ssid_size);
	nvs_read_buffer(WIFI_NVS_PASSWORD, (uint8_t **)&current_password, &current_password_size);

	if (current_ssid == NULL && ssid == NULL && current_password == NULL && password == NULL) {
		return false;
	}

	if (current_ssid != NULL && ssid != NULL && strcmp(current_ssid, ssid) == 0 &&
		current_password != NULL && password != NULL && strcmp(current_ssid, password) == 0) {
		return false;
	}

	esp_err_t res = nvs_write_buffer(WIFI_NVS_SSID, (uint8_t *)ssid, ssid == NULL ? 0 :strlen(ssid));
	if (res) {
		return false;
	}
	res = nvs_write_buffer(WIFI_NVS_PASSWORD, (uint8_t *)password, password == NULL ? 0 : strlen(password));
	if (res) {
		return false;
	}

	return true;
}

bool wifi_nvs_set_ssid_password(const char * ssid, const char * password) {
	if (ssid == NULL || password == NULL || strlen(ssid) == 0 || strlen(password) == 0) {
		return wifi_nvs_store(NULL, NULL);
	} else {
		return wifi_nvs_store(ssid, password);
	}
}
