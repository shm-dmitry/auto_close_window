#include "stepper_adc.h"

#include <string.h>
#include "sdkconfig.h"
#include "../log/log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_adc/adc_continuous.h"
#include "../common/delay_timer.h"

#define STEPPER_ADC_TASK_STACK_SIZE 2048
#define STEPPER_ADC_FRAME_SIZE (5*2*2)

#define STEPPER_ADC_MAXVALUE       4095

static TaskHandle_t stepper_adc_task = NULL;
adc_continuous_handle_t stepper_adc_handle = NULL;

static volatile uint8_t stepper_adc_limit_switch_value = 0xFF;
static volatile uint8_t stepper_adc_noise_alarm_value = 0xFF;

#define STEPPER_ADC_OPENCLOSE_AWAIT_MS	20
#define STEPPER_ADC_IS_CLOSED(x) ( \
									(x) >= (CONFIG_ADC_STEPPER_CLOSE_VALUE - CONFIG_ADC_STEPPER_DELTA_PC) && \
									(x) <= (CONFIG_ADC_STEPPER_CLOSE_VALUE + CONFIG_ADC_STEPPER_DELTA_PC) \
							     )
#define STEPPER_ADC_IS_OPENED(x) ( \
									(x) >= (CONFIG_ADC_STEPPER_OPEN_VALUE - CONFIG_ADC_STEPPER_DELTA_PC) && \
									(x) <= (CONFIG_ADC_STEPPER_OPEN_VALUE + CONFIG_ADC_STEPPER_DELTA_PC) \
								 )
#define STEPPER_ADC_IS_ALLOWED(x) ( \
									(x) >= (CONFIG_ADC_STEPPER_STEPPER_NOT_ALLOWED_VALUE + CONFIG_ADC_STEPPER_DELTA_PC) && \
									(x) <= (CONFIG_ADC_STEPPER_CONNECTED_VALUE - CONFIG_ADC_STEPPER_DELTA_PC) \
								  )

bool stepper_adc_is_close_position_reached();
bool stepper_adc_is_open_position_reached();
bool stepper_adc_is_stepper_allowed();
static void stepper_adc_on_read_raw_value_task(void*);

static bool IRAM_ATTR isr_stepper_adc_callback(adc_continuous_handle_t handle, const adc_continuous_evt_data_t *edata, void *user_data)
{
    BaseType_t mustYield = pdFALSE;
    //Notify that ADC continuous driver has done enough number of conversions
    vTaskNotifyGiveFromISR(stepper_adc_task, &mustYield);

    return (mustYield == pdTRUE);
}

t_endstops * stepper_adc_init() {
    adc_continuous_handle_cfg_t adc_config = {
        .max_store_buf_size = 1024,
        .conv_frame_size = STEPPER_ADC_FRAME_SIZE,
    };
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &stepper_adc_handle));

    adc_continuous_config_t dig_cfg = {
        .sample_freq_hz = 20 * 1000,
        .conv_mode = ADC_CONV_SINGLE_UNIT_1,
        .format = ADC_DIGI_OUTPUT_FORMAT_TYPE1,
    };

    adc_digi_pattern_config_t adc_pattern[2] = {
    		{
				.atten = ADC_ATTEN_DB_12,
				.channel = CONFIG_ADC_STEPPER_LIMITSWITCH,
				.unit = ADC_UNIT_1,
				.bit_width = ADC_BITWIDTH_12
    		},
			{
				.atten = ADC_ATTEN_DB_12,
				.channel = CONFIG_ADC_STEPPER_NOISE_ALARM,
				.unit = ADC_UNIT_1,
				.bit_width = ADC_BITWIDTH_12
			}
    };

	dig_cfg.adc_pattern = adc_pattern;
    dig_cfg.pattern_num = 2;

    ESP_ERROR_CHECK(adc_continuous_config(stepper_adc_handle, &dig_cfg));

	xTaskCreate(stepper_adc_on_read_raw_value_task, "stepper adc read task", STEPPER_ADC_TASK_STACK_SIZE, NULL, 10, NULL);

	while(stepper_adc_limit_switch_value == 0xFF || stepper_adc_noise_alarm_value == 0xFF) {
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}

    t_endstops * endstops = (t_endstops *) malloc(sizeof(t_endstops));
    if (endstops == NULL) {
    	return NULL;
    }

    memset(endstops, 0, sizeof(t_endstops));

    endstops->is_close_fired = &stepper_adc_is_close_position_reached;
    endstops->is_open_fired = &stepper_adc_is_open_position_reached;
    endstops->is_stepper_allowed = &stepper_adc_is_stepper_allowed;

	return endstops;
}

