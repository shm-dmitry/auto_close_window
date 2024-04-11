#include "mqtt_ota.h"

#include "sdkconfig.h"
#include "mqtt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_crt_bundle.h"
#include "../log/log.h"

#if CONFIG_MQTT_OTA_ENABLED
void mqtt_ota_upgrade(void * arg) {
	esp_http_client_config_t config = {
		.url = arg,
		.crt_bundle_attach = esp_crt_bundle_attach,
		.keep_alive_enable = false,
	};

	_ESP_LOGI(LOG_OTA, "Start OTA upgrade from URL %s", config.url);

	esp_https_ota_config_t ota_config = {
		.http_config = &config,
	};

    esp_err_t ret = esp_https_ota(&ota_config);
    if (ret == ESP_OK) {
        _ESP_LOGI(LOG_OTA, "OTA Succeed, Rebooting...");
        esp_restart();
    } else {
        _ESP_LOGE(LOG_OTA, "Firmware upgrade failed with code %04x", ret);
    }

    vTaskDelete(NULL);
}

void mqtt_ota_commands(const char * topic, const char * data) {
	if (strncmp(data, "https://", 8) == 0) {
		char * url = malloc(strlen(data) + 1);
		if (url != NULL) {
			strcpy(url, data);
			xTaskCreate(mqtt_ota_upgrade, "Perform OTA upgrade", 4096, url, 10, NULL);
		}
	}
}
#endif

void mqtt_ota_init() {
#if CONFIG_MQTT_OTA_ENABLED
	mqtt_subscribe(CONFIG_MQTT_OTA_TOPIC, mqtt_ota_commands);
#endif
}

void mqtt_ota_on_started() {
#if CONFIG_MQTT_OTA_ENABLED
    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_ota_img_states_t ota_state;
    if (esp_ota_get_state_partition(running, &ota_state) == ESP_OK) {
        if (ota_state == ESP_OTA_IMG_PENDING_VERIFY) {
			esp_ota_mark_app_valid_cancel_rollback();
			_ESP_LOGI(LOG_OTA, "OTA upgrade finished");
        }
    }

	esp_app_desc_t running_app_info;
	if (esp_ota_get_partition_description(running, &running_app_info) == ESP_OK) {
		_ESP_LOGI(LOG_OTA, "Running firmware version: %s", running_app_info.version);
		mqtt_publish(CONFIG_MQTT_OTA_VERSION_TOPIC, running_app_info.version);
	}
#endif
}
