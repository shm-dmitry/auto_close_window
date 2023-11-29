#include "fm_crypter.h"

#include "fm_crypter_key.h"
#include "esp_random.h"

bool fm_crypter_decrypt(t_fm_command * command) {
	if (command->protocol == FM_COMMAND_PROTOCOL_EXTENDED) {
		command->command ^= FM_CRYPTER_COMMAND_KEY;

		uint8_t crc = (command->command >> 8) + 3 * (command->command / 0xFF);
		uint8_t salt = crc;

		uint8_t key[FM_COMMAND_ARG_MAXSIZE] = FM_CRYPTER_ARG_KEY;
		for (uint8_t i = 0; i<FM_COMMAND_ARG_MAXSIZE; i++) {
			command->args[i] ^= key[i];
			command->args[i] ^= salt;
			if (i != (FM_COMMAND_ARG_MAXSIZE - 1)) {
				if (i % 2 == 0) {
					crc += command->args[i];
				} else {
					crc += 3 * command->args[i];
				}
			}
		}

		if (command->args[FM_COMMAND_ARG_MAXSIZE - 1] != crc) {
			return false;
		} else {
			return true;
		}
	} else {
		return true;
	}
}

void fm_crypter_encrypt(t_fm_command * command) {
	if (command->protocol == FM_COMMAND_PROTOCOL_NEC) {
		return;
	}

	command->command = (uint16_t) esp_random();

	uint8_t crc = (command->command >> 8) + 3 * (command->command / 0xFF);
	uint8_t salt = crc;

	command->command ^= FM_CRYPTER_COMMAND_KEY;
	uint8_t key[FM_COMMAND_ARG_MAXSIZE] = FM_CRYPTER_ARG_KEY;

	for (uint8_t i = 0; i<FM_COMMAND_ARG_MAXSIZE - 1; i++) {
		command->args[i] ^= key[i];
		command->args[i] ^= salt;

		if (i % 2 == 0) {
			crc += command->args[i];
		} else {
			crc += 3 * command->args[i];
		}
	}

	command->args[FM_COMMAND_ARG_MAXSIZE - 1] = crc;
	command->args[FM_COMMAND_ARG_MAXSIZE - 1] ^= key[FM_COMMAND_ARG_MAXSIZE - 1];
	command->args[FM_COMMAND_ARG_MAXSIZE - 1] ^= salt;
}
