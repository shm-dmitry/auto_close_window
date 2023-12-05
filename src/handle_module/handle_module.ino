#include "power_manager.h"
#include "led.h"
#include "user_input.h"
#include "fm_receiver.h"
#include "fm_sender.h"
#include "controller.h"

void setup() {
  power_manager_init();

  led_init();
  user_input_init();
  fm_sender_init();
  fm_receiver_init();
}

void loop() {
  controller_on_main_loop();
  power_manager_on_main_loop();
  led_on_main_loop();
}
