#include "encrypter.h"
#include "encrypter_secret.h"
#include "esp_random.h"
#include "string.h"
#include "../../log/log.h"

uint8_t encrypter_send_key_offset = 0;
uint8_t encrypter_byte_1 = 0;
uint8_t encrypter_byte_2 = 0;
uint8_t encrypter_crc = 0;

uint8_t decrypter_send_key_offset = 0;
uint8_t decrypter_byte_1 = 0;
uint8_t decrypter_byte_2 = 0;
uint8_t decrypter_crc = 0;

uint8_t crypter_secret[ENCRYPTER_SECRET_KEY_SIZE] = ENCRYPTER_SECRET_KEY;

void encrypter_reset();

void encrypter_init() {
	encrypter_reset();
	// TOOD: AVR: dont forget init random in AVR
}

void encrypter_reset() {
  encrypter_send_key_offset = 0;
  encrypter_byte_1 = 0;
  encrypter_byte_2 = 0;
  encrypter_crc = 0;
}

uint8_t encrypter_next_random() {
  return esp_random();
}

uint8_t encrypter_next(uint8_t value) {
  encrypter_crc += value;

  if (encrypter_send_key_offset >= ENCRYPTER_SECRET_KEY_SIZE) {
    encrypter_send_key_offset = 0;
  }

  uint8_t result = value ^ encrypter_byte_1 ^ encrypter_byte_2 ^ crypter_secret[encrypter_send_key_offset++];
  encrypter_byte_1 = encrypter_byte_2;
  encrypter_byte_2 = value;
  return result;
}

uint8_t encrypter_next_crc() {
	return encrypter_next(encrypter_crc);
}


void decrypter_reset() {
	decrypter_send_key_offset = 0;
	decrypter_byte_1 = 0;
	decrypter_byte_2 = 0;
	decrypter_crc = 0;
}

uint8_t decrypter_next(uint8_t value) {
	if (decrypter_send_key_offset >= ENCRYPTER_SECRET_KEY_SIZE) {
		decrypter_send_key_offset = 0;
	}

	value = value ^ decrypter_byte_1 ^ decrypter_byte_2 ^ crypter_secret[decrypter_send_key_offset++];
	decrypter_byte_1 = decrypter_byte_2;
	decrypter_byte_2 = value;

	decrypter_crc += value;

	return value;
}

uint8_t decrypter_get_crc() {
	return decrypter_crc;
}

void encrypter_process_memory(const t_fm_command * command, uint8_t ** out_buffer, uint8_t * out_buffer_size) {
	*out_buffer_size = command->args_size + 2 + 2 + 1;
	*out_buffer = malloc(*out_buffer_size);
	if (*out_buffer == NULL) {
		*out_buffer_size = 0;
		return;
	}

	memset(*out_buffer, 0, *out_buffer_size);

	encrypter_reset();
	(*out_buffer)[0] = command->address >> 8;
	(*out_buffer)[1] = command->address % 256;

	(*out_buffer)[2] = encrypter_next(encrypter_next_random());
	(*out_buffer)[3] = encrypter_next(encrypter_next_random());

	for (uint8_t i = 0; i<command->args_size; i++) {
		(*out_buffer)[4 + i] = encrypter_next(command->args[i]);
	}

	(*out_buffer)[4 + command->args_size] = encrypter_next_crc();
}

uint8_t decryptor_args_size_to_buff_size(uint8_t args_size) {
	return args_size + 3;
}

t_fm_command * decrypter_process_memory(uint16_t address, const uint8_t * buff, uint8_t size) {
	decrypter_reset();

	if (size <= 3) {
		return NULL;
	}

	if (size - 3 > FM_COMMAND_MAX_ARGS_SIZE) {
		return NULL;
	}

	uint8_t * args = malloc(size - 3);
	if (args == NULL) {
		return NULL;
	}

	decrypter_next(buff[0]); // salt1
	decrypter_next(buff[1]); // salt2

	for (uint8_t i = 0; i<size - 3; i++) {
		args[i] = decrypter_next(buff[2 + i]);
	}

	uint8_t calculated_crc = decrypter_get_crc();
	uint8_t actual_crc = decrypter_next(buff[size - 1]);
	if (actual_crc != calculated_crc) {
		_ESP_LOGE(LOG_ENCRYPTOR, "BAD CRC calculated %d, actual: %d. Buffer: [ %02X %02X %02X %02X ]",
				calculated_crc,
				actual_crc,
				buff[0],
				buff[1],
				buff[2],
				buff[3]);
		free(args);
		return NULL;
	}

	t_fm_command * out_command = malloc(sizeof(t_fm_command));
	if (out_command == NULL) {
		free(args);
		return NULL;
	}

	memset(out_command, 0, sizeof(t_fm_command));

	out_command->address = address;
	out_command->args_size = size - 3;
	memcpy(out_command->args, args, out_command->args_size);

	free(args);
	args = NULL;

	return out_command;
}

