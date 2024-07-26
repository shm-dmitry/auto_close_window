#include "power_manager.h"
#include "led.h"
#include "user_input.h"
#include "fm_receiver.h"
#include "fm_sender.h"
#include "controller.h"
#include "fm_decoder.h"
//#include "power_manager_monitor.h"

unsigned long now = 0;

void setup() {
  delay(1000);

  Serial.begin(9600);

  Serial.println("Starting");

//  power_manager_monitor_process();

  led_init();

  power_manager_init();

  user_input_init();
  fm_sender_init();
  fm_receiver_init();

  Serial.println("Firmware initialized");
}

void loop() {
  fm_decoder_on_main_loop();
  controller_on_main_loop();
  power_manager_on_main_loop();
  fm_sender_on_main_loop();
  led_on_main_loop();

  if (millis() > now) {
    now = millis() + 10000;

    uint16_t voltage_mv = 0;
    int16_t current_ma = 0;
    power_manager_read_batstatus(voltage_mv, current_ma);

    Serial.print("BAT: V = ");
    Serial.print(voltage_mv);
    Serial.print(" mV; I = ");
    Serial.print(current_ma);
    Serial.println(" mA");
  }
}