static void stepper_adc_on_read_raw_value_task(void*) {
	stepper_adc_task = xTaskGetCurrentTaskHandle();

    adc_continuous_evt_cbs_t cbs = {
        .on_conv_done = isr_stepper_adc_callback,
    };
    ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(stepper_adc_handle, &cbs, NULL));
    ESP_ERROR_CHECK(adc_continuous_start(stepper_adc_handle));

    while (true) {
    	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        uint8_t result[STEPPER_ADC_FRAME_SIZE] = {0};
        memset(result, 0xCC, STEPPER_ADC_FRAME_SIZE);

        uint32_t readed = 0;
    	esp_err_t err = adc_continuous_read(stepper_adc_handle, result, STEPPER_ADC_FRAME_SIZE, &readed, 0);

        if (err == ESP_OK) {
        	uint32_t lsw_avg = 0;
        	uint32_t noise_avg = 0;
        	uint8_t lsw_cnt = 0;
        	uint8_t noise_cnt = 0;

            for (int i = 0; i < readed; i += SOC_ADC_DIGI_RESULT_BYTES) {
                adc_digi_output_data_t *p = (adc_digi_output_data_t*)&result[i];
                uint16_t chan_num = ((p)->type1.channel);
                uint16_t data =  ((p)->type1.data);

                if (chan_num == CONFIG_ADC_STEPPER_LIMITSWITCH && data <= STEPPER_ADC_MAXVALUE) {
                	lsw_avg += ((uint32_t)data * (uint32_t)100) / (uint32_t)STEPPER_ADC_MAXVALUE;
                	lsw_cnt++;
                } else if (chan_num == CONFIG_ADC_STEPPER_NOISE_ALARM && data <= STEPPER_ADC_MAXVALUE) {
                	noise_avg += ((uint32_t)data * (uint32_t)100) / (uint32_t)STEPPER_ADC_MAXVALUE;
                	noise_cnt++;
                }
            }

            if (lsw_cnt > 0) {
#if CONFIG_ADC_STEPPER_CALIBRATION_MODE
            	uint8_t prev = stepper_adc_limit_switch_value;
#endif
            	stepper_adc_limit_switch_value = lsw_avg / lsw_cnt;
#if CONFIG_ADC_STEPPER_CALIBRATION_MODE
            	if (prev != stepper_adc_limit_switch_value) {
            		ESP_LOGI(LOG_STEPPER_ADC, "LSW Value: %d%%", stepper_adc_limit_switch_value);
            	}
#endif
            }
            if (noise_cnt > 0) {
#if CONFIG_ADC_STEPPER_CALIBRATION_MODE
            	uint8_t prev = stepper_adc_noise_alarm_value;
#endif
            	stepper_adc_noise_alarm_value = noise_avg / noise_cnt;
#if CONFIG_ADC_STEPPER_CALIBRATION_MODE
            	if (prev != stepper_adc_noise_alarm_value) {
            		ESP_LOGI(LOG_STEPPER_ADC, "Noise Value: %d%%", stepper_adc_noise_alarm_value);
            	}
#endif
            }
        }
    }
}


bool stepper_adc_is_close_position_reached() {
	uint8_t x = stepper_adc_limit_switch_value;
	if (STEPPER_ADC_IS_CLOSED(x)) {
		t_delay_timer * timer = delay_timer_allocate(STEPPER_ADC_OPENCLOSE_AWAIT_MS);
		while(!delay_timer_start_or_check(timer)) {
			x = stepper_adc_limit_switch_value;
			if (!STEPPER_ADC_IS_CLOSED(x)) {
				delay_timer_release(&timer);
				return false;
			}
		}

		delay_timer_release(&timer);

		return true;
	} else {
		return false;
	}
}

bool stepper_adc_is_open_position_reached() {
	uint8_t x = stepper_adc_limit_switch_value;
	if (STEPPER_ADC_IS_OPENED(x)) {
		t_delay_timer * timer = delay_timer_allocate(STEPPER_ADC_OPENCLOSE_AWAIT_MS);
		while(!delay_timer_start_or_check(timer)) {
			x = stepper_adc_limit_switch_value;
			if (!STEPPER_ADC_IS_OPENED(x)) {
				delay_timer_release(&timer);
				return false;
			}
		}

		delay_timer_release(&timer);

		return true;
	} else {
		return false;
	}
}

bool stepper_adc_is_stepper_allowed() {
	uint8_t x = stepper_adc_limit_switch_value;
	return  STEPPER_ADC_IS_ALLOWED(x);
}

bool stepper_adc_is_noise_alarm_fired() {
	uint8_t x = stepper_adc_noise_alarm_value;
	return x >= CONFIG_ADC_STEPPER_NOISE_ALARM_VALUE;
}
