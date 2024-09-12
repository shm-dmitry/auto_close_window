#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "stdint.h"

void controller_init();
void controller_on_main_loop();
void controller_on_charger_error(uint8_t err);

#endif /* #define CONTROLLER_H_ */
