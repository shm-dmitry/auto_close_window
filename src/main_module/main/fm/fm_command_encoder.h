#ifndef MAIN_FM_FM_COMMAND_ENCODER_H_
#define MAIN_FM_FM_COMMAND_ENCODER_H_

#include "fm_command_defs.h"
#include "driver/rmt_types.h"

bool fm_command_decode(const rmt_rx_done_event_data_t *edata, t_fm_command * result);
void fm_command_encode(t_fm_command * result);
void rmt_new_ir_nec_encoder(uint32_t resolution, rmt_encoder_handle_t *ret_encoder);

#endif /* MAIN_FM_FM_COMMAND_ENCODER_H_ */
