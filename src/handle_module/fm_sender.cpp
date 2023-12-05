#include "fm_sender.h"

#include "Arduino.h"

#include "fm_decoder.h"
#include "encrypter.h"

#define FM_SENDER_CARRIER_FREQ         40000

#define FM_SENDER_PIN 3
#define FM_SENDING_BIT__PREPARE     0xFD
#define FM_SENDING_BIT__PREAMBLE    0xFE
#define FM_SENDING_BIT__FINISH      0xFF

#define FM_SENDER_NO_BUFFER         0xFF

#define FM_SENDER_DURATION_ONE_BIT   400

#define FM_SENDER_DURATION_PREPARE_HIGH (FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_PREPARE_LOW (FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_PREAMBLE_HIGH (FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_PREAMBLE_LOW (31*FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_BIT_1_HIGH (4 * FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_BIT_1_LOW (FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_BIT_0_HIGH (FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_BIT_0_LOW (4 * FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_LAST_SYMB_HIGH (FM_SENDER_DURATION_ONE_BIT)
#define FM_SENDER_DURATION_LAST_SYMB_LOW (FM_SENDER_DURATION_ONE_BIT)

#define FM_SENDER_DURATITON_TO_TICKS(x) ((uint16_t)((x) * (uint32_t)1000 / FM_SENDER_CARRIER_FREQ))

#define FM_SENDER_GET_BUFFER(index)      (((index) == 0) ? fm_sending_buffer_1      : fm_sending_buffer_2);
#define FM_SENDER_GET_BUFFER_SIZE(index) (((index) == 0) ? fm_sending_buffer_1_size : fm_sending_buffer_2_size);

uint8_t fm_sender_next_bit = FM_SENDING_BIT__PREPARE;
uint8_t fm_sending_buffer_1_size = 0;
uint8_t fm_sending_buffer_2_size = 0;
uint8_t * fm_sending_buffer_1 = NULL;
uint8_t * fm_sending_buffer_2 = NULL;
uint8_t fm_sending_buffer_current = FM_SENDER_NO_BUFFER;

uint16_t fm_sender_high_counter = 0;
uint16_t fm_sender_low_counter = 0;

void isr_fm_sender_switch_sending_buffer();

ISR (TIMER2_COMPA_vect) {
  if (fm_sending_buffer_current != FM_SENDER_NO_BUFFER) {
    if (fm_sender_high_counter > 0) {
      digitalWrite(FM_SENDER_PIN, (fm_sender_high_counter % 2 == 0) ? HIGH : LOW);
      fm_sender_high_counter--;
      return;
    }

    if (fm_sender_low_counter > 0) {
      digitalWrite(FM_SENDER_PIN, LOW);
      fm_sender_low_counter--;
      return;
    }

    if (fm_sender_next_bit == FM_SENDING_BIT__PREPARE) {
      fm_sender_high_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_PREPARE_HIGH);
      fm_sender_low_counter  = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_PREPARE_LOW);
      fm_sender_next_bit = FM_SENDING_BIT__PREAMBLE;
    } else if (fm_sender_next_bit == FM_SENDING_BIT__PREAMBLE) {
      fm_sender_high_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_PREAMBLE_HIGH);
      fm_sender_low_counter  = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_PREAMBLE_LOW);
      fm_sender_next_bit = 0;
    } else if (fm_sender_next_bit != FM_SENDING_BIT__FINISH) {
      uint8_t * buffer = FM_SENDER_GET_BUFFER(fm_sending_buffer_current);
      uint8_t size = FM_SENDER_GET_BUFFER_SIZE(fm_sending_buffer_current);

      if (fm_sender_next_bit < size * 8) {
        if (bitRead(buffer[fm_sender_next_bit / 8], (7 - fm_sender_next_bit % 8)) != 0) {
          fm_sender_high_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_BIT_1_HIGH);
          fm_sender_low_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_BIT_1_LOW);
        } else {
          fm_sender_high_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_BIT_0_HIGH);
          fm_sender_low_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_BIT_0_LOW);
        }

        fm_sender_next_bit++;
      } else {
        fm_sender_high_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_LAST_SYMB_HIGH);
        fm_sender_low_counter = FM_SENDER_DURATITON_TO_TICKS(FM_SENDER_DURATION_LAST_SYMB_LOW);
        fm_sender_next_bit = FM_SENDING_BIT__FINISH;
      }
    } else {
      isr_fm_sender_switch_sending_buffer();
      fm_sender_next_bit = FM_SENDING_BIT__PREPARE;
    }
  } else {
    isr_fm_sender_switch_sending_buffer();
  }
}

void isr_fm_sender_switch_sending_buffer() {
  if (fm_sending_buffer_current == 0) {
    free(fm_sending_buffer_1);
    fm_sending_buffer_1 = NULL;
    fm_sending_buffer_1_size = 0;

    fm_sending_buffer_current = FM_SENDER_NO_BUFFER;
  } else if (fm_sending_buffer_current == 1) {
    free(fm_sending_buffer_2);
    fm_sending_buffer_2 = NULL;
    fm_sending_buffer_2_size = 0;

    fm_sending_buffer_current = FM_SENDER_NO_BUFFER;
  } else if (isr_fm_decoder_is_air_clean()) {
    if (fm_sending_buffer_1 != NULL) {
      fm_sending_buffer_current = 0;
    } else if (fm_sending_buffer_2 != NULL) {
      fm_sending_buffer_current = 1;
    }
  }
}

void fm_sender_init() {
  pinMode(FM_SENDER_PIN, OUTPUT);
  digitalWrite(FM_SENDER_PIN, LOW);

  OCR2A = F_CPU / 8 / FM_SENDER_CARRIER_FREQ / 2; 
  TCCR2A = _BV(WGM21);
  TCCR1B = _BV(CS21);

  TIMSK2 = _BV(OCIE2A);
}

void fm_sender_send_command(const t_fm_command * command) {
  uint8_t * buffer = NULL;
  uint8_t size = 0;
  encrypter_process_memory(command, &buffer, &size);

  if (buffer == NULL) {
    return;
  }

  uint8_t oldSREG = SREG;
  cli();
  
  if (fm_sending_buffer_1 == NULL) {
    fm_sending_buffer_1 = buffer;
    fm_sending_buffer_1_size = size;
  } else if (fm_sending_buffer_2 == NULL) {
    fm_sending_buffer_2 = buffer;
    fm_sending_buffer_2_size = size;
  } else {
    free(buffer);
    buffer = NULL;
  }
  
  SREG = oldSREG;
}
