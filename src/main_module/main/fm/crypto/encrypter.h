#ifndef MAIN_FM_CRYPTO_ENCRYPTER_H_
#define MAIN_FM_CRYPTO_ENCRYPTER_H_

#include "stdint.h"
#include "stdbool.h"

void encrypter_init();
void encrypter_process_memory(uint16_t * seed, uint8_t * buff, uint8_t size);

bool decrypter_process_memory(uint16_t * seed, uint8_t * buff, uint8_t size);

#endif /* MAIN_FM_CRYPTO_ENCRYPTER_H_ */
