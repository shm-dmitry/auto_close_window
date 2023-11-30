#ifndef MAIN_FM_FM_COMMAND_ADDRESSES_H_
#define MAIN_FM_FM_COMMAND_ADDRESSES_H_

#include "stdint.h"
#include "stdbool.h"

#define FM_VAL_BY_ADDRESS_UNKNOWN 0x00

typedef union {
	struct {
		bool encrypted : 1;
		uint8_t args_size : 7;
	};
	uint8_t val;
} t_fm_command_address_data;


t_fm_command_address_data fm_command_metadata_by_address(uint16_t address);

#endif /* MAIN_FM_FM_COMMAND_ADDRESSES_H_ */
