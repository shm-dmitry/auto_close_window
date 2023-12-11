#include "power_manager.h"
#include "led.h"
#include "user_input.h"
#include "fm_receiver.h"
#include "fm_sender.h"
#include "controller.h"
#include "fm_decoder.h"
//#include "power_manager_monitor.h"

void setup() {
  Serial.begin(115200);

//  power_manager_monitor_process();

  led_init();

  power_manager_init();

  user_input_init();
  fm_sender_init();
  fm_receiver_init();
}

void loop() {
  fm_decoder_on_main_loop();
  controller_on_main_loop();
  power_manager_on_main_loop();
  fm_sender_on_main_loop();
  led_on_main_loop();
}
