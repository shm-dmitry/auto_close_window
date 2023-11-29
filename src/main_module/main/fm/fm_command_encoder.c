#include "fm_command_encoder.h"

// we decode NEC protocol to use remote-control-units, and extended protocol (NEC-based) to transfer more data

// this code based on https://github.com/espressif/esp-idf/blob/master/examples/peripherals/rmt/ir_nec_transceiver

#include "crypto/encrypter.h"
#include "driver/rmt_encoder.h"
#include "string.h"
#include "esp_err.h"
#include "../log/log.h"
#include "stdbool.h"

typedef struct {
    rmt_encoder_t base;           // the base "class", declares the standard encoder interface
    rmt_encoder_t *copy_encoder;  // use the copy_encoder to encode the leading and ending pulse
    rmt_encoder_t *bytes_encoder; // use the bytes_encoder to encode the address and command data
    rmt_symbol_word_t nec_leading_symbol; // NEC leading code with RMT representation
    rmt_symbol_word_t ext_leading_symbol; // NEC leading code with RMT representation
    rmt_symbol_word_t nec_ending_symbol;  // NEC ending code with RMT representation
    int state;
} rmt_fm_nec_encoder_t;

typedef struct {
	bool found_preamble;

	uint8_t * buffer;
	uint8_t buffer_pointer;
	uint8_t buffer_size;

	uint16_t prev_duration;
} t_fm_encoder_context;

void fm_command_decode_next_period(uint8_t level, uint16_t duration, t_fm_encoder_context * context) {
	if (!context->found_preamble) {
		if (level == 0 && context->prev_duration == 0) {
			return;
		}

		if (level == 1 && context->prev_duration == 0) {
			context->prev_duration = duration;
			return;
		}

		if (level == 0) {
			if (duration / context->prev_duration > 25) {
				context->found_preamble = true;
			}
		}

		context->prev_duration = duration;
		return;
	}

	if (level == 1) {
		context->prev_duration = duration;
		return;
	}

	if (duration / context->prev_duration >= 2 && duration / context->prev_duration <= 5) {
		context->buffer[context->buffer_pointer] = 1;
		context->buffer_pointer++;
	} else if (context->prev_duration / duration >= 2 && context->prev_duration / duration <= 5) {
		context->buffer[context->buffer_pointer] = 0;
		context->buffer_pointer++;
	} else {
		ESP_LOGW(LOG_FM_ENCODER, "Reset encoder, bad duration %d; prev %d", duration, context->prev_duration);
		context->found_preamble = false;
	}

	context->prev_duration = duration;
}

bool fm_command_decode(const rmt_rx_done_event_data_t *edata, t_fm_command * result) {
	if (edata->num_symbols == 0 || edata->num_symbols > 0xFFFF) {
		return false;
	}

	if (edata->num_symbols < 10) {
		return false;
	}

	t_fm_encoder_context * context = malloc(sizeof(t_fm_encoder_context));
	memset(context, 0, sizeof(t_fm_encoder_context));
	context->buffer = malloc(24);
	context->buffer_size = 24;

	for (uint16_t i = 0; i<edata->num_symbols; i++) {
		if (edata->received_symbols[i].duration0 == 0 || edata->received_symbols[i].duration1 == 0) {
			continue;
		}


		if (context->buffer_pointer == context->buffer_size) {
			break;
		}

		fm_command_decode_next_period(edata->received_symbols[i].level0, edata->received_symbols[i].duration0, context);
		fm_command_decode_next_period(edata->received_symbols[i].level1, edata->received_symbols[i].duration1, context);
	}

	for (uint8_t i = 0; i< context->buffer_pointer; i++) {
		ESP_LOGI(LOG_FM_ENCODER, "#%d = %d", i, context->buffer[i]);
	}

	free(context->buffer);
	context->buffer = NULL;
	free(context);

	return false;

    return decrypter_process_memory(&(result->command), result->args, FM_COMMAND_ARG_MAXSIZE);
}

