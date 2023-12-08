#include "led.h"

#include "Arduino.h"
#include "led_arrays.h"

#define LED_PIN_RED 10
#define LED_PIN_GREEN 9

uint8_t led_running_type = LED_NO_COMMAND;

typedef struct {
  uint8_t array_index;
  uint8_t repeat_index;
  unsigned long delay_until;
} t_one_led_context;

t_one_led_context led_red;
t_one_led_context led_green;

void led_execute_one(const uint8_t * led_timing, t_one_led_context * context, uint8_t pin, unsigned long now);

void led_init() {
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);

  led_run_inform(LED_NO_COMMAND);
}

void led_on_main_loop() {
  if (led_running_type >= LED_DATA_ARRAY_SIZE) {
    return;
  }

  t_led_data actual_data = led_data[led_running_type];

  unsigned long now = millis();
  led_execute_one(actual_data.red,   &led_red,   LED_PIN_RED,   now);
  led_execute_one(actual_data.green, &led_green, LED_PIN_GREEN, now);

  if (led_red.repeat_index == 0xFF && led_green.repeat_index == 0xFF) {
    led_running_type = LED_NO_COMMAND;
    digitalWrite(LED_PIN_RED, HIGH); 
    digitalWrite(LED_PIN_GREEN, HIGH); 
  }
}

void led_run_inform(uint8_t type) {
  digitalWrite(LED_PIN_GREEN, HIGH);
  digitalWrite(LED_PIN_RED, HIGH);

  led_running_type = type;
  memset(&led_red, 0, sizeof(t_one_led_context));
  memset(&led_green, 0, sizeof(t_one_led_context));
}

void led_execute_one(const uint8_t * led_timing, t_one_led_context * context, uint8_t pin, unsigned long now) {
  if (context->repeat_index == 0xFF) {
    return;
  }

  uint8_t repeat_count = pgm_read_byte(&led_timing[0]);
  if (context->repeat_index >= repeat_count) {
    context->repeat_index = 0xFF;
    return;
  }

  if (now < context->delay_until) {
    return;
  }

  uint8_t array_size = pgm_read_byte(&led_timing[1]);
  if (context->array_index >= array_size * 2) {
    context->repeat_index++;
    context->array_index = 0;
    if (context->repeat_index >= repeat_count) {
      digitalWrite(pin, HIGH); 
    }
    return;
  }

  uint8_t delay = pgm_read_byte(&led_timing[context->array_index + 2]);
  if (delay == 0) {
    context->array_index++;
    return;
  }

  digitalWrite(pin, ((context->array_index % 2) == 0) ? LOW : HIGH);
  context->delay_until = now + delay;
  context->array_index++;
}
