#define ENCRYPTER_PLAIN_TEMPERATURE_OFFSET 100
#define ENCRYPTER_NOT_ATTACHED_PIN         A3
#define ENCRYPTER_SENSOR_ID                0
#define ENCRYPTER_NEXT_RANDOM_BYTE         ((uint8_t)random(256))
#define ENCRYPTER_ENCODE_TEMPERATURE(t)    ((uint8_t)(t < ENCRYPTER_PLAIN_TEMPERATURE_OFFSET ? 0 : t + ENCRYPTER_PLAIN_TEMPERATURE_OFFSET))
#define ENCRYPTER_HIGH_BYTE(v)             ((uint8_t) (v / 0xFF))
#define ENCRYPTER_LOW_BYTE(v)              ((uint8_t) (v % 0xFF))

// FIXME: this is test key. 
// Replace it when build final firmware
#define ENCRYPTER_KEY(index, save_to) { \
    uint8_t __key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 }; \
    save_to = __key[*index]; \
    if (*index >= 6) { \
      *index = 0; \
    } else { \
      *index = *index + 1; \
    } \
  }
  

void encrypter_init() {
  randomSeed(analogRead(ENCRYPTER_NOT_ATTACHED_PIN));
}

uint8_t encrypter_encrypt_one_byte(uint8_t prev_byte_3, uint8_t prev_byte_2, uint8_t prev_byte_1, uint8_t * key_index, uint8_t next_byte) {
  uint8_t key_byte = 0;
  ENCRYPTER_KEY(key_index, key_byte);

  return prev_byte_3 ^ prev_byte_2 ^ prev_byte_1 ^ key_byte ^ next_byte;
}

void encrypter_do_encryption(int8_t temperature, uint16_t tvoc, const noise_data_t * noise, uint8_t ** out_buffer, uint8_t * out_buffer_size) {
  // plain buffer:
  // byte[0] == unsigned byte value: temperature + ENCRYPTER_PLAIN_TEMPERATURE_OFFSET
  // byte[1] == tvoc
  // byte[2] == tvoc
  // byte[3] == noise_count
  // byte[4] == noise_freq_0
  // byte[5] == noise_freq_0
  // byte[6] == noise_volume_0
  // byte[7] == noise_volume_0
  // byte[8] == noise_freq_1
  // byte[9] == noise_freq_1
  // byte[10] == noise_volume_1
  // byte[11] == noise_volume_1
  // .......

  // encrypted buffer:
  // --- start of plain header ---
  // byte[0] == SENSOR_ID
  // byte[1] == SALT_BYTE_1
  // byte[2] == SALT_BYTE_2
  // --- start of encrypted message ---
  // byte[3] == ENCRYPTED_SALT_BYTE_3
  // byte[4] == ENCRYPTED_DATA_BYTE_1
  // byte[5] == ENCRYPTED_DATA_BYTE_2
  // ....

  // work in stream-mode, dont dublicate buffers...
  *out_buffer_size = (uint8_t) ((3 + 1) + (1 + 2) + (noise != NULL ? (noise->count * 4 + 1) : 1));
  *out_buffer = malloc(*out_buffer_size);
  *out_buffer[0] = ENCRYPTER_SENSOR_ID;
  *out_buffer[1] = ENCRYPTER_NEXT_RANDOM_BYTE;
  *out_buffer[2] = ENCRYPTER_NEXT_RANDOM_BYTE;

  uint8_t key_index = 0;
  *out_buffer[3] = encrypter_encrypt_one_byte(*out_buffer[0], *out_buffer[1], *out_buffer[2], &key_index, ENCRYPTER_NEXT_RANDOM_BYTE);
  *out_buffer[4] = encrypter_encrypt_one_byte(*out_buffer[1], *out_buffer[2], *out_buffer[3], &key_index, ENCRYPTER_ENCODE_TEMPERATURE(temperature));
  *out_buffer[5] = encrypter_encrypt_one_byte(*out_buffer[2], *out_buffer[3], *out_buffer[4], &key_index, ENCRYPTER_HIGH_BYTE(tvoc));
  *out_buffer[6] = encrypter_encrypt_one_byte(*out_buffer[3], *out_buffer[4], *out_buffer[5], &key_index, ENCRYPTER_LOW_BYTE(tvoc));
  *out_buffer[7] = encrypter_encrypt_one_byte(*out_buffer[4], *out_buffer[5], *out_buffer[6], &key_index, (noise == NULL ? 0 : noise->count));
  if (noise != NULL) {
    for (uint8_t i = 0; i<noise->count; i++) {
      *out_buffer[8 + i * 4] = encrypter_encrypt_one_byte(*out_buffer[5 + i * 4], *out_buffer[6 + i * 4], *out_buffer[7 + i * 4], &key_index, ENCRYPTER_HIGH_BYTE(noise->freq[i]));
      *out_buffer[9 + i * 4] = encrypter_encrypt_one_byte(*out_buffer[6 + i * 4], *out_buffer[7 + i * 4], *out_buffer[8 + i * 4], &key_index, ENCRYPTER_LOW_BYTE(noise->freq[i]));
      *out_buffer[10 + i * 4] = encrypter_encrypt_one_byte(*out_buffer[7 + i * 4], *out_buffer[8 + i * 4], *out_buffer[9 + i * 4], &key_index, ENCRYPTER_HIGH_BYTE(noise->volume[i]));
      *out_buffer[11 + i * 4] = encrypter_encrypt_one_byte(*out_buffer[8 + i * 4], *out_buffer[9 + i * 4], *out_buffer[10 + i * 4], &key_index, ENCRYPTER_LOW_BYTE(noise->volume[i]));
    }
  }
}
