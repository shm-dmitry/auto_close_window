#ifndef MAIN_FM_FM_CRYPTER_H_
#define MAIN_FM_FM_CRYPTER_H_

#include "fm_command_defs.h"
#include "stdbool.h"

bool fm_crypter_decrypt(t_fm_command * command);
void fm_crypter_encrypt(t_fm_command * command);

#endif /* MAIN_FM_FM_CRYPTER_H_ */
