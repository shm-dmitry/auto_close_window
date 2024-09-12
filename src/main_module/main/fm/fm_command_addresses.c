#include "fm_command_addresses.h"

#include "fm_command_address_def.h"

typedef struct {
	uint16_t address;
	t_fm_command_address_data data;
} t_fm_command_size_by_address_data;

#define FM_COMMAND_ADDRESS_DATA_SIZE 11
t_fm_command_size_by_address_data address_data[FM_COMMAND_ADDRESS_DATA_SIZE] =
{
		{ .address = FM_COMMAND_ADDRESS__PDU1,               .data.encrypted = false, .data.args_size = 1 },
		{ .address = FM_COMMAND_ADDRESS__PDU2,               .data.encrypted = false, .data.args_size = 1 },

		{ .address = FM_COMMAND_ADDRESS__MM_STEPPER_STATUS, .data.encrypted = true,  .data.args_size = 1 },

		{ .address = FM_COMMAND_ADDRESS__OM_ALARM,          .data.encrypted = true,  .data.args_size = 1 },
		{ .address = FM_COMMAND_ADDRESS__OM_AIR_STATUS,     .data.encrypted = true,  .data.args_size = 5 },
		{ .address = FM_COMMAND_ADDRESS__OM_NOISE_DATA,     .data.encrypted = true,  .data.args_size = 10 },
		{ .address = FM_COMMAND_ADDRESS__OM_CHARGE_STATUS,  .data.encrypted = true,  .data.args_size = 1 },

		{ .address = FM_COMMAND_ADDRESS__HM_COMMAND,        .data.encrypted = true,  .data.args_size = 1 },
		{ .address = FM_COMMAND_ADDRESS__HM_CHARGE_STATUS,  .data.encrypted = true,  .data.args_size = 1 },
		{ .address = FM_COMMAND_ADDRESS__HM_CHARGE_ERROR,   .data.encrypted = true,  .data.args_size = 1 },
		{ .address = FM_COMMAND_ADDRESS__HM_BAT_STATUS,     .data.encrypted = true,  .data.args_size = 2 },
};

t_fm_command_address_data address_unknown = { .val = FM_VAL_BY_ADDRESS_UNKNOWN };

t_fm_command_address_data fm_command_metadata_by_address(uint16_t address) {
	for (uint8_t i = 0; i<FM_COMMAND_ADDRESS_DATA_SIZE; i++) {
		if (address_data[i].address == address) {
			return address_data[i].data;
		}
	}

	return address_unknown;
}
