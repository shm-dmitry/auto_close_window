#include "fm_command_encoder.h"

// this code based on https://github.com/espressif/esp-idf/blob/master/examples/peripherals/rmt/ir_nec_transceiver

#include "crypto/encrypter.h"
#include "driver/rmt_encoder.h"
#include "string.h"
#include "esp_err.h"
#include "../log/log.h"
#include "stdbool.h"
#include "fm_command_addresses.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

typedef struct {
    rmt_encoder_t base;
    rmt_encoder_t *copy_encoder;
    rmt_encoder_t *bytes_encoder;
    rmt_symbol_word_t prepare_symbol;
    rmt_symbol_word_t leading_symbol;
    rmt_symbol_word_t ending_symbol;
    int state;
} rmt_fm_encoder_t;

typedef struct {
	bool found_preamble;
	uint16_t prev_duration;

	uint8_t * buffer;
	uint8_t buffer_size;
	uint8_t buffer_loaded_bits;

	uint16_t decoded_address;
} t_fm_encoder_context;

#define FM_COMMAND_DECODER_CONTINUE      0x00
#define FM_COMMAND_DECODER_RESTART       0x01
#define FM_COMMAND_DECODER_BUFFER_LOADED 0x02

#define FM_COMMAND_DURATION_BASE_SYMBOL  350

#define FM_DURATION_CHECK_BETWEEN(x, a, b) ((x) >= a && (x) <= b)

uint8_t fm_command_decode_next_period(t_fm_encoder_context * decoder_context, uint8_t level, uint16_t duration) {
	if (!decoder_context->found_preamble) {
		if (level == 0 && decoder_context->prev_duration == 0) {
			return FM_COMMAND_DECODER_CONTINUE;
		}

		if (level == 1 && decoder_context->prev_duration == 0) {
			decoder_context->prev_duration = duration;
			return FM_COMMAND_DECODER_CONTINUE;
		}

		if (level == 0) {
			if (duration / decoder_context->prev_duration > 25) {
				decoder_context->found_preamble = true;
	//			ESP_LOGI(LOG_FM_ENCODER, "Found preamble %d; prev %d", duration, context->prev_duration);
			}
		}

		decoder_context->prev_duration = duration;
		return FM_COMMAND_DECODER_CONTINUE;
	}

	if (level == 1) {
		decoder_context->prev_duration = duration;
		return FM_COMMAND_DECODER_CONTINUE;
	}

	uint8_t bit = 0;
	if (FM_DURATION_CHECK_BETWEEN((double)duration / decoder_context->prev_duration, 1.5, 10)) {
		bit = 0;
	} else if (FM_DURATION_CHECK_BETWEEN((double)decoder_context->prev_duration / duration, 1.5, 10)) {
		bit = 1;
	} else {
		ESP_LOGW(LOG_FM_ENCODER, "Reset encoder, bad duration %d; prev %d", duration, decoder_context->prev_duration);
		decoder_context->found_preamble = false;
		decoder_context->prev_duration = duration;
		decoder_context->buffer_loaded_bits = 0;
		return FM_COMMAND_DECODER_RESTART;
	}

//	ESP_LOGI(LOG_FM_ENCODER, "Bit#%d = %d", context->buffer_loaded_bits, bit);

	if (decoder_context->buffer_loaded_bits < decoder_context->buffer_size * 8) {
		if (decoder_context->buffer != NULL) {
			decoder_context->buffer[decoder_context->buffer_loaded_bits / 8] =
					decoder_context->buffer[decoder_context->buffer_loaded_bits / 8] +
					(bit << (7 - (decoder_context->buffer_loaded_bits % 8)));
		}
		decoder_context->buffer_loaded_bits++;
	}

	decoder_context->prev_duration = duration;
	if (decoder_context->buffer_loaded_bits == decoder_context->buffer_size * 8) {
		decoder_context->buffer_loaded_bits = 0;
		return FM_COMMAND_DECODER_BUFFER_LOADED;
	}

	return FM_COMMAND_DECODER_CONTINUE;
}

void fm_command_restart_context(t_fm_encoder_context * decoder_context) {
	if (decoder_context->buffer) {
		free(decoder_context->buffer);
	}

	memset(decoder_context, 0, sizeof(t_fm_encoder_context));
	decoder_context->buffer = malloc(2);
	decoder_context->buffer_size = 2;
	if (decoder_context->buffer) {
		memset(decoder_context->buffer, 0, 2);
	}
}

