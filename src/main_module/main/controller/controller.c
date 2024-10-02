#include "controller.h"

#include "controller_mqtt.h"
#include "../fm/fm_command_address_def.h"
#include "../fm/fm_command_defs.h"
#include "../fm/fm_sender.h"
#include "../log/log.h"
#include "../stepper/stepper_init.h"
#include "../charger/charger_init.h"
#include "../common/nvs_rw.h"
#include "stdbool.h"
#include <string.h>

#include "controller_args_def.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// This codes used by my remote control unit
// Change them to your codes.
// You can just press buttons and check log messages
#define CONTROLLER_PDU1_ARG_BUTTON1   0x68
#define CONTROLLER_PDU1_ARG_BUTTON2   0x64
#define CONTROLLER_PDU1_ARG_BUTTON3   0x62
#define CONTROLLER_PDU1_ARG_BUTTON4   0x61
#define CONTROLLER_PDU2_ARG_BUTTON1   0xA8
#define CONTROLLER_PDU2_ARG_BUTTON2   0xA4
#define CONTROLLER_PDU2_ARG_BUTTON3   0xA2
#define CONTROLLER_PDU2_ARG_BUTTON4   0xA1

#define CONTROLLER_BAT_STATUS_V_OFFSET 450

#define CONTROLLER_MQTT_ASYNC_MESSAGE__ERROR    1
#define CONTROLLER_MQTT_ASYNC_MESSAGE__POSITION 2

#define CONTROLLER_ASYNC_MQTT_TASK_STACK_SIZE 4096

#define CONTROLLER_LIGHT_OPEN_PERCENT 10
#define CONTROLLER_LIGHT_OPEN_PERCENT_CONFIG "cntrl_lopc"

static volatile uint8_t controller_light_open_percent = CONTROLLER_LIGHT_OPEN_PERCENT;

QueueHandle_t controller_mqtt_async_message_queue;

static void controller_mqtt_async_message_task(void*);

void controller_process_pdu1_command(uint16_t freq, uint8_t arg) {
	_ESP_LOGI(LOG_CONTROLLER, "PDU1 command: arg=%02X on freq %d", arg, freq);

	switch (arg) {
		case CONTROLLER_PDU1_ARG_BUTTON1:
			stepper_move_to(100);
			break;
		case CONTROLLER_PDU1_ARG_BUTTON2:
			stepper_move_to(0);
			break;
		case CONTROLLER_PDU1_ARG_BUTTON3:
			stepper_cancel();
			break;
		case CONTROLLER_PDU1_ARG_BUTTON4:
			stepper_move_to(controller_light_open_percent);
			break;
	}
}

