#include "controller.h"

#include "../fm/fm_command_address_def.h"
#include "../fm/fm_command_defs.h"
#include "../fm/fm_sender.h"
#include "../log/log.h"
#include "../stepper/stepper_init.h"
#include "../stepper/stepper_commands.h"
#include "../charger/charger_init.h"
#include "stdbool.h"
#include <string.h>

#define CONTROLLER_PDU_ARG_FULL_OPEN 	0x68
#define CONTROLLER_PDU_ARG_FULL_CLOSE  0x64
#define CONTROLLER_PDU_ARG_STEP_OPEN   0x62
#define CONTROLLER_PDU_ARG_STEP_CLOSE  0x61

#define CONTROLLER_HM_FULL_OPEN		   0x01
#define CONTROLLER_HM_FULL_CLOSE		   0x02
#define CONTROLLER_HM_STEP_OPEN		   0x03
#define CONTROLLER_HM_STEP_CLOSE		   0x04
#define CONTROLLER_HM_CALIBRATE		   0x05
#define CONTROLLER_HM_ON_CHARGE_BEGIN	   0x06
#define CONTROLLER_HM_ON_CHARGE_END	   0x07

#define CONTROLLER_OM_ON_CHARGE_BEGIN	   0x51
#define CONTROLLER_OM_ON_CHARGE_END	   0x52
#define CONTROLLER_OM_STATUS_AIR          0x53
#define CONTROLLER_OM_STATUS_NOISE_ALRM   0x54
#define CONTROLLER_OM_STATUS_NOISE_DATA   0x55

#define CONTROLLER_MM_ON_STATUS   	       0xA0

void controller_on_air_data(int8_t temperature, uint8_t humidity, uint32_t pressure);
void controller_on_noise_alarm(bool alarm);
void controller_on_noise_data(uint8_t freq1, uint8_t level1, uint8_t freq2, uint8_t level2, uint8_t freq3, uint8_t level3, uint8_t freq4, uint8_t level4);

void controller_process_pdu_command(uint8_t arg) {
	ESP_LOGI(LOG_CONTROLLER, "PDU command: arg=%02X", arg);

	switch (arg) {
		case CONTROLLER_PDU_ARG_FULL_OPEN:
			stepper_execute_command(STEPPER_COMMAND_FULL_OPEN);
			break;
		case CONTROLLER_PDU_ARG_FULL_CLOSE:
			stepper_execute_command(STEPPER_COMMAND_FULL_CLOSE);
			break;
		case CONTROLLER_PDU_ARG_STEP_OPEN:
			stepper_execute_command(STEPPER_COMMAND_STEP_OPEN);
			break;
		case CONTROLLER_PDU_ARG_STEP_CLOSE:
			stepper_execute_command(STEPPER_COMMAND_STEP_CLOSE);
			break;
	}
}

void controller_process_internal_command(uint16_t address, const uint8_t * args, uint8_t args_size) {
	ESP_LOGI(LOG_CONTROLLER, "Address = %04X; args size = %d; args[0] == %02X", address, args_size, args[0]);
return;
	switch(args[0]) {
	case CONTROLLER_HM_FULL_OPEN:
		stepper_execute_command(STEPPER_COMMAND_FULL_OPEN);
		break;
	case CONTROLLER_HM_FULL_CLOSE:
		stepper_execute_command(STEPPER_COMMAND_FULL_CLOSE);
		break;
	case CONTROLLER_HM_STEP_OPEN:
		stepper_execute_command(STEPPER_COMMAND_STEP_OPEN);
		break;
	case CONTROLLER_HM_STEP_CLOSE:
		stepper_execute_command(STEPPER_COMMAND_STEP_CLOSE);
		break;
	case CONTROLLER_HM_CALIBRATE:
		stepper_execute_command(STEPPER_COMMAND_CALIBRATE);
		break;
	case CONTROLLER_HM_ON_CHARGE_BEGIN:
	case CONTROLLER_OM_ON_CHARGE_BEGIN:
		charger_confirm_started();
		break;
	case CONTROLLER_HM_ON_CHARGE_END:
	case CONTROLLER_OM_ON_CHARGE_END:
		charger_stop();
		break;
	case CONTROLLER_OM_STATUS_AIR:
		controller_on_air_data(args[0] - 100, args[1], (args[2] << 16) + (args[3] << 8) + args[4]);
		break;
	case CONTROLLER_OM_STATUS_NOISE_ALRM:
		controller_on_noise_alarm(args[0] == 1);
		break;
	case CONTROLLER_OM_STATUS_NOISE_DATA:
		controller_on_noise_data(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
		break;
	}
}

void controller_process_command(const t_fm_command * command) {
	if (command->address == FM_COMMAND_ADDRESS__PDU) {
		controller_process_pdu_command(command->args[0]);
	} else {
		controller_process_internal_command(command->address, command->args, command->args_size);
	}
}

void controller_on_status(uint8_t status) {
	t_fm_command cmd;
	memset(&cmd, 0, sizeof(t_fm_command));
	cmd.address = FM_COMMAND_ADDRESS__MM_STEPPER_STATUS;
	cmd.args[0] = status;
	cmd.args_size = 1;

	fm_sender_send(&cmd);
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

