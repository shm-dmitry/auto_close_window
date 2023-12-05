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

void isr_fm_receiver_on_high() {
  unsigned long now = millis();

  if (fm_receiver_low_start > 0 &&
      fm_receiver_high_start < fm_receiver_low_start &&
      fm_receiver_low_start < now
      ) {
    if (
      // high duration
      fm_receiver_high_start - fm_receiver_low_start >= FM_RECEIVER_MIN_SYMBOL_LEN &&
      fm_receiver_high_start - fm_receiver_low_start <= FM_RECEIVER_MAX_SYMBOL_LEN &&

      // low duration
      now - fm_receiver_low_start >= FM_RECEIVER_MIN_SYMBOL_LEN &&
      now - fm_receiver_low_start <= FM_RECEIVER_MAX_SYMBOL_LEN
    ) {
      isr_fm_decoder_on_symbol(fm_receiver_high_start - fm_receiver_low_start, now - fm_receiver_low_start);

      fm_receiver_high_start = 0;
      fm_receiver_low_start = 0;
    } else {
      // bad length - reset states
      fm_receiver_high_start = 0;
      fm_receiver_low_start = 0;
    }
  }

  if (fm_receiver_high_start == 0) {
    fm_receiver_high_start = now;
  }
}

ISR (TIMER1_COMPA_vect) {
  if (fm_receiver_low_start == 0) {
    unsigned long now = millis();

    if (fm_receiver_high_start + FM_RECEIVER_LOW_AFTER_HIGH_LEN < now) {
      fm_receiver_low_start = now;
    }
  }
}

void fm_receiver_init() {
  fm_decoder_init();

  pinMode(FM_RECEIVER_PIN, INPUT);

  OCR1A = F_CPU / 8 / FM_RECEIVER_TIMER_FREQ; 
  TCCR1A = 0;
  TCCR1B = _BV(WGM12) | _BV(CS11);

  TIMSK1 = _BV(OCIE1A);
}