void fm_command_decode_on_next_byte(t_fm_encoder_context * decoder_context, t_fm_commands_list * list, uint8_t status) {
	if (status == FM_COMMAND_DECODER_BUFFER_LOADED) {
		if (decoder_context->buffer == NULL) {
			ESP_LOGW(LOG_FM_ENCODER, "Restart context - buffer == NULL");
			fm_command_restart_context(decoder_context);
			return;
		}

		if (decoder_context->decoded_address == 0 && decoder_context->buffer_size == 2) {
			decoder_context->decoded_address = (decoder_context->buffer[0] << 8) + decoder_context->buffer[1];
			free(decoder_context->buffer);
			decoder_context->buffer = NULL;

			if (decoder_context->decoded_address == 0) {
				ESP_LOGW(LOG_FM_ENCODER, "Restart context - address = 0 not allowed");
				fm_command_restart_context(decoder_context);
				return;
			}

			t_fm_command_address_data data = fm_command_metadata_by_address(decoder_context->decoded_address);
			if (data.val == FM_VAL_BY_ADDRESS_UNKNOWN) {
				ESP_LOGW(LOG_FM_ENCODER, "Restart context - address %04X not allowed", decoder_context->decoded_address);
				fm_command_restart_context(decoder_context);
				return;
			}

			if (data.args_size > FM_COMMAND_MAX_ARGS_SIZE) {
				ESP_LOGW(LOG_FM_ENCODER, "Restart context - Too many args for address %04X: %d, max %d", decoder_context->decoded_address, data.args_size, FM_COMMAND_MAX_ARGS_SIZE);
				fm_command_restart_context(decoder_context);
				return;
			}

			uint8_t size = data.encrypted ? decryptor_args_size_to_buff_size(data.args_size) : data.args_size;

//			ESP_LOGI(LOG_FM_ENCODER, "Requesting %d bytes for address %04X", size, context->decoded_address);

			decoder_context->buffer = malloc(size);
			decoder_context->buffer_size = size;
			if (decoder_context->buffer) {
				memset(decoder_context->buffer, 0, size);
			}
			return;
		}

		if (decoder_context->decoded_address != 0) {
			t_fm_command_address_data data = fm_command_metadata_by_address(decoder_context->decoded_address);
			if (data.val == FM_VAL_BY_ADDRESS_UNKNOWN) {
				ESP_LOGW(LOG_FM_ENCODER, "[BAD STATE] Restart context - address %04X not allowed", decoder_context->decoded_address);
				fm_command_restart_context(decoder_context);
				return;
			}

			if (data.args_size > FM_COMMAND_MAX_ARGS_SIZE) {
				ESP_LOGW(LOG_FM_ENCODER, "[BAD STATE] Restart context - Too many args for address %04X: %d, max %d",
						decoder_context->decoded_address, data.args_size, FM_COMMAND_MAX_ARGS_SIZE);
				fm_command_restart_context(decoder_context);
				return;
			}
/*
			ESP_LOGI(LOG_FM_ENCODER, "Processing %s command address %04X; buffer size = %d",
					(data.encrypted ? "encrypted" : "plain"),
					context->decoded_address,
					context->buffer_size);
*/
			t_fm_command * temp = NULL;
			if (data.encrypted) {
				temp = decrypter_process_memory(decoder_context->decoded_address, decoder_context->buffer, decoder_context->buffer_size);
			} else {
				temp = malloc(sizeof(t_fm_command));
				if (temp != NULL) {
					temp->address = decoder_context->decoded_address;
					temp->args_size = decoder_context->buffer_size;
					memcpy(temp->args, decoder_context->buffer, decoder_context->buffer_size);
				}
			}

			fm_command_restart_context(decoder_context);

			if (temp) {
				t_fm_command * prev = list->commands;
				list->commands = malloc(sizeof(t_fm_command) * (list->commands_size + 1));
				if (list->commands == NULL) {
					list->commands = prev;
				} else {
					if (prev) {
						memcpy(list->commands, prev, sizeof(t_fm_command) * list->commands_size);
					}
					memcpy(&(list->commands[list->commands_size]), temp, sizeof(t_fm_command));
					list->commands_size++;

					if (prev) {
						free(prev);
						prev = NULL;
					}
				}

				free(temp);
				temp = NULL;
			}
		}
	}

	if (status == FM_COMMAND_DECODER_RESTART) {
		fm_command_restart_context(decoder_context);
		return;
	}
}