void controller_process_pdu2_command(uint16_t freq, uint8_t arg) {
	_ESP_LOGI(LOG_CONTROLLER, "PDU2 command: arg=%02X on freq %d", arg, freq);

	switch (arg) {
		case CONTROLLER_PDU2_ARG_BUTTON1:
			stepper_move_to(100);
			break;
		case CONTROLLER_PDU2_ARG_BUTTON2:
			stepper_move_to(0);
			break;
		case CONTROLLER_PDU2_ARG_BUTTON3:
			stepper_cancel();
			break;
		case CONTROLLER_PDU2_ARG_BUTTON4:
			stepper_move_to(controller_light_open_percent);
			break;
	}
}
void controller_process_hm_command(uint16_t freq, uint8_t arg) {
	_ESP_LOGI(LOG_CONTROLLER, "HM command: arg=%02X on freq %d", arg, freq);

	switch (arg) {
		case CONTROLLER_HM_FULL_OPEN:
			if (stepper_is_now_executing_move_to(100)) {
				stepper_cancel();
			} else {
				stepper_move_to(100);
			}
			break;
		case CONTROLLER_HM_FULL_CLOSE:
			if (stepper_is_now_executing_move_to(0)) {
				stepper_cancel();
			} else {
				stepper_move_to(0);
			}
			break;
		case CONTROLLER_HM_CALIBRATE:
			stepper_calibrate();
			break;
		case CONTROLLER_HM_CANCEL_ERROR:
			stepper_cancel_error();
			break;
		default:
			ESP_LOGW(LOG_CONTROLLER, "HM command : unknown arg %02X", arg);
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

void controller_process_hmom_bat_status(bool hm, uint8_t _voltage, uint8_t _current) {
	uint16_t v = ((uint16_t)_voltage + CONTROLLER_BAT_STATUS_V_OFFSET) * 10;
	bool charge_in_progress = !(_current & 0b10000000);
	_current = _current & 0b01111111;
	uint16_t i = (uint16_t) _current * (uint16_t) 10;

	controller_mqtt_process_bat_status(hm, v, i, charge_in_progress);
}

void controller_process_command(uint16_t freq, const t_fm_command * command) {
	const uint8_t * args = command->args;

	switch (command->address) {
	case FM_COMMAND_ADDRESS__PDU1:
		controller_process_pdu1_command(freq, args[0]);
		break;

	case FM_COMMAND_ADDRESS__PDU2:
		controller_process_pdu2_command(freq, args[0]);
		break;

	case FM_COMMAND_ADDRESS__MM_STEPPER_STATUS:
		_ESP_LOGI(LOG_CONTROLLER, "Received self message with arg = %02X on freq %d", args[0], freq);
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
		controller_process_hm_command(freq, args[0]);
		break;
	case FM_COMMAND_ADDRESS__HM_CHARGE_STATUS:
		controller_process_hm_charge_status(args[0]);
		break;
	case FM_COMMAND_ADDRESS__HM_BAT_STATUS:
		controller_process_hmom_bat_status(true, args[0], args[1]);
		break;
	default:
		ESP_LOGW(LOG_CONTROLLER, "Unknown address = %04X (arg0 == %02X)", command->address, args[0]);
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

	if (status == CONTROLLER_STATUS_ERROR_RAISED || status == CONTROLLER_STATUS_ERROR_CANCELLED) {
		uint16_t x = (status << 8) + CONTROLLER_MQTT_ASYNC_MESSAGE__ERROR;
		xQueueSend(controller_mqtt_async_message_queue, &x, 0);
	}
}

void controller_on_stepper_position_updated(uint8_t percent) {
	uint16_t x = (percent << 8) + CONTROLLER_MQTT_ASYNC_MESSAGE__POSITION;
	xQueueSend(controller_mqtt_async_message_queue, &x, 0);
}

static void controller_mqtt_async_message_task(void*) {
	while(true) {
		uint16_t data = 0;
		xQueueReceive(controller_mqtt_async_message_queue, &data, portMAX_DELAY);
		if (data == 0) {
			continue;
		}

		switch ((data & 0xFF)) {
		case CONTROLLER_MQTT_ASYNC_MESSAGE__ERROR: {
			uint8_t status = data >> 8;
			if (status == CONTROLLER_STATUS_ERROR_RAISED) {
				controller_mqtt_on_stepper_error(true);
			} else if (status == CONTROLLER_STATUS_ERROR_CANCELLED) {
				controller_mqtt_on_stepper_error(false);
			}
		}
		break;
		case CONTROLLER_MQTT_ASYNC_MESSAGE__POSITION: {
			controller_mqtt_stepper_position_updated(data >> 8);
		}
		break;
		default:
			break;
		}
	}
}

void controller_init() {
	controller_mqtt_async_message_queue = xQueueCreate(5, sizeof(uint16_t));
	xTaskCreate(controller_mqtt_async_message_task, "controller async mqtt", CONTROLLER_ASYNC_MQTT_TASK_STACK_SIZE, NULL, 10, NULL);

	uint8_t * buf = malloc(1);
	if (buf) {
		*buf = 0;
		size_t size = 0;
		nvs_read_buffer(CONTROLLER_LIGHT_OPEN_PERCENT_CONFIG, &buf, &size);

		if ((size == 1) &&
			((*buf) < 100) &&
			((*buf) > 0)) {
			controller_light_open_percent = *buf;
		} else {
			controller_light_open_percent = CONTROLLER_LIGHT_OPEN_PERCENT;
		}

		free(buf);
	}
}

void controller_set_light_open_percent(uint8_t value) {
	if (value > 0 && value < 100) {
		controller_light_open_percent = value;

		uint8_t temp = controller_light_open_percent;
		nvs_write_buffer(CONTROLLER_LIGHT_OPEN_PERCENT_CONFIG, &temp, 1);
	}
}
