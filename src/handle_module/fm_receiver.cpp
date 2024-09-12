#include "fm_receiver.h"

#include "Arduino.h"
#include "fm_decoder.h"

#define FM_RECEIVER_CARRIER_FREQ         40000

#define FM_RECEIVER_MIN_SYMBOL_LEN       100
#define FM_RECEIVER_MAX_SYMBOL_LEN       (600*31)
#define FM_RECEIVER_LOW_AFTER_HIGH_LEN   10


#define FM_RECEIVER_TIMER_FREQ (FM_RECEIVER_CARRIER_FREQ / 2)

unsigned long fm_receiver_high_start = 0;
unsigned long fm_receiver_low_start  = 0;
bool fm_receiver_last_state_high = false;

void isr_fm_receiver_on_high(bool high) {
  if (fm_receiver_last_state_high == high) {
    return;
  }

  fm_receiver_last_state_high = high;

  unsigned long now = micros();

  if (fm_receiver_last_state_high) {
    if ( // check PREVIOUS times
      fm_receiver_low_start > 0 &&
      now > fm_receiver_low_start &&
      fm_receiver_high_start < fm_receiver_low_start
    ) {
      if (
        // high duration
        fm_receiver_low_start - fm_receiver_high_start >= FM_RECEIVER_MIN_SYMBOL_LEN &&
        fm_receiver_low_start - fm_receiver_high_start <= FM_RECEIVER_MAX_SYMBOL_LEN &&

        // low duration
        now - fm_receiver_low_start >= FM_RECEIVER_MIN_SYMBOL_LEN &&
        now - fm_receiver_low_start <= FM_RECEIVER_MAX_SYMBOL_LEN
      ) {
        isr_fm_decoder_on_symbol(fm_receiver_low_start - fm_receiver_high_start, now - fm_receiver_low_start);

        // start next symbol recording
        fm_receiver_high_start = now;
        fm_receiver_low_start = 0;
      } else {
        // bad duration - reset
        fm_receiver_high_start = now;
        fm_receiver_low_start = 0;
      }
    } else {
      // something wrong with durations - start next symbol recording
      fm_receiver_high_start = now;
      fm_receiver_low_start = 0;
    }
  } else {
    fm_receiver_low_start = now;
  }
}

void fm_receiver_init() {
  fm_receiver_high_start = 0;
  fm_receiver_low_start  = 0;
  fm_receiver_last_state_high = false;

  fm_decoder_init();

  pinMode(FM_RECEIVER_PIN, INPUT);
}

