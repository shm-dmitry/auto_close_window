#include "controller.h"

#include "Arduino.h"

#include "user_input.h"
#include "power_manager.h"
#include "fm_decoder.h"
#include "encrypter.h"
#include "fm_command_address_def.h"
#include "controller_status_def.h"
#include "controller_args_def.h"
#include "fm_sender.h"
#include "led.h"

#define CONTROLLER_CHECK_CHARGING_DELAY_MS 5000

unsigned long controller_check_chargin_delay = 0;
bool controller_charge_in_progress = false;

void controller_check_charging();

void controller_on_open();
void controller_on_close();
void controller_on_prepare_calibrate();
void controller_on_calibrate();
void controller_check_data_received();

void controller_on_main_loop() {
  controller_check_charging();

  switch(user_input_get_event()) {
    case USER_INPUT__OPEN:
    controller_on_open();
    power_manager_on_event();
    break;
    case USER_INPUT__CLOSE:
    controller_on_close();
    power_manager_on_event();
    break;
    case USER_INPUT__PREPARE_CALIBRATE:
    controller_on_prepare_calibrate();
    power_manager_on_event();
    break;
    case USER_INPUT__CALIBRATE:
    controller_on_calibrate();
    power_manager_on_event();
    break;

    case USER_INPUT__NOEVENT:
    default:
    break;
  }

  controller_check_data_received();
}

void controller_check_charging() {
  if (millis() > controller_check_chargin_delay) {
    controller_check_chargin_delay = millis() + CONTROLLER_CHECK_CHARGING_DELAY_MS;

    if (power_manager_is_charging()) {
      controller_charge_in_progress = true;
      power_manager_on_event();

      Serial.println("CHRG 1");

      t_fm_command cmd = {
        .address = FM_COMMAND_ADDRESS__HM_CHARGE_STATUS,
        .arg = true
      };

      fm_sender_send_command(&cmd);
    } else if (controller_charge_in_progress) {
      controller_charge_in_progress = false;

      Serial.println("CHRG 0");

      t_fm_command cmd = {
        .address = FM_COMMAND_ADDRESS__HM_CHARGE_STATUS,
        .arg = false
      };

      fm_sender_send_command(&cmd);
    }
  }
}

void controller_on_charger_error(uint8_t err) {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_CHARGE_ERROR,
    .arg = err
  };

  fm_sender_send_command(&cmd);
}

void controller_check_data_received() {
  uint8_t * buffer = NULL;
  uint8_t buffer_size = 0;
  fm_decoder_get_data(&buffer, &buffer_size);
  
  if (buffer == NULL) {
    return;
  }

  uint16_t address = (buffer[0] << 8) + buffer[1];
    Serial.print("FM addr ");
    Serial.println(address, HEX);

  t_fm_command * command = decrypter_process_memory(address, buffer + 2, buffer_size - 2);
  if (command == NULL) {
    free(buffer);
    return;
  }

  if (command->address == FM_COMMAND_ADDRESS__MM_STEPPER_STATUS) {
    switch (command->arg) {
      case CONTROLLER_STATUS_START_EXECUTE_OPEN:
        led_run_inform(LED_START_OPEN);
        break;
      case CONTROLLER_STATUS_START_EXECUTE_CLOSE:
        led_run_inform(LED_START_CLOSE);
        break;
      case CONTROLLER_STATUS_END_EXECUTE_OPEN:
        led_run_inform(LED_END_OPEN);
        break;
      case CONTROLLER_STATUS_END_EXECUTE_CLOSE:
        led_run_inform(LED_END_CLOSE);
        break;
      case CONTROLLER_STATUS_START_FIND_POSITION:
        led_run_inform(LED_START_FIND_POS);
        break;
      case CONTROLLER_STATUS_START_CALIBRATION:
        led_run_inform(LED_CALIBRATE);
        break;
      case CONTROLLER_STATUS_END_CALIBRATION:
        led_run_inform(LED_END_CALIBRATE);
        break;
      case CONTROLLER_STATUS_FAIL_CALIBRATION:
        led_run_inform(LED_FAIL_CALIBRATE);
      break;
      default:
      break;
    }
  }

  free(command);
  free(buffer);
}

void controller_on_open() {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_COMMAND,
    .arg = CONTROLLER_HM_FULL_OPEN
  };

  fm_sender_send_command(&cmd);
}

void controller_on_close() {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_COMMAND,
    .arg = CONTROLLER_HM_FULL_CLOSE
  };

  fm_sender_send_command(&cmd);
}

void controller_on_prepare_calibrate() {
  led_run_inform(LED_PREENTER_CALLIBRATE);
}

void controller_on_calibrate() {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_COMMAND,
    .arg = CONTROLLER_HM_CALIBRATE
  };

  fm_sender_send_command(&cmd);
}
