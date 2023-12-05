#ifndef FM_COMMAND_H_
#define FM_COMMAND_H_

#define FM_COMMAND_MAX_ARGS_SIZE 1

#include "stdint.h"

typedef struct {
	uint16_t address;
	uint8_t arg;
} t_fm_command;

#endif /* #define FM_COMMAND_H_ */
