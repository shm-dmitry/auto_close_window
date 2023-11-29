#ifndef MAIN_FM_FM_COMMAND_DEFS_H_
#define MAIN_FM_FM_COMMAND_DEFS_H_

#include "stdint.h"

#define FM_COMMAND_ARG_MAXSIZE 10

#define FM_COMMAND_PROTOCOL_NEC 0x01
#define FM_COMMAND_PROTOCOL_EXTENDED 0x02

#define FM_COMMAND_ADDRESS_BITES(protocol) ((protocol == FM_COMMAND_PROTOCOL_NEC) ? 16 : (8 * FM_COMMAND_ARG_MAXSIZE))

typedef struct {
	uint8_t protocol;
	uint16_t command;
	uint8_t args[FM_COMMAND_ARG_MAXSIZE];
} t_fm_command;

#endif /* MAIN_FM_FM_COMMAND_DEFS_H_ */
