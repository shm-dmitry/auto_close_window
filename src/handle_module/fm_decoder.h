#ifndef FM_DECODER_H_
#define FM_DECODER_H_

#include "stdint.h"

void isr_fm_decoder_on_symbol(uint16_t high, uint16_t low);
void isr_fm_decoder_reset();

void fm_decoder_init();
void fm_decoder_get_data(uint8_t ** buffer, uint8_t * buffer_size);
bool fm_decoder_is_air_clean();

void fm_decoder_on_main_loop();

#endif /* #define FM_DECODER_H_ */
