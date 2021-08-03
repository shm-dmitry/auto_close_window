#ifndef MAIN_HW_LOCKS_HW_LOCKS_API_H_
#define MAIN_HW_LOCKS_HW_LOCKS_API_H_

#include "esp_err.h"
#include "stdbool.h"

#define HWLOCK_STATE_OK       0b00000000
#define HWLOCK_STATE_HALL     0b00000001
#define HWLOCK_STATE_SWITCH   0b00000010
#define HWLOCK_STATE_SOFTLOCK 0b00000100

esp_err_t hwlocks_init(int gpio_hall, int gpio_switch, int gpio_softlock, const char * softlock_topic, const char * status_topic);

esp_err_t hwlocks_softlock_set(bool on);

uint8_t hwlocks_read();

#endif /* MAIN_HW_LOCKS_HW_LOCKS_API_H_ */
