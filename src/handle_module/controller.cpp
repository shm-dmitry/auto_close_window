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

#define CONTROLLER_CHECK_CHARGING_DELAY_MS 10000

#define CONTROLLER_BAT_STATUS_FIRST_NOTIFY_DELAY 5000
#define CONTROLLER_BAT_STATUS_NOTIFY_REPEAT      5000

#define CONTROLLER_BAT_STATUS_V_OFFSET 450

unsigned long controller_check_chargin_delay = 0;
bool controller_charge_in_progress = false;
unsigned long controller_next_bat_status_notify = CONTROLLER_BAT_STATUS_FIRST_NOTIFY_DELAY;

void controller_check_charging();

void controller_on_open();
void controller_on_close();
void controller_on_prepare_calibrate();
void controller_on_calibrate();
void controller_check_data_received();
void controller_on_notify_bat_status();

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

  if (millis() > controller_next_bat_status_notify) {
    controller_next_bat_status_notify = millis() + CONTROLLER_BAT_STATUS_NOTIFY_REPEAT;

    controller_on_notify_bat_status();
  }
}

void controller_check_charging() {
  if (millis() > controller_check_chargin_delay) {
    controller_check_chargin_delay = millis() + CONTROLLER_CHECK_CHARGING_DELAY_MS;

    if (power_manager_is_acok()) {
      Serial.println("ACOK");

      power_manager_on_event();

      if (power_manager_is_charging()) {
      Serial.println("charge on");
        controller_charge_in_progress = true;

        t_fm_command cmd = {
          .address = FM_COMMAND_ADDRESS__HM_CHARGE_STATUS,
          .arg1 = true,
          .arg2 = 0,
          .argssize = 1
        };

        fm_sender_send_command(&cmd);
        led_run_inform(LED_CHARGE_IN_PROGRESS);
      } else {
      Serial.println("charge off");
      }
    }else if (controller_charge_in_progress) {
      controller_charge_in_progress = false;

      t_fm_command cmd = {
        .address = FM_COMMAND_ADDRESS__HM_CHARGE_STATUS,
        .arg1 = false,
        .arg2 = 0,
        .argssize = 1
      };

      fm_sender_send_command(&cmd);
    }
  }
}

void controller_on_charger_error(uint8_t err) {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_CHARGE_ERROR,
    .arg1 = err,
    .arg2 = 0,
    .argssize = 1
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
  if (address == FM_COMMAND_ADDRESS__HM_COMMAND || address == FM_COMMAND_ADDRESS__HM_CHARGE_ERROR || address == FM_COMMAND_ADDRESS__HM_CHARGE_STATUS || address == FM_COMMAND_ADDRESS__HM_BAT_STATUS) {
    Serial.print("FM addr [self/skipped]: ");
    Serial.println(address, HEX);
   
    free(buffer);
    buffer = NULL;
    return;
  } else {
    Serial.print("FM addr ");
    Serial.println(address, HEX);
  }

  t_fm_command * command = decrypter_process_memory(address, buffer + 2, buffer_size - 2);
  if (command == NULL) {
    Serial.println("Decrypt failed");

    free(buffer);
    return;
  }

  Serial.print("Received command from host: ");
  Serial.println(command->arg1, HEX);

  if (command->address == FM_COMMAND_ADDRESS__MM_STEPPER_STATUS) {
    switch (command->arg1) {
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
      case CONTROLLER_STATUS_WINDOW_LOCK_OPENED:
      case CONTROLLER_STATUS_ERROR_RAISED:
        led_run_inform(LED_FAIL_WINDOW_LOCK_OPENED);
      break;
      default:
      Serial.print("Host sended unknown command: ");
      Serial.println(command->arg1, HEX);
      break;
    }
  }

  free(command);
  free(buffer);
}

void controller_on_open() {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_COMMAND,
    .arg1 = CONTROLLER_HM_FULL_OPEN,
    .arg2 = 0,
    .argssize = 1
  };

  fm_sender_send_command(&cmd);
}

void controller_on_close() {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_COMMAND,
    .arg1 = CONTROLLER_HM_FULL_CLOSE,
    .arg2 = 0,
    .argssize = 1
  };

  fm_sender_send_command(&cmd);
}

void controller_on_prepare_calibrate() {
  led_run_inform(LED_PREENTER_CALLIBRATE);
}

void controller_on_calibrate() {
  t_fm_command cmd = {
    .address = FM_COMMAND_ADDRESS__HM_COMMAND,
    .arg1 = CONTROLLER_HM_CALIBRATE,
    .arg2 = 0,
    .argssize = 1
  };

  fm_sender_send_command(&cmd);
}

void controller_on_notify_bat_status() {
    uint16_t voltage_mv = 0;
    int16_t current_ma = 0;

    power_manager_read_batstatus(voltage_mv, current_ma);
    if (voltage_mv == 0) {
      return;
    }


    Serial.print("Bat status: V = ");
    Serial.print(voltage_mv);
    Serial.print(" mV; I = ");
    Serial.print(current_ma);
    Serial.println(" mA");

    uint8_t v = (uint8_t) (voltage_mv / (uint16_t)10 - (uint16_t)CONTROLLER_BAT_STATUS_V_OFFSET);
    uint8_t i = 0;

    if (current_ma == 0) {
      i = 0;
    } else if (current_ma > 0) {
      uint8_t t = (uint8_t)((uint16_t)current_ma / (uint16_t)10);
      if (t & 0b10000000) {
        // overflow
        i = 0b01111111;
      } else {
        i = t;
      }
    } else {
      uint8_t t = (uint8_t)((uint16_t)(-current_ma) / (uint16_t)10);
      if (t & 0b10000000) {
        // overflow
        i = 0b11111111;
      } else {
        i = t + 0b10000000;
      }
    }

    t_fm_command cmd = {
      .address = FM_COMMAND_ADDRESS__HM_BAT_STATUS,
      .arg1 = v,
      .arg2 = i,
      .argssize = 2
    };

    fm_sender_send_command(&cmd);
}
