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

#include "../controller/controller.h"

#define RX_BUFFER_SIZE 3
#define FM_RECEIVER_TASK_STACK_SIZE 1024

#define FM_COMMAND_SYMBOLS (FM_COMMAND_ARG_MAXSIZE * 8 + 2 * 8 + 2)

static bool fm_rx_done_callback(rmt_channel_handle_t channel, const rmt_rx_done_event_data_t *edata, void *user_data) {
    BaseType_t high_task_wakeup = pdFALSE;
    QueueHandle_t receive_queue = (QueueHandle_t)user_data;
    xQueueSendFromISR(receive_queue, edata, &high_task_wakeup);
    return high_task_wakeup == pdTRUE;
}

static void fm_receiver_task(void* arg) {
	rmt_receive_config_t fm_receiveconfig = {
		.signal_range_min_ns = 1250,
		.signal_range_max_ns = 12000000
	};

    rmt_rx_event_callbacks_t cbs = {
        .on_recv_done = fm_rx_done_callback,
    };

    rmt_channel_handle_t rx_chan = (rmt_channel_handle_t) arg;

    QueueHandle_t queue = xQueueCreate(1, sizeof(rmt_rx_done_event_data_t));

    ESP_ERROR_CHECK(rmt_rx_register_event_callbacks(rx_chan, &cbs, queue));

    ESP_ERROR_CHECK(rmt_enable(rx_chan));

    rmt_symbol_word_t raw_symbols[64];
	t_fm_command decoded;
    while(true) {
    	memset(raw_symbols, 0, sizeof(raw_symbols));
    	ESP_ERROR_CHECK(rmt_receive(rx_chan, raw_symbols, sizeof(raw_symbols), &fm_receiveconfig));

		rmt_rx_done_event_data_t rx_data;
		xQueueReceive(queue, &rx_data, portMAX_DELAY);

		memset(&decoded, 0, sizeof(t_fm_command));
		if (fm_command_decode(&rx_data, &decoded)) {
			controller_process_command(&decoded);
		}
    }
}

void fm_receiver_init() {
	rmt_rx_channel_config_t rx_chan_config_433 = {
	    .clk_src = RMT_CLK_SRC_DEFAULT,
	    .resolution_hz = 1 * 1000 * 1000,
	    .mem_block_symbols = FM_COMMAND_SYMBOLS,
	    .gpio_num = CONFIG_PIN_FM_IN_433,
	    .flags.invert_in = false,
	    .flags.with_dma = false,
	};

	rmt_channel_handle_t rx_chan_433;
	rmt_channel_handle_t rx_chan_315;

    esp_err_t res = rmt_new_rx_channel(&rx_chan_config_433, &rx_chan_433);
    if (res) {
		ESP_LOGE(LOG_FM_SENDER, "rmt_new_rx_channel-433 error: %d", res);
		return;
    }

	rmt_rx_channel_config_t rx_chan_config_315 = {
	    .clk_src = RMT_CLK_SRC_DEFAULT,
	    .resolution_hz = 1 * 1000 * 1000,
	    .mem_block_symbols = FM_COMMAND_SYMBOLS,
	    .gpio_num = CONFIG_PIN_FM_IN_315,
	    .flags.invert_in = false,
	    .flags.with_dma = false,
	};

    res = rmt_new_rx_channel(&rx_chan_config_315, &rx_chan_315);
    if (res) {
		ESP_LOGE(LOG_FM_SENDER, "rmt_new_rx_channel-315 error: %d", res);
		return;
    }

    rmt_carrier_config_t rx_carrier_cfg = {
        .duty_cycle = 0.33,
        .frequency_hz = CONFIG_FM_RX_CARRIER_FREQ,
    };

    res = rmt_apply_carrier(rx_chan_433, &rx_carrier_cfg);
    if (res) {
		ESP_LOGE(LOG_FM_SENDER, "rmt_apply_carrier-433 error: %d", res);
		return;
    }

    res = rmt_apply_carrier(rx_chan_315, &rx_carrier_cfg);
    if (res) {
		ESP_LOGE(LOG_FM_SENDER, "rmt_apply_carrier-315 error: %d", res);
		return;
    }

	xTaskCreate(fm_receiver_task, "FM receiver 433", FM_RECEIVER_TASK_STACK_SIZE, rx_chan_433, 10, NULL);
	xTaskCreate(fm_receiver_task, "FM receiver 315", FM_RECEIVER_TASK_STACK_SIZE, rx_chan_315, 10, NULL);
}
