#ifndef MAIN_CONTROLLER_CONTROLLER_H_
#define MAIN_CONTROLLER_CONTROLLER_H_

#include "../fm/fm_command_defs.h"
#include "controller_status_def.h"

void controller_process_command(const t_fm_command * command);
void controller_on_status(uint8_t status);
void controller_on_stepper_position_updated(uint8_t percent);

#endif /* MAIN_CONTROLLER_CONTROLLER_H_ */
