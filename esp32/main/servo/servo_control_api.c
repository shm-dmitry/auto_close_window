#include "servo_control_api.h"

#include "driver/ledc.h"
#include "../log.h"

#define SERVO_TIME_ROTATE_0			600
#define SERVO_TIME_ROTATE_180		2400
#define SERVO_TIME_ZERO				(5 * 10)
#define SERVO_FULL_TIME				(SERVO_TIME_ROTATE_180 + SERVO_TIME_ZERO)

#define SERVI_TIME2FREQ(time)		(1000000 / time)

#define SERVO_TIME(angle)			(SERVO_TIME_ROTATE_0 + angle * (SERVO_TIME_ROTATE_180 - SERVO_TIME_ROTATE_0) / 180)
#define SERVO_FREQ					SERVI_TIME2FREQ(SERVO_FULL_TIME)
#define SERVO_DUTY(angle)			((SERVO_TIME(angle) * 0xFF) / SERVO_FULL_TIME)

#define SERVO_CONTROL_CHANNEL   LEDC_CHANNEL_3
#define SERVO_CONTROL_TIMER     LEDC_TIMER_2
#define SERVO_CONTROL_SPEED     LEDC_LOW_SPEED_MODE

esp_err_t servo_control_api_init(int gpio) {
    ledc_timer_config_t ledc_timer = {
		.duty_resolution = LEDC_TIMER_8_BIT, // resolution of PWM duty
		.freq_hz = SERVO_FREQ,             // frequency of PWM signal
		.speed_mode = SERVO_CONTROL_SPEED,         // timer mode
		.timer_num = SERVO_CONTROL_TIMER,          // timer index
		.clk_cfg = LEDC_AUTO_CLK,            // Auto select the source clock
    };

    esp_err_t res = ledc_timer_config(&ledc_timer);
    if (res) {
    	ESP_LOGE(SERVO_CONTROL_LOG, "ledc_timer_config error %d", res);
    	return res;
    }

    ledc_channel_config_t cfg = {
		.channel    = SERVO_CONTROL_CHANNEL,
		.duty       = 0,
		.gpio_num   = gpio,
		.speed_mode = SERVO_CONTROL_SPEED,
		.hpoint     = 0,
		.timer_sel  = SERVO_CONTROL_TIMER
    };

	res = ledc_channel_config(&cfg);
	if (res) {
    	ESP_LOGE(SERVO_CONTROL_LOG, "ledc_channel_config error %d for pin %d", res, gpio);
		return res;
	}

	res = ledc_fade_func_install(0);
	if (res && res != ESP_ERR_NOT_FOUND) {
		ESP_LOGE(SERVO_CONTROL_LOG, "ledc_fade_func_install error %d", res);
		return res;
	}

	ESP_LOGI(SERVO_CONTROL_LOG, "Driver initialized on port %d on speed %d hz", gpio, ledc_timer.freq_hz);

	return ESP_OK;
}

esp_err_t servo_control_api_rotate(uint8_t duty) {
	esp_err_t res = ledc_set_duty(SERVO_CONTROL_SPEED, SERVO_CONTROL_CHANNEL, duty);
	if (res) {
		ESP_LOGE(SERVO_CONTROL_LOG, "set duty :: ledc_set_duty() error %d", res);
		return res;
	}


	res = ledc_update_duty(SERVO_CONTROL_SPEED, SERVO_CONTROL_CHANNEL);
	if (res) {
		ESP_LOGE(SERVO_CONTROL_LOG, "change duty :: ledc_update_duty() error %d", res);
		return res;
	}

	ESP_LOGI(SERVO_CONTROL_LOG, "Duty changed to %d", duty);

	return res;
}

esp_err_t servo_control_api_off() {
	return servo_control_api_rotate(0);
}

esp_err_t servo_control_api_rotate_to(uint8_t angle) {
	if (angle > 180) {
		angle = 180;
	}

	return servo_control_api_rotate(SERVO_DUTY(angle));
}
