#ifndef FM_SENDER_H_
#define FM_SENDER_H_

#include "fm_command.h"

void fm_sender_init();
void fm_sender_send_command(const t_fm_command * command);
void fm_sender_on_main_loop();

#endif /* #define FM_SENDER_H_ */
