#ifndef MAIN_BUTTONS_BUTTON_DEF_H_
#define MAIN_BUTTONS_BUTTON_DEF_H_

#include "stdint.h"

#define BUTTON_ON_IDLE   			0x00
#define BUTTON_ON_KEY_DOWN 			0x01
#define BUTTON_ON_KEY_UP   			0x02
#define BUTTON_ON_CLICK   			0x03

typedef void (* button_callback_t)(uint8_t button1_state, uint8_t button2_state);

#endif /* MAIN_BUTTONS_BUTTON_DEF_H_ */
