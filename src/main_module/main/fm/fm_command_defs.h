#ifndef MAIN_FM_FM_COMMAND_DEFS_H_
#define MAIN_FM_FM_COMMAND_DEFS_H_

#include "stdint.h"

#define FM_COMMAND_MAX_ARGS_SIZE 10

typedef struct {
	uint16_t address;
	uint8_t args[FM_COMMAND_MAX_ARGS_SIZE];
	uint8_t args_size;
} t_fm_command;

#endif /* MAIN_FM_FM_COMMAND_DEFS_H_ */
