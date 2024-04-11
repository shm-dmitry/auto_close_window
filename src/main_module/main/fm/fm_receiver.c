#include "fm_receiver.h"

#include "driver/rmt_rx.h"
#include "stddef.h"
#include "sdkconfig.h"
#include "../log/log.h"
#include "stdbool.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "fm_command_encoder.h"
#include "esp_timer.h"

#include "../controller/controller.h"

#define FM_RECEIVER_TASK_STACK_SIZE 4096
#define FM_RECEIVER_AIR_CLEAN_TIMEOUT ((uint64_t)30000)

#define FM_RECEIVER_DATA_ONE_PART 192

typedef struct {
	QueueHandle_t queue;
	bool update_last_received;
} t_fm_isr_parameters;

typedef struct {
	rmt_channel_handle_t rx_chan;
	bool update_last_received;
	uint16_t freq;
} t_fm_task_parameters;

int64_t volatile fm_receiver_last_received = 0;

static bool IRAM_ATTR fm_rx_done_callback(rmt_channel_handle_t channel, const rmt_rx_done_event_data_t *edata, void *user_data) {
    BaseType_t high_task_wakeup = pdFALSE;
    t_fm_isr_parameters * params = (t_fm_isr_parameters *)user_data;

    rmt_rx_done_event_data_t copy;
	copy.num_symbols = edata->num_symbols;
	copy.flags = edata->flags;
	copy.received_symbols = malloc(sizeof(rmt_symbol_word_t) * edata->num_symbols);
	if (copy.received_symbols) {
		memcpy(copy.received_symbols, edata->received_symbols, sizeof(rmt_symbol_word_t) * edata->num_symbols);
		xQueueSendFromISR(params->queue, &copy, &high_task_wakeup);
	}

	if (params->update_last_received && edata->num_symbols > 5) {
		fm_receiver_last_received = esp_timer_get_time() + FM_RECEIVER_AIR_CLEAN_TIMEOUT;
	}

    return high_task_wakeup == pdTRUE;
}

static void fm_receiver_task(void* arg) {
	t_fm_task_parameters * taskparams = (t_fm_task_parameters *) arg;

    rmt_receive_config_t fm_receiveconfig = {
		.signal_range_min_ns = 100,
		.signal_range_max_ns = FM_COMMAND_ENCODER_MAX_IMPL_TIME * 1000,
		.flags = {
			.en_partial_rx = true
		}
	};

    rmt_rx_event_callbacks_t cbs = {
        .on_recv_done = fm_rx_done_callback,
    };

    QueueHandle_t queue = xQueueCreate(10, sizeof(rmt_rx_done_event_data_t));

    t_fm_isr_parameters params = {
		.queue = queue,
		.update_last_received = taskparams->update_last_received
    };

    ESP_ERROR_CHECK(rmt_rx_register_event_callbacks(taskparams->rx_chan, &cbs, &params));

    ESP_ERROR_CHECK(rmt_enable(taskparams->rx_chan));

    _ESP_LOGI(LOG_FM_RECEIVER, "FM Channel %dMHz started to listen", taskparams->freq);

    rmt_symbol_word_t raw_symbols[FM_RECEIVER_DATA_ONE_PART];
	void * decoder_context_data = NULL;

    while(true) {
    	memset(raw_symbols, 0, sizeof(rmt_symbol_word_t) * FM_RECEIVER_DATA_ONE_PART);
    	ESP_ERROR_CHECK(rmt_receive(taskparams->rx_chan, raw_symbols, sizeof(rmt_symbol_word_t) * FM_RECEIVER_DATA_ONE_PART, &fm_receiveconfig));

    	while (true) {
			rmt_rx_done_event_data_t rx_data;
			xQueueReceive(queue, &rx_data, portMAX_DELAY);

			t_fm_commands_list * list = fm_command_decode(&decoder_context_data, &rx_data, taskparams->freq);

			free(rx_data.received_symbols);
			rx_data.received_symbols = NULL;

			if (list != NULL) {
				for (uint8_t i = 0; i<list->commands_size; i++) {
					controller_process_command(&(list->commands[i]));
				}

				free(list->commands);
				list->commands = NULL;
				free(list);
				list = NULL;
			}

			if (rx_data.flags.is_last) {
				break;
			}
    	}
    }
}

bool fm_receiver_is_air_clean() {
	return esp_timer_get_time() > fm_receiver_last_received;
}

void fm_receiver_init() {
	rmt_rx_channel_config_t rx_chan_config_433 = {
	    .clk_src = RMT_CLK_SRC_DEFAULT,
	    .resolution_hz = 1 * 1000 * 1000,
	    .mem_block_symbols = FM_RECEIVER_DATA_ONE_PART,
	    .gpio_num = CONFIG_PIN_FM_IN_433,
	    .flags.invert_in = false,
	    .flags.with_dma = false,
	};

	rmt_channel_handle_t rx_chan_433;
	rmt_channel_handle_t rx_chan_315;

    esp_err_t res = rmt_new_rx_channel(&rx_chan_config_433, &rx_chan_433);
    if (res) {
		_ESP_LOGE(LOG_FM_RECEIVER, "rmt_new_rx_channel-433 error: %d", res);
		return;
    }

	rmt_rx_channel_config_t rx_chan_config_315 = {
	    .clk_src = RMT_CLK_SRC_DEFAULT,
	    .resolution_hz = 1 * 1000 * 1000,
	    .mem_block_symbols = FM_RECEIVER_DATA_ONE_PART,
	    .gpio_num = CONFIG_PIN_FM_IN_315,
	    .flags.invert_in = false,
	    .flags.with_dma = false,
	};

    res = rmt_new_rx_channel(&rx_chan_config_315, &rx_chan_315);
    if (res) {
		_ESP_LOGE(LOG_FM_RECEIVER, "rmt_new_rx_channel-315 error: %d", res);
		return;
    }

    t_fm_task_parameters * p315 = malloc(sizeof(t_fm_task_parameters));
    t_fm_task_parameters * p433 = malloc(sizeof(t_fm_task_parameters));

    p315->rx_chan = rx_chan_315;
    p315->update_last_received = true;
    p315->freq = 315;

    p433->rx_chan = rx_chan_433;
    p433->update_last_received = false;
    p433->freq = 433;

	xTaskCreate(fm_receiver_task, "FM receiver 433", FM_RECEIVER_TASK_STACK_SIZE, p433, 10, NULL);
	xTaskCreate(fm_receiver_task, "FM receiver 315", FM_RECEIVER_TASK_STACK_SIZE, p315, 10, NULL);

	_ESP_LOGI(LOG_FM_RECEIVER, "FM Receiver initialized");
}
