# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c init/init_logger.c init/init.c init/mqtt_logger.c init/mqtt.c init/nvs_rw.c init/wifi_nvs.c init/wifi.c cjson/cjson_helper.c cjson/cJSON.c led/led_api.c led/led_control.c servo/servo_control_api.c servo/servo_control_nvs.c servo/servo_control.c controller/controller.c hw_locks/hw_locks_api.c hw_locks/hwlocks_nvs.c outdoor_module/outdoor_module_api.c outdoor_module/outdoor_module.c buttons/botton_api.c")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
