#include "wifi.h"

#include "../log.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event.h"
#include "esp_smartconfig.h"

#include "wifi_nvs.h"
#include "mqtt.h"
#include "../cjson/cJSON.h"

#define WIFI_MAXIMUM_RETRY 30
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define WIFI_DEFAULT_WAIT_CONNECTION (30000 / portTICK_PERIOD_MS)

#define WIFI_CONNECT \
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) ); \
    ESP_ERROR_CHECK(esp_wifi_start() ); \
    \
    bits = xEventGroupWaitBits(s_wifi_event_group, \
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, \
            pdFALSE, \
            pdFALSE, \
			WIFI_DEFAULT_WAIT_CONNECTION); \
    \
    if (bits & WIFI_CONNECTED_BIT) { \
        ESP_LOGI(WIFI_LOG, "connected to ap SSID:%s", wifi_config.sta.ssid); \
    } else if (bits & WIFI_FAIL_BIT) { \
        ESP_LOGE(WIFI_LOG, "Failed to connect to SSID:%s", wifi_config.sta.ssid); \
    } else { \
        ESP_LOGE(WIFI_LOG, "UNEXPECTED EVENT"); \
    } \

static int s_retry_num = 0;

static EventGroupHandle_t s_wifi_event_group;

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < WIFI_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(WIFI_LOG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(WIFI_LOG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(WIFI_LOG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_mqtt_listener(const char * topic, const char * data) {
	cJSON *root = cJSON_Parse(data);
	if (root == NULL) {
		return;
	}

	const char * type = cJSON_GetStringValue(cJSON_GetObjectItem(root, "type"));
	if (strcmp(type, "wifi_reset_ssid") == 0) {
		if (wifi_nvs_set_ssid_password(NULL, NULL)) {
			ESP_LOGI(WIFI_LOG, "WiFi SSID/PASSWORD resetted to default. Restart.");
			esp_restart();
		}
	} else if (strcmp(type, "wifi_set_ssid") == 0) {
		const char* ssid = cJSON_GetStringValue(cJSON_GetObjectItem(root, "ssid"));
		const char* password = cJSON_GetStringValue(cJSON_GetObjectItem(root, "password"));

		if (ssid && password) {
			if (wifi_nvs_set_ssid_password(ssid, password)) {
				ESP_LOGI(WIFI_LOG, "WiFi SSID/PASSWORD Changed to %s:***. Restart", ssid);
				esp_restart();
			}
		}
	}

	cJSON_Delete(root);
}

void wifi_init(const char* ssid, const char* password, const char* topic) {
	esp_netif_create_default_wifi_sta();

    s_wifi_event_group = xEventGroupCreate();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));
    wifi_config_t wifi_config = {
        .sta = {
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
			.pmf_cfg = {
				.capable = true,
				.required = false
			},
        },
    };

	memset(wifi_config.sta.ssid,     0, sizeof(wifi_config.sta.ssid));
	memset(wifi_config.sta.password, 0, sizeof(wifi_config.sta.password));

    wifi_nvs_get_ssid_password(ssid, password,
    							wifi_config.sta.ssid, sizeof(wifi_config.sta.ssid) - 1,
								wifi_config.sta.password, sizeof(wifi_config.sta.password) - 1);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );

    EventBits_t bits = 0;

    WIFI_CONNECT;

    if (!(bits & WIFI_CONNECTED_BIT)) {
    	esp_wifi_stop();

    	memset(wifi_config.sta.ssid,     0, sizeof(wifi_config.sta.ssid));
    	memset(wifi_config.sta.password, 0, sizeof(wifi_config.sta.password));

        strncpy((char*)wifi_config.sta.ssid,     ssid,     sizeof(wifi_config.sta.ssid) - 1);
        strncpy((char*)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);

        WIFI_CONNECT;
    }

    if (!(bits & WIFI_CONNECTED_BIT)) {
    	ESP_LOGE(WIFI_LOG, "Cant connect to WIFI. Restart.");

    	esp_wifi_stop();

    	esp_restart();
    }

    esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip);
    esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id);
    vEventGroupDelete(s_wifi_event_group);

    mqtt_subscribe(topic, wifi_mqtt_listener);

	ESP_LOGI(WIFI_LOG, "WIFI configured");
}
