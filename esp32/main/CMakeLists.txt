# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c init/init_logger.c init/init.c init/mqtt_logger.c init/mqtt.c init/nvs_rw.c init/wifi_nvs.c init/wifi.c cjson/cjson_helper.c cjson/cJSON.c rgbled/rgbled_api.c rgbled/rgbled_calibration.c rgbled/rgbled.c servo/servo_control_api.c servo/servo.c")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
