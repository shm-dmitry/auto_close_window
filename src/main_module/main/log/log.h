#ifndef MAIN_LOG_LOG_H_
#define MAIN_LOG_LOG_H_

#include "esp_log.h"

#define LOG_SHOW_DEBUG_MESSAGES  false

#if LOG_SHOW_DEBUG_MESSAGES
#define _ESP_LOGI(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
#define _ESP_LOGW(tag, format, ...) ESP_LOGW(tag, format, ##__VA_ARGS__)
#define _ESP_LOGE(tag, format, ...) ESP_LOGE(tag, format, ##__VA_ARGS__)
#else
#define _ESP_LOGI(tag, format, ...)
#define _ESP_LOGW(tag, format, ...)
#define _ESP_LOGE(tag, format, ...)
#endif

#define LOG_OTA          "ota"
#define LOG_CHARGER      "charger"
#define LOG_STEPPER      "stepper"
#define LOG_STEPPER_EXEC "stepper_exec"
#define LOG_STEPPER_STEP "stepper_step"
#define LOG_NWS_RW       "nws_rw"
#define LOG_FM_SENDER    "fm_sender"
#define LOG_FM_RECEIVER  "fm_receiver"
#define LOG_CONTROLLER   "controller"
#define LOG_FM_ENCODER   "fm_encoder"
#define LOG_ENCRYPTOR    "encryptor"
#define LOG_WIFI         "wifi"
#define LOG_MQTT		 "mqtt"
#define LOG_MAIN		 "main"

#endif /* MAIN_LOG_LOG_H_ */
