#include "controller.h"

#include "../fm/fm_command_defs.h"
#include "../fm/fm_sender.h"
#include "../log/log.h"
#include "../stepper/stepper_init.h"
#include "../stepper/stepper_commands.h"
#include "../charger/charger_init.h"
#include "stdbool.h"
#include <string.h>

// TODO: REAL CODES required!
#define PDU_FULL_OPEN_COMMAND  0x1111
#define PDU_FULL_OPEN_ADDR     0x2222
#define PDU_FULL_CLOSE_COMMAND 0x3333
#define PDU_FULL_CLOSE_ADDR    0x4444
#define PDU_STEP_OPEN_COMMAND  0x5555
#define PDU_STEP_OPEN_ADDR     0x6666
#define PDU_STEP_CLOSE_COMMAND 0x7777
#define PDU_STEP_CLOSE_ADDR    0x8888

#define HM_FULL_OPEN		   0x01
#define HM_FULL_CLOSE		   0x02
#define HM_STEP_OPEN		   0x03
#define HM_STEP_CLOSE		   0x04
#define HM_CALIBRATE		   0x05
#define HM_ON_CHARGE_BEGIN	   0x06
#define HM_ON_CHARGE_END	   0x07

#define OM_ON_CHARGE_BEGIN	   0x51
#define OM_ON_CHARGE_END	   0x52
#define OM_STATUS_AIR          0x53
#define OM_STATUS_NOISE_ALRM   0x54
#define OM_STATUS_NOISE_DATA   0x55

#define MM_ON_STATUS   	       0xA0

void controller_on_air_data(int8_t temperature, uint8_t humidity, uint32_t pressure);
void controller_on_noise_alarm(bool alarm);
void controller_on_noise_data(uint8_t freq1, uint8_t level1, uint8_t freq2, uint8_t level2, uint8_t freq3, uint8_t level3, uint8_t freq4, uint8_t level4);

void controller_process_nec_command(uint16_t command, uint16_t address) {
	ESP_LOGI(LOG_CONTROLLER, "FM command: Address=%04X, Command=%04X", address, command);

	if (command == PDU_FULL_OPEN_COMMAND && address == PDU_FULL_OPEN_ADDR) {
		stepper_execute_command(STEPPER_COMMAND_FULL_OPEN);
	} else if (command == PDU_FULL_CLOSE_COMMAND && address == PDU_FULL_CLOSE_ADDR) {
		stepper_execute_command(STEPPER_COMMAND_FULL_CLOSE);
	} else if (command == PDU_STEP_OPEN_COMMAND && address == PDU_STEP_OPEN_ADDR) {
		stepper_execute_command(STEPPER_COMMAND_STEP_OPEN);
	} else if (command == PDU_STEP_CLOSE_COMMAND && address == PDU_STEP_CLOSE_ADDR) {
		stepper_execute_command(STEPPER_COMMAND_STEP_CLOSE);
	}
}

void controller_process_exts_command(uint8_t command, const uint8_t * args) {
	ESP_LOGI(LOG_CONTROLLER, "EXT command: Command=%02X, ARGs={ %02X %02X %02X %02X %02X %02X %02X %02X }",
			command, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);

	switch(command) {
	case HM_FULL_OPEN:
		stepper_execute_command(STEPPER_COMMAND_FULL_OPEN);
		break;
	case HM_FULL_CLOSE:
		stepper_execute_command(STEPPER_COMMAND_FULL_CLOSE);
		break;
	case HM_STEP_OPEN:
		stepper_execute_command(STEPPER_COMMAND_STEP_OPEN);
		break;
	case HM_STEP_CLOSE:
		stepper_execute_command(STEPPER_COMMAND_STEP_CLOSE);
		break;
	case HM_CALIBRATE:
		stepper_execute_command(STEPPER_COMMAND_CALIBRATE);
		break;
	case HM_ON_CHARGE_BEGIN:
	case OM_ON_CHARGE_BEGIN:
		charger_confirm_started();
		break;
	case HM_ON_CHARGE_END:
	case OM_ON_CHARGE_END:
		charger_stop();
		break;
	case OM_STATUS_AIR:
		controller_on_air_data(args[0] - 100, args[1], (args[2] << 16) + (args[3] << 8) + args[4]);
		break;
	case OM_STATUS_NOISE_ALRM:
		controller_on_noise_alarm(args[0] == 1);
		break;
	case OM_STATUS_NOISE_DATA:
		controller_on_noise_data(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
		break;
	}
}

void controller_process_command(const t_fm_command * command) {
	if (command->protocol == FM_COMMAND_PROTOCOL_NEC) {
		controller_process_nec_command(command->command, ((command->args[0] << 8) + command->args[1]));
	} else {
		controller_process_exts_command(command->args[0], command->args + 1);
	}
}

void controller_on_status(uint8_t status) {
	t_fm_command req;
	memset(&req, 0, sizeof(t_fm_command));

	req.protocol = FM_COMMAND_PROTOCOL_EXTENDED;
	req.args[0] = MM_ON_STATUS;
	req.args[1] = status;

	fm_sender_send(&req);
}

void controller_on_air_data(int8_t temperature, uint8_t humidity, uint32_t pressure) {
	ESP_LOGI(LOG_CONTROLLER, "OM AIR status: temperature=%d C, humidity=%d%%, pressure=%li Pa", temperature, humidity, pressure);
}

void controller_on_noise_alarm(bool alarm) {
	ESP_LOGI(LOG_CONTROLLER, "OM NOISE alarm: %s", (alarm ? "ON" : "OFF"));
}

void controller_on_noise_data(uint8_t freq1, uint8_t level1, uint8_t freq2, uint8_t level2, uint8_t freq3, uint8_t level3, uint8_t freq4, uint8_t level4) {
	ESP_LOGI(LOG_CONTROLLER, "OM NOISE data: freq1: [ %d = %d ]; freq2: [ %d = %d ]; freq3: [ %d = %d ]; freq4: [ %d = %d ]", freq1, level1, freq2, level2, freq3, level3, freq4, level4);
}