t_fm_commands_list * fm_command_decode(void ** decoder_context_ptr, const rmt_rx_done_event_data_t *edata) {
	if (edata->num_symbols == 0 || edata->num_symbols > 0xFFFF) {
		return NULL;
	}

	if (edata->num_symbols < 10) {
		return NULL;
	}

	t_fm_encoder_context * decoder_context = (t_fm_encoder_context *)*decoder_context_ptr;

	t_fm_commands_list * list = malloc(sizeof(t_fm_commands_list));
	if (list == NULL) {
		return NULL;
	}

	memset(list, 0, sizeof(t_fm_commands_list));

	if (decoder_context == NULL) {
		decoder_context = malloc(sizeof(t_fm_encoder_context));
		if (decoder_context == NULL) {
			free(list);
			return NULL;
		}
		memset(decoder_context, 0, sizeof(t_fm_encoder_context));
		fm_command_restart_context(decoder_context);
	}

	for (size_t i = 0; i<edata->num_symbols; i++) {
		if (edata->received_symbols[i].duration0 == 0 || edata->received_symbols[i].duration1 == 0) {
			continue;
		}
/*
		ESP_LOGI(LOG_FM_ENCODER, "Duration0 = %d, Level0 = %d, Duration1 = %d, Level1 = %d",
				edata->received_symbols[i].duration0,
				edata->received_symbols[i].level0,
				edata->received_symbols[i].duration1,
				edata->received_symbols[i].level1);
*/
		uint8_t status = fm_command_decode_next_period(decoder_context, edata->received_symbols[i].level0, edata->received_symbols[i].duration0);
		fm_command_decode_on_next_byte(decoder_context, list, status);
		status = fm_command_decode_next_period(decoder_context, edata->received_symbols[i].level1, edata->received_symbols[i].duration1);
		fm_command_decode_on_next_byte(decoder_context, list, status);
	}

	if (edata->flags.is_last) {
		if (decoder_context->buffer) {
			free(decoder_context->buffer);
			decoder_context->buffer = NULL;
		}
		free(decoder_context);
		decoder_context = NULL;
		ESP_LOGI(LOG_FM_ENCODER, "Context destroyed");
	} else {
		ESP_LOGI(LOG_FM_ENCODER, "Partical transfer - context saved");
	}

	return list;
}

static size_t IRAM_ATTR fm_isr_rmt_encode(rmt_encoder_t *encoder, rmt_channel_handle_t channel, const void *primary_data, size_t data_size, rmt_encode_state_t *ret_state)
{
	rmt_fm_encoder_t *encoder_data = __containerof(encoder, rmt_fm_encoder_t, base);
    rmt_encode_state_t session_state = RMT_ENCODING_RESET;
    rmt_encode_state_t state = RMT_ENCODING_RESET;
    size_t encoded_symbols = 0;
    rmt_encoder_handle_t copy_encoder = encoder_data->copy_encoder;
    rmt_encoder_handle_t bytes_encoder = encoder_data->bytes_encoder;

    if (encoder_data->state == 0) {
		encoded_symbols += copy_encoder->encode(copy_encoder,
												channel,
												&encoder_data->prepare_symbol,
												sizeof(rmt_symbol_word_t),
												&session_state);
		if (session_state & RMT_ENCODING_COMPLETE) {
			encoder_data->state = 1;
		}
		if (session_state & RMT_ENCODING_MEM_FULL) {
			state |= RMT_ENCODING_MEM_FULL;
			goto out;
		}
    }

    if (encoder_data->state == 1) {
        encoded_symbols += copy_encoder->encode(copy_encoder,
												channel,
												&encoder_data->leading_symbol,
												sizeof(rmt_symbol_word_t),
												&session_state);
        if (session_state & RMT_ENCODING_COMPLETE) {
            encoder_data->state = 1;
        }
        if (session_state & RMT_ENCODING_MEM_FULL) {
            state |= RMT_ENCODING_MEM_FULL;
            goto out;
        }
    }

    if (encoder_data->state < data_size + 2) {
        encoded_symbols += bytes_encoder->encode(bytes_encoder,
        										 channel,
												 primary_data,
												 data_size,
												 &session_state);
        if (session_state & RMT_ENCODING_COMPLETE) {
            encoder_data->state = data_size + 2;
        }
        if (session_state & RMT_ENCODING_MEM_FULL) {
            state |= RMT_ENCODING_MEM_FULL;
            goto out;
        }
    }

    encoded_symbols += copy_encoder->encode(copy_encoder, channel, &encoder_data->ending_symbol,
                                            sizeof(rmt_symbol_word_t), &session_state);
    if (session_state & RMT_ENCODING_COMPLETE) {
        encoder_data->state = 0;
        state |= RMT_ENCODING_COMPLETE;
    }
    if (session_state & RMT_ENCODING_MEM_FULL) {
        state |= RMT_ENCODING_MEM_FULL;
        goto out;
    }

out:
    *ret_state = state;
    return encoded_symbols;
}

