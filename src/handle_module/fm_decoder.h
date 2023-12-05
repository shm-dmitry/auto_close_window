#ifndef FM_DECODER_H_
#define FM_DECODER_H_

#include "stdint.h"

void fm_decoder_init();
void isr_fm_decoder_on_symbol(uint16_t high, uint16_t low);
void fm_decoder_get_data(uint8_t ** buffer, uint8_t * buffer_size);
bool isr_fm_decoder_is_air_clean();

#endif /* #define FM_DECODER_H_ */
