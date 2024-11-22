#ifndef MAIN_CONTROLLER_CONTROLLER_H_
#define MAIN_CONTROLLER_CONTROLLER_H_

#include "stdbool.h"
#include "../fm/fm_command_defs.h"
#include "controller_status_def.h"

void controller_process_command(uint16_t freq, const t_fm_command * command);
void controller_on_status(uint8_t status);
void controller_on_stepper_position_updated(uint8_t percent);
void controller_on_executor_allow_unlock(bool allowed);
void controller_init();
void controller_set_light_open_percent(uint8_t value);
void controller_set_fm_pdu_enabled(bool value);
void controller_publish_status();

#endif /* MAIN_CONTROLLER_CONTROLLER_H_ */
