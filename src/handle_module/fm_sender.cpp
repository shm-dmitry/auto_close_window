#include "fm_sender.h"

#include "Arduino.h"

#include "fm_decoder.h"
#include "encrypter.h"

#define FM_SENDER_PIN 3
#define FM_SENDING_BIT__PREPARE     0xFD
#define FM_SENDING_BIT__PREAMBLE    0xFE
#define FM_SENDING_BIT__FINISH      0xFF

#define FM_SENDER_NO_BUFFER         0xFF
#define FM_SENDER_BUFFSIZE_FREE_REQ 0xFF

#define FM_SENDER_DURATION_ONE_BIT   400
#define FM_SENDER_ONE_BIT_FREQ      (1000000/400)

#define FM_SENDER_DURATION_PREPARE_HIGH   (2)
#define FM_SENDER_DURATION_PREPARE_LOW    (3)
#define FM_SENDER_DURATION_PREAMBLE_HIGH  (1)
#define FM_SENDER_DURATION_PREAMBLE_LOW   (31)
#define FM_SENDER_DURATION_BIT_1_HIGH     (4)
#define FM_SENDER_DURATION_BIT_1_LOW      (1)
#define FM_SENDER_DURATION_BIT_0_HIGH     (1)
#define FM_SENDER_DURATION_BIT_0_LOW      (4)
#define FM_SENDER_DURATION_LAST_SYMB_HIGH (1)
#define FM_SENDER_DURATION_LAST_SYMB_LOW  (1)

#define FM_SENDER_GET_BUFFER(index)        (((index) == 0) ? fm_sending_buffer_1      : fm_sending_buffer_2);
#define FM_SENDER_GET_BUFFER_SIZE(index)   (((index) == 0) ? fm_sending_buffer_1_size : fm_sending_buffer_2_size);

#define FM_SENDER_PRINT_AIR_IN_USE true

volatile uint8_t fm_sender_next_bit = FM_SENDING_BIT__PREPARE;
volatile uint8_t fm_sending_buffer_1_size = 0;
volatile uint8_t fm_sending_buffer_2_size = 0;
volatile uint8_t * fm_sending_buffer_1 = NULL;
volatile uint8_t * fm_sending_buffer_2 = NULL;
volatile uint8_t fm_sending_buffer_current = FM_SENDER_NO_BUFFER;

volatile uint8_t fm_sender_high_counter = 0;
volatile uint8_t fm_sender_low_counter = 0;

void isr_fm_sender_switch_sending_buffer();

ISR (TIMER2_COMPA_vect) {
  if (fm_sending_buffer_current != FM_SENDER_NO_BUFFER) {
    if (fm_sender_high_counter > 0) {
      digitalWrite(FM_SENDER_PIN, HIGH);
      fm_sender_high_counter--;  
      return;
    }

    if (fm_sender_low_counter > 0) {
      digitalWrite(FM_SENDER_PIN, LOW);
      fm_sender_low_counter--;

      if (fm_sender_low_counter != 0) {
        return;
      }
    }

    if (fm_sender_next_bit == FM_SENDING_BIT__PREPARE) {
      fm_sender_high_counter = FM_SENDER_DURATION_PREPARE_HIGH;
      fm_sender_low_counter  = FM_SENDER_DURATION_PREPARE_LOW;
      fm_sender_next_bit     = FM_SENDING_BIT__PREAMBLE;
      return;
    } else if (fm_sender_next_bit == FM_SENDING_BIT__PREAMBLE) {
      fm_sender_high_counter = FM_SENDER_DURATION_PREAMBLE_HIGH;
      fm_sender_low_counter  = FM_SENDER_DURATION_PREAMBLE_LOW;
      fm_sender_next_bit     = 0;
      return;
    } else if (fm_sender_next_bit != FM_SENDING_BIT__FINISH) {
      uint8_t * buffer = FM_SENDER_GET_BUFFER(fm_sending_buffer_current);
      uint8_t size = FM_SENDER_GET_BUFFER_SIZE(fm_sending_buffer_current);

      if (size != FM_SENDER_BUFFSIZE_FREE_REQ && fm_sender_next_bit < size * 8) {
        if (bitRead(buffer[fm_sender_next_bit / 8], (7 - fm_sender_next_bit % 8)) != 0) {
          fm_sender_high_counter = FM_SENDER_DURATION_BIT_1_HIGH;
          fm_sender_low_counter = FM_SENDER_DURATION_BIT_1_LOW;
        } else {
          fm_sender_high_counter = FM_SENDER_DURATION_BIT_0_HIGH;
          fm_sender_low_counter = FM_SENDER_DURATION_BIT_0_LOW;
        }

        fm_sender_next_bit++;
        return;
      } else {
        fm_sender_high_counter = FM_SENDER_DURATION_LAST_SYMB_HIGH;
        fm_sender_low_counter = FM_SENDER_DURATION_LAST_SYMB_LOW;
        fm_sender_next_bit = FM_SENDING_BIT__FINISH;
        return;
      }
    } else {
      if (fm_sending_buffer_current == 0) { 
        fm_sending_buffer_1_size = FM_SENDER_BUFFSIZE_FREE_REQ; 
      } else { 
        fm_sending_buffer_2_size = FM_SENDER_BUFFSIZE_FREE_REQ; 
      }

      fm_sender_next_bit = FM_SENDING_BIT__PREPARE;
      fm_sending_buffer_current = FM_SENDER_NO_BUFFER;
    }
  }
}

