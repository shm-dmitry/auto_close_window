#ifndef POWER_MANAGER_H_
#define POWER_MANAGER_H_

void power_manager_init();
bool power_manager_is_charging();
void power_manager_on_event();
void power_manager_on_main_loop();

#endif /* #define POWER_MANAGER_H_ */
