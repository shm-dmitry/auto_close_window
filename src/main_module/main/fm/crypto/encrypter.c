#include "encrypter.h"
#include "encrypter_secret.h"
#include "esp_random.h"

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

void encrypter_process_memory(uint16_t * seed, uint8_t * buff, uint8_t size) {
	encrypter_reset();

	*seed = (encrypter_next(encrypter_next_random()) << 8);
	*seed = *seed + encrypter_next(encrypter_next_random());
	for (uint8_t i = 0; i<size - 1; i++) {
		buff[i] = encrypter_next(buff[i]);
	}
	buff[size - 1] = encrypter_next_crc();
}

bool decrypter_process_memory(uint16_t * seed, uint8_t * buff, uint8_t size) {
	decrypter_reset();

	uint16_t sd = decrypter_next(*seed >> 8) << 8;
	sd += decrypter_next(*seed % 256);

	*seed = sd;

	for (uint8_t i = 0; i<size - 1; i++) {
		buff[i] = decrypter_next(buff[i]);
	}

	uint8_t crc = decrypter_get_crc();
	buff[size - 1] = decrypter_next(buff[size - 1]);

	return crc == buff[size - 1];
}
