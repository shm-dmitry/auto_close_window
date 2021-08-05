#include <RCSwitch.h>
#include "string.h"

RCSwitch radio = RCSwitch();

void wire_logger_init(){
  radio.enableTransmit(12);
  radio.setProtocol(5);
//  radio.setRepeatTransmit(15);
}

void wire_logger_send(const char * data){
  char * tmp = malloc(strlen(data) + 2);
  strcpy(tmp, data);
  tmp[strlen(data)] = '\n';
  tmp[strlen(data) + 1] = 0;
  
    int len = strlen(tmp);
    for (int i = 0; i<len; i+=3) {
      radio.send(0xFEFEFE, 24);

      unsigned long sent = 0;
      for (int j = i; j<i + 3 && j < len; j++) {
         sent = (sent << 8) + tmp[j];
      }
      radio.send(sent, 24);
    }

    free(tmp);
}
