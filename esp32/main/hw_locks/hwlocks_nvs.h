#ifndef MAIN_HW_LOCKS_HWLOCKS_NVS_H_
#define MAIN_HW_LOCKS_HWLOCKS_NVS_H_

#include "stdbool.h"

bool hwlocks_nvs_read_soft_lock_state();

void hwlocks_nvs_save_softlock_state(bool value);

#endif /* MAIN_HW_LOCKS_HWLOCKS_NVS_H_ */
