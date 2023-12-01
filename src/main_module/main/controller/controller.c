#include "controller.h"

#include "controller_mqtt.h"
#include "../fm/fm_command_address_def.h"
#include "../fm/fm_command_defs.h"
#include "../fm/fm_sender.h"
#include "../log/log.h"
#include "../stepper/stepper_init.h"
#include "../stepper/stepper_commands.h"
#include "../charger/charger_init.h"
#include "stdbool.h"
#include <string.h>

#define CONTROLLER_PDU_ARG_FULL_OPEN   0x68
#define CONTROLLER_PDU_ARG_FULL_CLOSE  0x64
#define CONTROLLER_PDU_ARG_STEP_OPEN   0x62
#define CONTROLLER_PDU_ARG_STEP_CLOSE  0x61

#define CONTROLLER_HM_FULL_OPEN		   0x01
#define CONTROLLER_HM_FULL_CLOSE	   0x02
#define CONTROLLER_HM_STEP_OPEN		   0x03
#define CONTROLLER_HM_STEP_CLOSE	   0x04
#define CONTROLLER_HM_CALIBRATE		   0x05

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

void controller_process_hm_command(uint8_t arg) {
	switch (arg) {
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
	}
}

void controller_process_hm_charge_status(bool charge_in_progress) {
	if (charge_in_progress) {
		charger_confirm_in_progress();
	} else {
		charger_stop();
	}
}

void controller_process_om_charge_status(bool charge_in_progress) {
	if (charge_in_progress) {
		charger_confirm_in_progress();
	} else {
		charger_stop();
	}
}

void controller_process_command(const t_fm_command * command) {
	const uint8_t * args = command->args;

	switch (command->address) {
	case FM_COMMAND_ADDRESS__PDU:
		controller_process_pdu_command(args[0]);
		break;

	case FM_COMMAND_ADDRESS__MM_STEPPER_STATUS:
		// ignore this address - I receive myself commands
		break;

	case FM_COMMAND_ADDRESS__OM_CHARGE_STATUS:
		controller_process_om_charge_status(args[0]);
		break;
	case FM_COMMAND_ADDRESS__OM_ALARM:
		controller_mqtt_process_om_noise_alarm(args[0]);
		break;
	case FM_COMMAND_ADDRESS__OM_AIR_STATUS:
		controller_mqtt_process_om_air_data(args[0] - 100,
				                            args[1],
							     		    (args[2] << 16) + (args[3] << 8) + args[4]);
		break;
	case FM_COMMAND_ADDRESS__OM_NOISE_DATA:
		controller_mqtt_process_om_noise_data(args[0], args[1],
									          args[2], args[3],
									          args[4], args[5],
									          args[6], args[7],
									          args[8], args[9]);
		break;

	case FM_COMMAND_ADDRESS__HM_COMMAND:
		controller_process_hm_command(args[0]);
		break;
	case FM_COMMAND_ADDRESS__HM_CHARGE_STATUS:
		controller_process_hm_charge_status(args[0]);
		break;
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

