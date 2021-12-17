#ifndef MAIN_BUTTONS_BUTTON_API_H_
#define MAIN_BUTTONS_BUTTON_API_H_

#include "esp_err.h"
#include "button_def.h"

esp_err_t button_setup(int gpio_button1, int gpio_button2, button_callback_t callback);

#endif /* MAIN_BUTTONS_BUTTON_API_H_ */
