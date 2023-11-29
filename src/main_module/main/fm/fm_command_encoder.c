#include "fm_command_encoder.h"

// we decode NEC protocol to use remote-control-units, and extended protocol (NEC-based) to transfer more data

// this code based on https://github.com/espressif/esp-idf/blob/master/examples/peripherals/rmt/ir_nec_transceiver

#include "crypto/encrypter.h"
#include "driver/rmt_encoder.h"
#include "string.h"
#include "esp_err.h"
#include "../log/log.h"

#define NEC_DECODE_MARGIN 200

#define NEC_LEADING_CODE_DURATION_0  9000ULL
#define NEC_LEADING_CODE_DURATION_1  4500ULL
#define NEC_PAYLOAD_ZERO_DURATION_0  560
#define NEC_PAYLOAD_ONE_DURATION_0   560
#define NEC_PAYLOAD_ZERO_DURATION_1  560
#define NEC_PAYLOAD_ONE_DURATION_1   1690
// TODO: repeat?
#define NEC_REPEAT_CODE_DURATION_0   9000
#define NEC_REPEAT_CODE_DURATION_1   2250

#define EXTENDED_LEADING_CODE_DURATION_0  7000ULL
#define EXTENDED_LEADING_CODE_DURATION_1  6500ULL

typedef struct {
    rmt_encoder_t base;           // the base "class", declares the standard encoder interface
    rmt_encoder_t *copy_encoder;  // use the copy_encoder to encode the leading and ending pulse
    rmt_encoder_t *bytes_encoder; // use the bytes_encoder to encode the address and command data
    rmt_symbol_word_t nec_leading_symbol; // NEC leading code with RMT representation
    rmt_symbol_word_t ext_leading_symbol; // NEC leading code with RMT representation
    rmt_symbol_word_t nec_ending_symbol;  // NEC ending code with RMT representation
    int state;
} rmt_fm_nec_encoder_t;

static inline bool nec_check_in_range(uint32_t signal_duration, uint32_t spec_duration) {
    return (signal_duration < (spec_duration + NEC_DECODE_MARGIN)) &&
           (signal_duration > (spec_duration - NEC_DECODE_MARGIN));
}

static bool nec_parse_logic0(const rmt_symbol_word_t *rmt_nec_symbols) {
    return nec_check_in_range(rmt_nec_symbols->duration0, NEC_PAYLOAD_ZERO_DURATION_0) &&
           nec_check_in_range(rmt_nec_symbols->duration1, NEC_PAYLOAD_ZERO_DURATION_1);
}

static bool nec_parse_logic1(const rmt_symbol_word_t *rmt_nec_symbols) {
    return nec_check_in_range(rmt_nec_symbols->duration0, NEC_PAYLOAD_ONE_DURATION_0) &&
           nec_check_in_range(rmt_nec_symbols->duration1, NEC_PAYLOAD_ONE_DURATION_1);
}

bool fm_command_decode(const rmt_rx_done_event_data_t *edata, t_fm_command * result) {
	if (edata->num_symbols == 0) {
		return false;
	}

	const rmt_symbol_word_t *cur = edata->received_symbols;
    if (nec_check_in_range(cur->duration0, NEC_LEADING_CODE_DURATION_0) &&
            nec_check_in_range(cur->duration1, NEC_LEADING_CODE_DURATION_1)) {
    	result->protocol = FM_COMMAND_PROTOCOL_NEC;
    } else if (nec_check_in_range(cur->duration0, EXTENDED_LEADING_CODE_DURATION_0) &&
            nec_check_in_range(cur->duration1, EXTENDED_LEADING_CODE_DURATION_1)) {
    	result->protocol = FM_COMMAND_PROTOCOL_EXTENDED;
    } else {
    	return false;
    }

    if (edata->num_symbols != (FM_COMMAND_ADDRESS_BYTES(result->protocol) + 16 + 2)) {
    	return false;
    }

    cur++;
    for (int i = 0; i < FM_COMMAND_ADDRESS_BYTES(result->protocol); i++) {
        if (nec_parse_logic1(cur)) {
            result->args[i / 8] |= 1 << i;
        } else if (nec_parse_logic0(cur)) {
        	result->args[i / 8] &= ~(1 << i);
        } else {
            return false;
        }
        cur++;
    }

    for (int i = 0; i < 16; i++) {
        if (nec_parse_logic1(cur)) {
            result->command |= 1 << i;
        } else if (nec_parse_logic0(cur)) {
        	result->command &= ~(1 << i);
        } else {
            return false;
        }
        cur++;
    }

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

    uint8_t size = FM_COMMAND_ADDRESS_BYTES(fm_command->protocol);

    if (nec_encoder->state <= size) {
        encoded_symbols += bytes_encoder->encode(bytes_encoder,
        										 channel,
												 fm_command->args,
												 FM_COMMAND_ADDRESS_BYTES(fm_command->protocol),
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
    rmt_fm_nec_encoder_t *nec_encoder = NULL;
    nec_encoder = calloc(1, sizeof(rmt_fm_nec_encoder_t));
    nec_encoder->base.encode = fm_isr_rmt_encode_nec;
    nec_encoder->base.del = fm_isr_rmt_del_encoder;
    nec_encoder->base.reset = fm_isr_rmt_reset_encoder;

    rmt_copy_encoder_config_t copy_encoder_config = {};
    rmt_new_copy_encoder(&copy_encoder_config, &nec_encoder->copy_encoder);

    // construct the leading code and ending code with RMT symbol format
    nec_encoder->nec_leading_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = NEC_LEADING_CODE_DURATION_0 * resolution / 1000000,
        .level1 = 0,
        .duration1 = NEC_LEADING_CODE_DURATION_1 * resolution / 1000000,
    };
    nec_encoder->ext_leading_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = EXTENDED_LEADING_CODE_DURATION_0 * resolution / 1000000,
        .level1 = 0,
        .duration1 = EXTENDED_LEADING_CODE_DURATION_1 * resolution / 1000000,
    };
    nec_encoder->nec_ending_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = 560 * resolution / 1000000,
        .level1 = 0,
        .duration1 = 0x7FFF,
    };

    rmt_bytes_encoder_config_t bytes_encoder_config = {
        .bit0 = {
            .level0 = 1,
            .duration0 = NEC_PAYLOAD_ZERO_DURATION_0 * resolution / 1000000, // T0H=560us
            .level1 = 0,
            .duration1 = NEC_PAYLOAD_ONE_DURATION_0 * resolution / 1000000, // T0L=560us
        },
        .bit1 = {
            .level0 = 1,
            .duration0 = NEC_PAYLOAD_ZERO_DURATION_1 * resolution / 1000000,  // T1H=560us
            .level1 = 0,
            .duration1 = NEC_PAYLOAD_ONE_DURATION_1 * resolution / 1000000, // T1L=1690us
        },
    };
    rmt_new_bytes_encoder(&bytes_encoder_config, &nec_encoder->bytes_encoder);

    *ret_encoder = &nec_encoder->base;
}

void fm_command_encode(t_fm_command * command) {
	if (command->protocol == FM_COMMAND_PROTOCOL_EXTENDED) {
		encrypter_process_memory(&(command->command), command->args, FM_COMMAND_ARG_MAXSIZE);
	}
}

