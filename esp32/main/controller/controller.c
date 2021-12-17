#include "controller.h"

#include "../led/led_control.h"
#include "../buttons/button_api.h"
#include "../servo/servo_control.h"
#include "../hw_locks/hw_locks_api.h"
#include "../init/mqtt.h"
#include "../cjson/cjson_helper.h"
#include "string.h"
#include "../log.h"

#include "sdkconfig.h"

#define TOCHPAD_INDEX_OPEN 0
#define TOCHPAD_INDEX_CLOSE 1
#define TOCHPAD_INDEX_AUTO 2

void controller_exec_open_close(uint8_t, bool);
void controller_exec_auto();
void controller_exec_calibrate_auto(uint8_t);
void controller_exec_calibrate_manual(uint8_t, uint8_t);

void controller_button_callback(uint8_t button1_state, uint8_t button2_state) {
	if (button1_state == BUTTON_ON_KEY_DOWN || button2_state == BUTTON_ON_KEY_DOWN) {
		if (servo_control_calibrate_onaction()) {
			return;
		}
	}

	if (button1_state == BUTTON_ON_CLICK && button2_state == BUTTON_ON_CLICK) {
		controller_exec_auto();
	} else if (button1_state == BUTTON_ON_CLICK) {
		controller_exec_open_close(100, true);
	} else if (button2_state == BUTTON_ON_CLICK) {
		controller_exec_open_close(0, true);
	}
}

void controller_command(const char * topic, const char * data)  {
	cJSON *root = cJSON_Parse(data);
	if (root == NULL) {
		return;
	}

	char * type = cJSON_GetStringValue(cJSON_GetObjectItem(root, "type"));
	if (strcmp(type, "open") == 0) {
		controller_exec_open_close(get_number8_from_json(cJSON_GetObjectItem(root, "percent"), 100), false);
	} else if (strcmp(type, "close") == 0) {
		controller_exec_open_close(0, false);
	} else if (strcmp(type, "calibrate_auto") == 0) {
		controller_exec_calibrate_auto(get_number8_from_json(cJSON_GetObjectItem(root, "init_angle"), 90));
	} else if (strcmp(type, "calibrate_manual") == 0) {
		controller_exec_calibrate_manual(get_number8_from_json(cJSON_GetObjectItem(root, "open_angle"), 180), get_number8_from_json(cJSON_GetObjectItem(root, "close_angle"), 0));
	}

	cJSON_Delete(root);
}

void controller_init() {
	// init led driver
	if (led_control_init(CONFIG_LED_GPIO)) {
		ESP_LOGE(CONTROLLER_LOG, "Cant init LED driver");
		return;
	}

	// init buttons
	if (button_setup(CONFIG_BUTTON_OPEN, CONFIG_BUTTON_CLOSE, controller_button_callback)) {
		ESP_LOGE(CONTROLLER_LOG, "Cant init buttons driver");
		return;
	}

	// init servo
	if (servo_control_init(CONFIG_CONTROLLER_SERVO_GPIO)) {
		ESP_LOGE(CONTROLLER_LOG, "Cant init servo driver");
		return;
	}

	if (hwlocks_init(CONFIG_HWLOCK_GPIO_HALL, CONFIG_HWLOCK_GPIO_SWITCH, CONFIG_HWLOCK_GPIO_SOFTLOCK, CONFIG_HWLOCK_SOFTLOCK_TOPIC, CONFIG_HWLOCK_STATUS_TOPIC)) {
		ESP_LOGE(CONTROLLER_LOG, "Cant init hwlocks driver");
		return;
	}

	mqtt_subscribe(CONFIG_CONTROLLER_COMMAND_TOPIC, controller_command);

	ESP_LOGI(CONTROLLER_LOG, "Controller initialized");
}

bool controller_check_locks() {
	uint8_t value = hwlocks_read();
	if (value == HWLOCK_STATE_OK) {
		return false;
	}

	if (value & HWLOCK_STATE_HALL) {
		led_control_submit(LED_CONTROL_ON_OFF);
	} else if (value & HWLOCK_STATE_SWITCH) {
		led_control_submit(LED_CONTROL_BLINK);
	} else if (value & HWLOCK_STATE_SOFTLOCK) {
		led_control_submit(LED_CONTROL_BLINK_2);
	}

	return true;
}

void controller_exec_open_close(uint8_t percent, bool postmessage) {
	if (controller_check_locks()) {
		return;
	}

	servo_control_rotate(percent);

	if (postmessage) {
		cJSON *root = cJSON_CreateObject();
		if (percent == 0) {
			cJSON_AddStringToObject(root, "type", "mode_close");
		} else {
			cJSON_AddStringToObject(root, "type", "mode_open");
			cJSON_AddNumberToObject(root, "percent", percent);
		}

		char * json = cJSON_Print(root);
		mqtt_publish(CONFIG_CONTROLLER_STATUS_TOPIC, json);
		cJSON_free(json);

		cJSON_Delete(root);
	}
}

void controller_exec_auto() {
	if (controller_check_locks()) {
		return;
	}

	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "type", "mode_auto");

	char * json = cJSON_Print(root);
	mqtt_publish(CONFIG_CONTROLLER_STATUS_TOPIC, json);
	cJSON_free(json);

	cJSON_Delete(root);
}

void controller_on_calibrate_success(uint8_t open_angle, uint8_t close_angle) {
	led_control_submit(LED_CONTROL_BLINK_3);


	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "type", "calibrate_success");
	cJSON_AddNumberToObject(root, "open_angle", open_angle);
	cJSON_AddNumberToObject(root, "close_angle", close_angle);

	char * json = cJSON_Print(root);
	mqtt_publish(CONFIG_CONTROLLER_STATUS_TOPIC, json);
	cJSON_free(json);

	cJSON_Delete(root);
}

void controller_exec_calibrate_auto(uint8_t init_angle) {
	if (controller_check_locks()) {
		return;
	}

	servo_control_calibrate_auto(init_angle, controller_on_calibrate_success);
}

void controller_exec_calibrate_manual(uint8_t open_angle, uint8_t close_angle) {
	if (controller_check_locks()) {
		return;
	}

	servo_control_calibrate_manual(open_angle, close_angle);
}