void fm_sender_switch_sending_buffer() {
  if (fm_sending_buffer_current == FM_SENDER_NO_BUFFER) {
    if (fm_sending_buffer_1_size == FM_SENDER_BUFFSIZE_FREE_REQ) {
      if (fm_sending_buffer_1 != NULL) {
        free(fm_sending_buffer_1);
      }
      fm_sending_buffer_1 = NULL;
      fm_sending_buffer_1_size = 0;
    } 

    if (fm_sending_buffer_2_size == FM_SENDER_BUFFSIZE_FREE_REQ) {
      if (fm_sending_buffer_2 != NULL) {
        free(fm_sending_buffer_2);
      }
      fm_sending_buffer_2 = NULL;
      fm_sending_buffer_2_size = 0;
    } 
    
    if (fm_decoder_is_air_clean()) {
      if (fm_sending_buffer_1 != NULL) {
        fm_sending_buffer_current = 0;
      } else if (fm_sending_buffer_2 != NULL) {
        fm_sending_buffer_current = 1;
      }
    }
#if FM_SENDER_PRINT_AIR_IN_USE
    else if (
        (fm_sending_buffer_1 != NULL || fm_sending_buffer_2 != NULL) &&
        (fm_sending_buffer_current == FM_SENDER_NO_BUFFER)
    )
    {
      Serial.print("FM SENDER: await clean air. B1 = ");
      Serial.print((fm_sending_buffer_1 != NULL ? "Y" : "N"));
      Serial.print("; B2 = ");
      Serial.println((fm_sending_buffer_2 != NULL ? "Y" : "N"));
    }
#endif
  }
}

void fm_sender_init() {
  fm_sender_next_bit = FM_SENDING_BIT__PREPARE;
  fm_sending_buffer_1_size = 0;
  fm_sending_buffer_2_size = 0;
  fm_sending_buffer_1 = NULL;
  fm_sending_buffer_2 = NULL;
  fm_sending_buffer_current = FM_SENDER_NO_BUFFER;

  fm_sender_high_counter = 0;
  fm_sender_low_counter = 0;

  pinMode(FM_SENDER_PIN, OUTPUT);
  digitalWrite(FM_SENDER_PIN, LOW);

  TIMSK2 = 0;
  TCCR2A = 0;
  TCCR2B = 0;

  OCR2A = F_CPU / 32 / FM_SENDER_ONE_BIT_FREQ; 
  TCCR2A = _BV(WGM21);
  TCCR2B = _BV(CS21) | _BV(CS20);

  TIMSK2 = _BV(OCIE2A);
}

void fm_sender_on_main_loop() {
  fm_sender_switch_sending_buffer();
}

void fm_sender_send_command(const t_fm_command * command) {
  uint8_t * buffer = NULL;
  uint8_t size = 0;
  encrypter_process_memory(command, &buffer, &size);

  if (buffer == NULL) {
    Serial.print("FM SENDER: OOM: ADDR = ");
    Serial.print(command->address);
    Serial.print("; argsize = ");
    Serial.println(command->argssize);
    return;
  }

  uint8_t idx = 0;

  uint8_t oldSREG = SREG;
  cli();
  
  if (fm_sending_buffer_1 == NULL) {
    fm_sending_buffer_1 = buffer;
    fm_sending_buffer_1_size = size;
    buffer = NULL;
    idx = 0;
  } else if (fm_sending_buffer_2 == NULL) {
    fm_sending_buffer_2 = buffer;
    fm_sending_buffer_2_size = size;
    buffer = NULL;
    idx = 1;
  }
  
  SREG = oldSREG;

  if (buffer != NULL) {
    Serial.print("FM SENDER: OOB. Sending ");
    Serial.println(fm_sending_buffer_current);
    free(buffer);
  } else {
    Serial.print("Sended FM: ");
    Serial.print(command->address, HEX);
    Serial.print(" via buffer ");
    Serial.println(idx);
  }
}
