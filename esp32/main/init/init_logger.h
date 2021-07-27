#ifndef MAIN_INIT_INIT_LOGGER_H_
#define MAIN_INIT_INIT_LOGGER_H_

#include "esp_err.h"

void init_logger_enable();

void init_logger_add_success(const char * message);

void init_logger_add_fail(const char * message, esp_err_t error);

void init_logger_dump_messages(const char * topic);

#define INIT_DRIVER_AND_LOG_OR_RETURN(driver_init_code, on_success_message, on_fail_message) \
	{ \
		esp_err_t err = driver_init_code; \
		if (err) { \
			init_logger_add_fail(on_fail_message, err); \
			return; \
		} else { \
			init_logger_add_success(on_success_message); \
		} \
	}

#endif /* MAIN_INIT_INIT_LOGGER_H_ */
