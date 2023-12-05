#include "led.h"

#include "Arduino.h"

#define LED_PIN_RED 10
#define LED_PIN_GREEN 9

void led_init() {
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);

  digitalWrite(LED_PIN_GREEN, HIGH);
  digitalWrite(LED_PIN_RED, HIGH);
}

void led_on_main_loop() {

}

void led_run_inform(uint8_t type) {

}
