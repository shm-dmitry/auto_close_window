#include "servo.h"

#include "../cjson/cjson_helper.h"
#include "../init/mqtt.h"
#include "../init/init_logger.h"
#include "servo_control_api.h"

#define SERVO_ANGLE_NOCHANGE 0xFF
#define SERVO_ANGLE_OFF 0xFE

void servo_commands(const char * topic, const char * data) {
	cJSON *root = cJSON_Parse(data);
	if (root == NULL) {
		return;
	}

	uint8_t percent = get_number8_from_json(cJSON_GetObjectItem(root, "angle"), SERVO_ANGLE_NOCHANGE);
	if (percent != SERVO_ANGLE_NOCHANGE) {
		if (percent == SERVO_ANGLE_OFF) {
			servo_control_off();
		} else {
			servo_control_rotate_to(percent);
		}
	}

	cJSON_Delete(root);
}

void servo_init(int gpio, const char * commands_topic, const char * status_topic) {
	INIT_DRIVER_AND_LOG_OR_RETURN(servo_control_init(gpio), "SERVO driver initialized.", "Cant initlize SERVO driver: %d");

	mqtt_subscribe(commands_topic, servo_commands);
}
