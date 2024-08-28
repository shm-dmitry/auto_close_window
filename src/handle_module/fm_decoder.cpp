#include "fm_decoder.h"

#include "string.h"
#include "Arduino.h"

#define FM_DECODER_AIR_CLEAN_DELAY    10

#define FM_DECODER_PREAMBLE_LOW_DIV_HIGH 20

#define FM_DECODER_BIT_1_HIGH_DIV_LOW  2
#define FM_DECODER_BIT_0_LOW_DIV_HIGH  2

// receive buffer allows one argument only!
#define FM_DECODER_BUFFER_SIZE (2 + 2 + 1 + 1)

#define FM_DECODER_NO_FILLED_BUFFER 0xFF

#define FM_DECODER_GET_ACTIVE_BUFFER(index) ((index == 0) ? fm_decoder_buffer_1 : fm_decoder_buffer_2)

bool fm_decoder_found_preamble = false;
uint8_t fm_decoder_received_bits = 0;
uint8_t fm_decoder_actual_buffer = 0;
uint8_t fm_decoder_filled_buffer = FM_DECODER_NO_FILLED_BUFFER;
uint8_t fm_decoder_buffer_1[FM_DECODER_BUFFER_SIZE];
uint8_t fm_decoder_buffer_2[FM_DECODER_BUFFER_SIZE];

unsigned long fm_decoder_millis = 0;
unsigned long fm_decoder_last_activity = 0;

void fm_decoder_init() {
  memset(fm_decoder_buffer_1, 0, FM_DECODER_BUFFER_SIZE);
  memset(fm_decoder_buffer_2, 0, FM_DECODER_BUFFER_SIZE);
}

void isr_fm_decoder_on_symbol(uint16_t high, uint16_t low) {
  if (!fm_decoder_found_preamble) {
    if (low > high && (low / high) >= FM_DECODER_PREAMBLE_LOW_DIV_HIGH) {
      fm_decoder_found_preamble = true;
      fm_decoder_received_bits  = 0;
    }

    return;
  }

  fm_decoder_last_activity = fm_decoder_millis;

  uint8_t * fm_decoder_buffer = FM_DECODER_GET_ACTIVE_BUFFER(fm_decoder_actual_buffer);

  uint8_t bit = 0;
  if (low > high && (low / high) >= FM_DECODER_BIT_0_LOW_DIV_HIGH) {
    bit = 0;
  } else if (high > low && (high / low) >= FM_DECODER_BIT_1_HIGH_DIV_LOW) {
    bit = 1;
  } else {
    fm_decoder_found_preamble = false;
    memset(fm_decoder_buffer, 0, FM_DECODER_BUFFER_SIZE);
    fm_decoder_received_bits = 0;
    return;
  }

  fm_decoder_buffer[fm_decoder_received_bits / 8] = 
            fm_decoder_buffer[fm_decoder_received_bits / 8] +
            (bit << (7 - (fm_decoder_received_bits % 8)));
  fm_decoder_received_bits++;

  if (fm_decoder_received_bits == FM_DECODER_BUFFER_SIZE * 8) {
    fm_decoder_filled_buffer = fm_decoder_actual_buffer;
    fm_decoder_actual_buffer = (fm_decoder_actual_buffer == 0) ? 1 : 0;

    fm_decoder_buffer = FM_DECODER_GET_ACTIVE_BUFFER(fm_decoder_actual_buffer);

    fm_decoder_found_preamble = false;
    memset(fm_decoder_buffer, 0, FM_DECODER_BUFFER_SIZE);
    fm_decoder_received_bits = 0;
  }
}

void fm_decoder_get_data(uint8_t ** buffer, uint8_t * buffer_size) {
  uint8_t oldSREG = SREG;
  cli();

  if (fm_decoder_filled_buffer != FM_DECODER_NO_FILLED_BUFFER) {
    uint8_t * temp = FM_DECODER_GET_ACTIVE_BUFFER(fm_decoder_filled_buffer);
    *buffer = (uint8_t*)malloc(FM_DECODER_BUFFER_SIZE);
    if (*buffer != NULL) {
      memcpy(*buffer, temp, FM_DECODER_BUFFER_SIZE);
      *buffer_size = FM_DECODER_BUFFER_SIZE;
    }

    fm_decoder_filled_buffer = FM_DECODER_NO_FILLED_BUFFER;
  }

  SREG = oldSREG;
}

void fm_decoder_on_main_loop() {
  fm_decoder_millis = millis();
}

bool fm_decoder_is_air_clean() {
  uint8_t oldSREG = SREG;
  cli();
  unsigned long temp = fm_decoder_last_activity;
  SREG = oldSREG;

  return (temp + FM_DECODER_AIR_CLEAN_DELAY) < millis() ? true : false;
}

