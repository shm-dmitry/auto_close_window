#ifndef MAIN_FM_FM_COMMAND_ENCODER_H_
#define MAIN_FM_FM_COMMAND_ENCODER_H_

#include "fm_command_defs.h"
#include "driver/rmt_types.h"

typedef struct {
	t_fm_command * commands;
	uint8_t commands_size;
} t_fm_commands_list;

t_fm_commands_list * fm_command_decode(const rmt_rx_done_event_data_t *edata);
void fm_command_encode(t_fm_command * command, uint8_t ** out_buffer, uint8_t * out_buffer_size);
void rmt_new_ir_nec_encoder(rmt_encoder_handle_t *ret_encoder);

#endif /* MAIN_FM_FM_COMMAND_ENCODER_H_ */
