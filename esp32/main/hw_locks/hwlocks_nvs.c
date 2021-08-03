#include "hwlocks_nvs.h"

#include "../init/nvs_rw.h"

#define HWLOCKS_CONFIG_NAME "hwlocks_softlock"

bool hwlocks_nvs_read_soft_lock_state() {
	uint8_t * buffer = NULL;
	size_t buffer_size = 0;

	if (nvs_read_buffer(HWLOCKS_CONFIG_NAME, &buffer, &buffer_size)) {
		return true;
	}

	if (buffer) {
		bool state = true;
		if (buffer_size == 1) {
			state = buffer[0] == 1;
		}

		free(buffer);

		return state;
	} else {
		return true;
	}
}

void hwlocks_nvs_save_softlock_state(bool value) {
	uint8_t buffer = value;
	nvs_write_buffer(HWLOCKS_CONFIG_NAME, &buffer, 1);
}
