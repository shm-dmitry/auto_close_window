#ifndef POWER_MANAGER_H_
#define POWER_MANAGER_H_

#include "stdint.h"

void power_manager_init();
bool power_manager_is_charging();
void power_manager_on_event();
void power_manager_on_main_loop();
void power_manager_read_batstatus(uint16_t & voltage_mv, int16_t & current_ma);

#endif /* #define POWER_MANAGER_H_ */