static size_t fm_isr_rmt_encode_nec(rmt_encoder_t *encoder, rmt_channel_handle_t channel, const void *primary_data, size_t data_size, rmt_encode_state_t *ret_state)
{
	rmt_fm_nec_encoder_t *nec_encoder = __containerof(encoder, rmt_fm_nec_encoder_t, base);
    rmt_encode_state_t session_state = RMT_ENCODING_RESET;
    rmt_encode_state_t state = RMT_ENCODING_RESET;
    size_t encoded_symbols = 0;
    t_fm_command *fm_command = (t_fm_command *)primary_data;
    rmt_encoder_handle_t copy_encoder = nec_encoder->copy_encoder;
    rmt_encoder_handle_t bytes_encoder = nec_encoder->bytes_encoder;

    if (nec_encoder->state == 0) {
		encoded_symbols += copy_encoder->encode(copy_encoder,
												channel,
												(
													fm_command->protocol == FM_COMMAND_PROTOCOL_NEC ?
															&nec_encoder->nec_leading_symbol :
															&nec_encoder->ext_leading_symbol
												),
												sizeof(rmt_symbol_word_t),
												&session_state);
        if (session_state & RMT_ENCODING_COMPLETE) {
            nec_encoder->state = 1; // we can only switch to next state when current encoder finished
        }
        if (session_state & RMT_ENCODING_MEM_FULL) {
            state |= RMT_ENCODING_MEM_FULL;
            goto out; // yield if there's no free space to put other encoding artifacts
        }
    }

    uint8_t size = FM_COMMAND_ADDRESS_BITES(fm_command->protocol);

    if (nec_encoder->state <= size) {
        encoded_symbols += bytes_encoder->encode(bytes_encoder,
        										 channel,
												 fm_command->args,
												 FM_COMMAND_ADDRESS_BITES(fm_command->protocol),
												 &session_state);
        if (session_state & RMT_ENCODING_COMPLETE) {
            nec_encoder->state = size; // we can only switch to next state when current encoder finished
        }
        if (session_state & RMT_ENCODING_MEM_FULL) {
            state |= RMT_ENCODING_MEM_FULL;
            goto out; // yield if there's no free space to put other encoding artifacts
        }
    }

    if (nec_encoder->state <= size + 2 ) {
        encoded_symbols += bytes_encoder->encode(bytes_encoder,
        										 channel,
												 &fm_command->command,
												 sizeof(uint16_t),
												 &session_state);
        if (session_state & RMT_ENCODING_COMPLETE) {
            nec_encoder->state = size + 2; // we can only switch to next state when current encoder finished
        }
        if (session_state & RMT_ENCODING_MEM_FULL) {
            state |= RMT_ENCODING_MEM_FULL;
            goto out; // yield if there's no free space to put other encoding artifacts
        }
    }

    encoded_symbols += copy_encoder->encode(copy_encoder, channel, &nec_encoder->nec_ending_symbol,
                                            sizeof(rmt_symbol_word_t), &session_state);
    if (session_state & RMT_ENCODING_COMPLETE) {
        nec_encoder->state = RMT_ENCODING_RESET; // back to the initial encoding session
        state |= RMT_ENCODING_COMPLETE;
    }
    if (session_state & RMT_ENCODING_MEM_FULL) {
        state |= RMT_ENCODING_MEM_FULL;
        goto out; // yield if there's no free space to put other encoding artifacts
    }

out:
    *ret_state = state;
    return encoded_symbols;
}

static esp_err_t fm_isr_rmt_del_encoder(rmt_encoder_t *encoder)
{
	rmt_fm_nec_encoder_t *nec_encoder = __containerof(encoder, rmt_fm_nec_encoder_t, base);
    rmt_del_encoder(nec_encoder->copy_encoder);
    rmt_del_encoder(nec_encoder->bytes_encoder);
    free(nec_encoder);
    return ESP_OK;
}

static esp_err_t fm_isr_rmt_reset_encoder(rmt_encoder_t *encoder)
{
	rmt_fm_nec_encoder_t *nec_encoder = __containerof(encoder, rmt_fm_nec_encoder_t, base);
    rmt_encoder_reset(nec_encoder->copy_encoder);
    rmt_encoder_reset(nec_encoder->bytes_encoder);
    nec_encoder->state = RMT_ENCODING_RESET;
    return ESP_OK;
}

void rmt_new_ir_nec_encoder(uint32_t resolution, rmt_encoder_handle_t *ret_encoder) {
    rmt_fm_nec_encoder_t *fm_encoder_iface = NULL;
    fm_encoder_iface = calloc(1, sizeof(rmt_fm_nec_encoder_t));
    fm_encoder_iface->base.encode = fm_isr_rmt_encode_nec;
    fm_encoder_iface->base.del = fm_isr_rmt_del_encoder;
    fm_encoder_iface->base.reset = fm_isr_rmt_reset_encoder;

    rmt_copy_encoder_config_t copy_encoder_config = {};
    rmt_new_copy_encoder(&copy_encoder_config, &fm_encoder_iface->copy_encoder);

    fm_encoder_iface->nec_leading_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = 100 * resolution / 1000000,
        .level1 = 0,
        .duration1 = 31*100 * resolution / 1000000,
    };
    fm_encoder_iface->ext_leading_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = 500 * resolution / 1000000,
        .level1 = 0,
        .duration1 = 1500 * resolution / 1000000,
    };
    fm_encoder_iface->nec_ending_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = 100 * resolution / 1000000,
        .level1 = 0,
        .duration1 = 0x7FFF,
    };

    rmt_bytes_encoder_config_t bytes_encoder_config = {
        .bit0 = {
            .level0 = 1,
            .duration0 = 100 * resolution / 1000000,
            .level1 = 0,
            .duration1 = 300 * resolution / 1000000,
        },
        .bit1 = {
            .level0 = 1,
            .duration0 = 300 * resolution / 1000000,
            .level1 = 0,
            .duration1 = 100 * resolution / 1000000,
        },
    };
    rmt_new_bytes_encoder(&bytes_encoder_config, &fm_encoder_iface->bytes_encoder);

    *ret_encoder = &fm_encoder_iface->base;
}

void fm_command_encode(t_fm_command * command) {
	if (command->protocol == FM_COMMAND_PROTOCOL_EXTENDED) {
		encrypter_process_memory(&(command->command), command->args, FM_COMMAND_ARG_MAXSIZE);
	}
}

