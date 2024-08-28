#ifndef FM_COMMAND_H_
#define FM_COMMAND_H_

#define FM_COMMAND_SEND_MAX_ARGS_SIZE 2
#define FM_COMMAND_RECEIVE_MAX_ARGS_SIZE 1

#include "stdint.h"

typedef struct {
	uint16_t address;
	uint8_t arg1;
	uint8_t arg2;
	uint8_t argssize;
} t_fm_command;

#endif /* #define FM_COMMAND_H_ */
