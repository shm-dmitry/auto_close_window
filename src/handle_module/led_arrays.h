#ifndef LED_ARRAYS_H_
#define LED_ARRAYS_H_

// array format: [repeat-count; on-off-pairs-count; on-time-ms; off-time-ms; on-time-ms; off-time-ms; ...]

const uint8_t led_green_OPEN[]               PROGMEM = { 10, 1, 100, 100 };
const uint8_t led_red_OPEN[]                 PROGMEM = { 0, 0 };

const uint8_t led_green_CLOSE[]              PROGMEM = { 0, 0 };
const uint8_t led_red_CLOSE[]                PROGMEM = { 10, 1, 100, 100 };

const uint8_t led_green_CALIBRATE_START[]    PROGMEM = { 10, 3, 100, 100, 100, 100, 0, 200 };
const uint8_t led_red_CALIBRATE_START[]      PROGMEM = { 10, 3, 0, 200, 0, 200, 100, 100 };

const uint8_t led_green_CALIBRATE_PREENTER[] PROGMEM = { 10, 2, 0, 100, 100, 0 };
const uint8_t led_red_CALIBRATE_PREENTER[]   PROGMEM = { 10, 2, 100, 0, 0, 100 };

const uint8_t led_green_CALIBRATE_END[]      PROGMEM = { 10, 1, 100, 0 };
const uint8_t led_red_CALIBRATE_END[]        PROGMEM = { 0, 0 };

const uint8_t led_green_DONE_EXECUTION[]     PROGMEM = { 0, 0 };
const uint8_t led_red_DONE_EXECUTION[]       PROGMEM = { 0, 0 };

const uint8_t led_green_FIND_POSITION[]      PROGMEM = { 10, 4, 0, 250, 0, 250, 250, 0, 250, 0 };
const uint8_t led_red_FIND_POSITION[]        PROGMEM = { 10, 4, 250, 0, 250, 0, 0, 250, 0, 250 };

typedef struct {
  const uint8_t * red;
  const uint8_t * green;
} t_led_data;

#define LED_DATA_ARRAY_SIZE 7

t_led_data led_data[LED_DATA_ARRAY_SIZE] = {
  { .red = led_red_OPEN,               .green = led_green_OPEN },
  { .red = led_red_CLOSE,              .green = led_green_CLOSE },
  { .red = led_red_CALIBRATE_START,    .green = led_green_CALIBRATE_START },
  { .red = led_red_CALIBRATE_PREENTER, .green = led_green_CALIBRATE_PREENTER },
  { .red = led_red_CALIBRATE_END,      .green = led_green_CALIBRATE_END },
  { .red = led_red_DONE_EXECUTION,     .green = led_green_DONE_EXECUTION },
  { .red = led_red_FIND_POSITION,      .green = led_green_FIND_POSITION },
};

#endif /* #define LED_ARRAYS_H_ */
