#ifndef MAIN_STEPPER_STEPPER_ADC_H_
#define MAIN_STEPPER_STEPPER_ADC_H_

#include "stepper_def.h"

t_endstops * stepper_adc_init();
bool stepper_adc_is_noise_alarm_fired();
void stepper_adc_lsw_enable(bool enabled);
void stepper_adc_publish_status();

#endif /* MAIN_STEPPER_STEPPER_ADC_H_ */
