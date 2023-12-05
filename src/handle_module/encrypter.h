#ifndef ENCRYPTER_H_
#define ENCRYPTER_H_

#include "fm_command.h"
#include "stdint.h"

void encrypter_init();

void encrypter_process_memory(const t_fm_command * command, uint8_t ** out_buff, uint8_t * out_buff_size);
t_fm_command * decrypter_process_memory(uint16_t address, const uint8_t * buff, uint8_t size);
uint8_t decryptor_args_size_to_buff_size(uint8_t args_size);


#endif /* #define ENCRYPTER_H_ */
