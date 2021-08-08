#include <RCSwitch.h>
#include "string.h"

RCSwitch radio = RCSwitch();

void wire_logger_init(){
  radio.enableTransmit(12);
  radio.setProtocol(5);
//  radio.setRepeatTransmit(7);
}

void wire_logger_send(const char * message, ...){
    char * buff = malloc(strlen(message) + 1024);
    va_list args;
    va_start(args, message);
    vsnprintf(buff, strlen(message) + 1024 - 1, message, args);
    va_end(args);

    int len = strlen(buff);
    buff[len] = '\n';
    buff[len + 1] = 0;

    len++;
    
    for (int i = 0; i<len; i+=3) {
      radio.send(0xFEFEFE, 24);

      unsigned long sent = 0;
      for (int j = i; j<i + 3 && j < len; j++) {
         sent = (sent << 8) + buff[j];
      }
      radio.send(sent, 24);
    }

    free(buff);
}
