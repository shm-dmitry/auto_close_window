#ifndef MAIN_FM_FM_CRYPTER_KEY_H_
#define MAIN_FM_FM_CRYPTER_KEY_H_

#if __has_include("fm_crypter_private.h")

#pragma message "OK :: Used fm_crypter_private.h for initializing private defines"

#include "fm_crypter_private.h"

#else

#pragma message "WARNING! Used public defines. Create 'fm_crypter_private.h' file and put same defines with your personal values into it"

#define FM_CRYPTER_COMMAND_KEY 0x1234
#define FM_CRYPTER_ARG_KEY { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA }

#endif

#endif /* MAIN_FM_FM_CRYPTER_KEY_H_ */
