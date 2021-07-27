#include "init.h"

#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "wifi.h"
#include "esp_sntp.h"
#include "nvs_rw.h"

#include "../log.h"

void init_flash() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
}

void init_wifi(const char* ssid, const char* password, const char* topic) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init(ssid, password, topic);
}

void init_snmp() {
    ESP_LOGI(SNMP_LOG, "Start SNTP configuration");

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_setservername(1, "time.google.com");
    sntp_init();

    ESP_LOGI(SNMP_LOG, "snmp initialized");
}
