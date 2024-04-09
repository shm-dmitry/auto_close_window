#include "stepper_init.h"

#include "stepper_executor.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_attr.h"
#include "../log/log.h"
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"

#include "string.h"

#define STEPPER_COMMAND_TASK_STACK_SIZE 2048

#define STEPPER_MOVE_TO_POS_RECHECK_QUEUE_EVERY 10

#define STEPPER_SYGNALS_PER_ONE_STEP  100
#define STEPPER_SYGNAL_FREQUENCY      2000

#define STEPPER_ADC_MAXVALUE       4095
#define STEPPER_ADC_VALUE_DELTA    (STEPPER_ADC_MAXVALUE / CONFIG_ADC_STEPPER_DELTA_PC)


#define STEPPER_IS_NOISE_ALARM(x) ((x) >= ((CONFIG_ADC_STEPPER_NOISE_ALARM_VALUE * STEPPER_ADC_MAXVALUE / 100) + STEPPER_ADC_VALUE_DELTA))
#define STEPPER_IS_ALLOWED(x)     ((x) >= ((CONFIG_ADC_STEPPER_STEPPER_NOT_ALLOWED_VALUE * STEPPER_ADC_MAXVALUE / 100) + STEPPER_ADC_VALUE_DELTA))
#define STEPPER_IS_OPENED(x)      ((x) >= ((CONFIG_ADC_STEPPER_OPEN_VALUE * STEPPER_ADC_MAXVALUE / 100) - STEPPER_ADC_VALUE_DELTA) && (x) <= ((CONFIG_ADC_STEPPER_OPEN_VALUE * STEPPER_ADC_MAXVALUE / 100) + STEPPER_ADC_VALUE_DELTA))
#define STEPPER_IS_CLOSED(x)      ((x) >= ((CONFIG_ADC_STEPPER_CLOSE_VALUE * STEPPER_ADC_MAXVALUE / 100) - STEPPER_ADC_VALUE_DELTA) && (x) <= ((CONFIG_ADC_STEPPER_CLOSE_VALUE * STEPPER_ADC_MAXVALUE / 100) + STEPPER_ADC_VALUE_DELTA))

#define STEPPER_ENABLE_LIMIT_SWITCH true
#define STEPPER_ENABLE_NOISE_ALARM  false

adc_oneshot_unit_handle_t adc_limit_sw_handle;

#if STEPPER_ENABLE_NOISE_ALARM
static void stepper_noise_alarm_task(void*);
#endif

bool stepper_is_close_position_reached() {
#if STEPPER_ENABLE_LIMIT_SWITCH
	int value = 0;
	esp_err_t res = adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
	if (res != ESP_OK) {
		return true;
	}

	if (!STEPPER_IS_ALLOWED(value)) {
		return true;
	}

	return STEPPER_IS_CLOSED(value);
#else
	return true;
#endif
}

bool stepper_is_open_position_reached() {
#if STEPPER_ENABLE_LIMIT_SWITCH
	int value = 0;
	esp_err_t res = adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
	if (res != ESP_OK) {
		return true;
	}

	if (!STEPPER_IS_ALLOWED(value)) {
		return true;
	}

	return STEPPER_IS_OPENED(value);
#else
	return true;
#endif
}

bool stepper_is_stepper_allowed() {
#if STEPPER_ENABLE_LIMIT_SWITCH
	int value = 0;
	esp_err_t res = adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
	if (res != ESP_OK) {
		return true;
	}

	return STEPPER_IS_ALLOWED(value);
#else
	return true;
#endif
}

bool stepper_is_noise_alarm() {
#if STEPPER_ENABLE_NOISE_ALARM
	int value = 0;
	esp_err_t res = adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_NOISE_ALARM, &value);
	if (res != ESP_OK) {
		return true;
	}

	return STEPPER_IS_NOISE_ALARM(value);
#else
	return false;
#endif
}

void stepper_init() {
	ESP_LOGI(LOG_STEPPER, "Initializing limit switch channel...");

    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc_limit_sw_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &config));

#if CONFIG_ADC_STEPPER_CALIBRATION_MODE
    while(true) {
    	int value = 0;
    	adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_LIMITSWITCH, &value);
    	ESP_LOGI(LOG_STEPPER, "LSW Value: %d / %d%%", value, ((value * 100) / 4095));

    	adc_oneshot_read(adc_limit_sw_handle, (adc_channel_t) CONFIG_ADC_STEPPER_NOISE_ALARM, &value);
    	ESP_LOGI(LOG_STEPPER, "Noise Value: %d / %d%%", value, ((value * 100) / 4095));

    	if (!stepper_is_stepper_allowed()) {
    		ESP_LOGI(LOG_STEPPER, "Stepper disabled!");
    	} else if (stepper_is_close_position_reached()) {
    		ESP_LOGI(LOG_STEPPER, "CLose position reached!");
    	} else if (stepper_is_open_position_reached()) {
    		ESP_LOGI(LOG_STEPPER, "Open position reached!");
    	}

    	if (stepper_is_noise_alarm()) {
    		ESP_LOGI(LOG_STEPPER, "Noise alarm fired!");
    	}

    	vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
#endif

	ESP_LOGI(LOG_STEPPER, "Initializing stepper executor controller");

    t_endstops * endstops = (t_endstops *) malloc(sizeof(t_endstops));
    memset(endstops, 0, sizeof(t_endstops));

    endstops->is_close_fired = &stepper_is_close_position_reached;
    endstops->is_open_fired = &stepper_is_open_position_reached;
    endstops->is_stepper_allowed = &stepper_is_stepper_allowed;

    stepper_executor_init(endstops);

#if STEPPER_ENABLE_NOISE_ALARM
	ESP_LOGI(LOG_STEPPER, "Starting check noise alarm thread");

	xTaskCreate(stepper_noise_alarm_task, "noise alarm task", STEPPER_COMMAND_TASK_STACK_SIZE, NULL, 10, NULL);
#endif

	ESP_LOGI(LOG_STEPPER, "Stepper initialied");
}

#if STEPPER_ENABLE_NOISE_ALARM
static void stepper_noise_alarm_task(void*) {
	while(true) {
		if (stepper_is_noise_alarm()) {
			stepper_executor_on_alarm();
		}

    	vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
#endif

void stepper_calibrate() {
	stepper_executor_calibrate();
}

void stepper_move_to(uint8_t percent) {
	stepper_executor_moveto(percent);
}

void stepper_cancel() {
	stepper_executor_cancel();
}
