#include "string.h"

#define GPIO_LOGGER_SEND_DATA_PIN             PIN_PD0
#define GPIO_LOGGER_BYTE2BYTE_DELAY           delay(30)
#define GPIO_LOGGER_INTRABYTE_DELAY           delayMicroseconds(300)

void gpio_logger_init() {
  pinMode(GPIO_LOGGER_SEND_DATA_PIN, OUTPUT);
  digitalWrite(GPIO_LOGGER_SEND_DATA_PIN,  LOW);

  GPIO_LOGGER_BYTE2BYTE_DELAY;
}

void gpio_logger_do_send_message(const char * message, int len) {
  for (int i = 0; i < len; i++) {
    uint8_t data_char = ((uint8_t) message[i]);
    for (uint8_t j = 0; j < data_char; j++) {
      digitalWrite(GPIO_LOGGER_SEND_DATA_PIN,  HIGH);
      GPIO_LOGGER_INTRABYTE_DELAY;

      digitalWrite(GPIO_LOGGER_SEND_DATA_PIN,  LOW);
      GPIO_LOGGER_INTRABYTE_DELAY;
    }

    GPIO_LOGGER_BYTE2BYTE_DELAY;
  }
}

void gpio_logger_send_message(const char * message, ...) {
  // calculate buffer size
  char c;
  va_list args;
  va_start(args, message);
  int buffersize = vsnprintf(&c, 1, message, args);
  va_end(args);

  if (buffersize <= 0) {
    gpio_logger_do_send_message(message, strlen(message));
    return;
  }
  
  char * buff = malloc(buffersize + 1);
  if (buff) {
    va_list args;
    va_start(args, message);
    vsnprintf(buff, buffersize + 1, message, args);
    va_end(args);

    int len = strlen(buff);
    buff[len] = '\n';
    buff[len + 1] = 0;

    len++;

    gpio_logger_do_send_message(buff, len);

    free(buff);
  } else {
    gpio_logger_do_send_message(message, strlen(message));
  }
}
