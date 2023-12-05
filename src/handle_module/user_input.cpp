#include "user_input.h"

#include "Arduino.h"

#include "fm_receiver.h"

// PCINT22
#define USER_INPUT_PIN_OPEN  6

// PCINT0
#define USER_INPUT_PIN_CLOSE 8

#define USERINPUT_BIT_OPEN     (_BV(0))
#define USERINPUT_BIT_CLOSE    (_BV(1))

#define USERINPUT_ENTER_CALIBRATE_CLOSE_NUM      10
#define USERINPUT_ENTER_CALIBRATE_CLOSE_DELAY    1000

#define USERINPUT_ENTER_CALIBRATE_OPEN_NUM       3
#define USERINPUT_ENTER_CALIBRATE_OPEN_DELAY     2000

#define USERINPUT_ENTER_CALIBRATE_PREPCAL_AFTER  5

uint8_t user_input_buttons = 0;

uint8_t user_input_initcalibrate_step = 0;
unsigned long user_input_initcalibrate_delay = 0;

ISR(PCINT0_vect) {
  if (digitalRead(USER_INPUT_PIN_CLOSE) == LOW) {
    bitSet(user_input_buttons, USERINPUT_BIT_CLOSE);
  }
}

ISR(PCINT2_vect) {
  if (digitalRead(USER_INPUT_PIN_OPEN) == LOW) {
    bitSet(user_input_buttons, USERINPUT_BIT_OPEN);
  }

  if (digitalRead(FM_RECEIVER_PIN) == HIGH) {
    isr_fm_receiver_on_high();
  }
}

void user_input_init() {
  pinMode(USER_INPUT_PIN_OPEN,  INPUT);
  pinMode(USER_INPUT_PIN_CLOSE, INPUT);

  PCMSK0 = _BV(PCINT0);
  PCMSK2 = _BV(PCINT22) | _BV(PCINT23);

  PCICR =  _BV(PCIE0) | _BV(PCIE2);

  uint8_t oldSREG = SREG;
  cli();

  if (digitalRead(USER_INPUT_PIN_CLOSE) == LOW) {
    bitSet(user_input_buttons, USERINPUT_BIT_CLOSE);
  }
  if (digitalRead(USER_INPUT_PIN_OPEN) == LOW) {
    bitSet(user_input_buttons, USERINPUT_BIT_OPEN);
  }

  SREG = oldSREG;
}

uint8_t user_input_get_event() {
  uint8_t oldSREG = SREG;
  cli();
  uint8_t buttons = user_input_buttons;
  user_input_buttons = 0;
  SREG = oldSREG;

  if (buttons & USERINPUT_BIT_CLOSE) {
    if (millis() > user_input_initcalibrate_delay) {
      if (user_input_initcalibrate_step < USERINPUT_ENTER_CALIBRATE_CLOSE_NUM) {
        user_input_initcalibrate_step++;
        user_input_initcalibrate_delay = millis() + ((user_input_initcalibrate_step == USERINPUT_ENTER_CALIBRATE_CLOSE_NUM - 1) ? 
                                                      USERINPUT_ENTER_CALIBRATE_OPEN_DELAY :
                                                      USERINPUT_ENTER_CALIBRATE_CLOSE_DELAY);

        return (user_input_initcalibrate_step < USERINPUT_ENTER_CALIBRATE_PREPCAL_AFTER) ? USER_INPUT__CLOSE : USER_INPUT__PREPARE_CALIBRATE;
      } else {
        user_input_initcalibrate_step = 0;
        user_input_initcalibrate_delay = 0;
        return USER_INPUT__CLOSE;
      }
    } else {
      user_input_initcalibrate_step = 0;
      user_input_initcalibrate_delay = 0;
      return USER_INPUT__CLOSE;
    }
  }

  if (buttons & USERINPUT_BIT_OPEN) {
    if (user_input_initcalibrate_delay > 0 && 
        millis() > user_input_initcalibrate_delay && 
        user_input_initcalibrate_step >= USERINPUT_ENTER_CALIBRATE_CLOSE_NUM) {

        if (user_input_initcalibrate_step < USERINPUT_ENTER_CALIBRATE_CLOSE_NUM + USERINPUT_ENTER_CALIBRATE_OPEN_NUM) {
          user_input_initcalibrate_step++;
          user_input_initcalibrate_delay = millis() + USERINPUT_ENTER_CALIBRATE_OPEN_DELAY;
          return USER_INPUT__PREPARE_CALIBRATE;
        } else {
          user_input_initcalibrate_step = 0;
          user_input_initcalibrate_delay = 0;
          return USER_INPUT__CALIBRATE;
        }
    } else {
      user_input_initcalibrate_step = 0;
      user_input_initcalibrate_delay = 0;
      return USER_INPUT__OPEN;
    }
  }

  if (user_input_initcalibrate_delay > 0) {
    if (millis() <= user_input_initcalibrate_delay) {
      user_input_initcalibrate_step = 0;
      user_input_initcalibrate_delay = 0;
    }
  }

  return USER_INPUT__NOEVENT;
}
