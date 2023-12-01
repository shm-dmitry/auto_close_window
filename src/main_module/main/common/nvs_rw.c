#include "nvs_rw.h"

#include "nvs_flash.h"
#include "esp_system.h"
#include "nvs.h"

#include "../log/log.h"

#define STORAGE_NAMESPACE "acw"

void nvs_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

esp_err_t nvs_read_buffer(const char* name, uint8_t** buffer, size_t * buffer_size) {
	nvs_handle_t handle;
	esp_err_t err;

    err = nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK) {
    	ESP_LOGE(LOG_NWS_RW, "Cant open namespace %s for paramter %s: %d", STORAGE_NAMESPACE, name, err);
    	return err;
    }

    *buffer_size = 0;

    err = nvs_get_blob(handle, name, NULL, buffer_size);
    if (err != ESP_OK || *buffer_size == 0) {
    	ESP_LOGE(LOG_NWS_RW, "Cant read blob size for blob %s from NVS: %d", name, err);

    	nvs_close(handle);
    	return err;
    }

    *buffer = (uint8_t *) malloc(*buffer_size);
    if (*buffer == NULL) {
    	ESP_LOGE(LOG_NWS_RW, "Cant allocate %d bytes. OOM.", *buffer_size);

    	nvs_close(handle);
    	return ESP_FAIL;
    }

    err = nvs_get_blob(handle, name, *buffer, buffer_size);
    if (err != ESP_OK) {
    	ESP_LOGE(LOG_NWS_RW, "Cant read blob %s from NVS: %d", name, err);

    	nvs_close(handle);
    	return err;
    }

	nvs_close(handle);
	return ESP_OK;
}

esp_err_t nvs_write_buffer(const char* name, const uint8_t* buffer, size_t buffer_size) {
	nvs_handle_t handle;
	esp_err_t err;

    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
    	ESP_LOGE(LOG_NWS_RW, "Cant open namespace %s for paramter %s: %d", STORAGE_NAMESPACE, name, err);
    	return err;
    }

    err = nvs_erase_key(handle, name);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
    	ESP_LOGE(LOG_NWS_RW, "Cant cleanup memory for %s: %d", name, err);

    	nvs_close(handle);
    	return err;
    }

    err = nvs_commit(handle);
    if (err) {
    	ESP_LOGE(LOG_NWS_RW, "Cant commit cleanup changes for %s: %d", name, err);

    	nvs_close(handle);
    	return err;
    }

    if (buffer == NULL || buffer_size == 0) {
    	nvs_close(handle);
    	return ESP_OK;
    }

    err = nvs_set_blob(handle, name, buffer, buffer_size);
    if (err != ESP_OK) {
    	ESP_LOGE(LOG_NWS_RW, "Cant set blob for %s [%d bytes]: %d", name, buffer_size, err);

    	nvs_close(handle);
    	return err;
    }


    err = nvs_commit(handle);
    if (err) {
    	ESP_LOGE(LOG_NWS_RW, "Cant commit setblob changes for %s [%d bytes]: %d", name, buffer_size, err);

    	nvs_close(handle);
    	return err;
    }

	nvs_close(handle);
	return ESP_OK;
}

uint32_t nvs_read_32t(const char* name, uint32_t default_value) {
	size_t size = sizeof(uint32_t);
	uint8_t * buffer = (uint8_t *)malloc(size);
	if (buffer == NULL) {
		return default_value;
	}

	if (nvs_read_buffer(name, &buffer, &size)) {
		free(buffer);
		return default_value;
	}

	if (size != sizeof(uint32_t)) {
		free(buffer);
		return default_value;
	}

	default_value = 0;
	for (uint8_t i = 0; i<size; i++) {
		default_value = (default_value << 8) + buffer[i];
	}

	free(buffer);

	return default_value;
}

esp_err_t nvs_write_32t(const char* name, uint32_t value) {
	size_t size = sizeof(uint32_t);
	uint8_t * buffer = (uint8_t *)malloc(size);
	if (buffer == NULL) {
		return ESP_ERR_NO_MEM;
	}

	for (int8_t i = size - 1; i>=0; i--) {
		buffer[i] = (value % 0xFF);
		value = value >> 8;
	}

	esp_err_t res = nvs_write_buffer(name, buffer, size);

	free(buffer);

	return res;
}

