#ifndef MAIN_FM_SENDER_FM_SENDER_H_
#define MAIN_FM_SENDER_FM_SENDER_H_

#include "fm_command_defs.h"

void fm_sender_init();
void fm_sender_send(const t_fm_command * command);

#endif /* MAIN_FM_SENDER_FM_SENDER_H_ */