static esp_err_t IRAM_ATTR fm_isr_rmt_del_encoder(rmt_encoder_t *encoder)
{
	rmt_fm_encoder_t *encoder_data = __containerof(encoder, rmt_fm_encoder_t, base);
    rmt_del_encoder(encoder_data->copy_encoder);
    rmt_del_encoder(encoder_data->bytes_encoder);
    free(encoder_data);
    return ESP_OK;
}

static esp_err_t IRAM_ATTR fm_isr_rmt_reset_encoder(rmt_encoder_t *encoder)
{
	rmt_fm_encoder_t *encoder_data = __containerof(encoder, rmt_fm_encoder_t, base);
    rmt_encoder_reset(encoder_data->copy_encoder);
    rmt_encoder_reset(encoder_data->bytes_encoder);
    encoder_data->state = 0;
    return ESP_OK;
}

void rmt_new_ir_nec_encoder(rmt_encoder_handle_t *ret_encoder) {
    rmt_fm_encoder_t *fm_encoder_iface = NULL;
    fm_encoder_iface = calloc(1, sizeof(rmt_fm_encoder_t));
    fm_encoder_iface->state = 0;
    fm_encoder_iface->base.encode = fm_isr_rmt_encode;
    fm_encoder_iface->base.del = fm_isr_rmt_del_encoder;
    fm_encoder_iface->base.reset = fm_isr_rmt_reset_encoder;

    rmt_copy_encoder_config_t copy_encoder_config = {};
    rmt_new_copy_encoder(&copy_encoder_config, &fm_encoder_iface->copy_encoder);

    fm_encoder_iface->prepare_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = FM_COMMAND_DURATION_BASE_SYMBOL,
        .level1 = 0,
        .duration1 = FM_COMMAND_DURATION_BASE_SYMBOL,
    };
    fm_encoder_iface->leading_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = FM_COMMAND_DURATION_BASE_SYMBOL,
        .level1 = 0,
        .duration1 = 28 * FM_COMMAND_DURATION_BASE_SYMBOL,
    };
    fm_encoder_iface->ending_symbol = (rmt_symbol_word_t) {
        .level0 = 1,
        .duration0 = FM_COMMAND_DURATION_BASE_SYMBOL,
        .level1 = 0,
        .duration1 = FM_COMMAND_DURATION_BASE_SYMBOL,
    };

    rmt_bytes_encoder_config_t bytes_encoder_config = {
        .bit0 = {
            .level0 = 1,
            .duration0 = FM_COMMAND_DURATION_BASE_SYMBOL,
            .level1 = 0,
            .duration1 = 4 * FM_COMMAND_DURATION_BASE_SYMBOL,
        },
        .bit1 = {
            .level0 = 1,
            .duration0 = 4 * FM_COMMAND_DURATION_BASE_SYMBOL,
            .level1 = 0,
            .duration1 = FM_COMMAND_DURATION_BASE_SYMBOL,
        },
		.flags = {
			.msb_first = true
		}
    };
    rmt_new_bytes_encoder(&bytes_encoder_config, &fm_encoder_iface->bytes_encoder);

    *ret_encoder = &fm_encoder_iface->base;
}

void fm_command_encode(t_fm_command * command, uint8_t ** out_buffer, uint8_t * out_buffer_size) {
	t_fm_command_address_data data = fm_command_metadata_by_address(command->address);

	if (data.args_size != command->args_size) {
		*out_buffer = NULL;
		*out_buffer_size = 0;
		return;
	}

	if (data.encrypted) {
		encrypter_process_memory(command, out_buffer, out_buffer_size);
	} else {
		*out_buffer = malloc(command->args_size + 2);
		if (*out_buffer) {
			*out_buffer[0] = command->address >> 8;
			*out_buffer[1] = command->address % 256;
			if (command->args_size > 0) {
				memcpy((*out_buffer) + 2, command->args, command->args_size);
			}
		}
	}
}
