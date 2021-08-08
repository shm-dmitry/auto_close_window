#include <Wire.h>
#include "Adafruit_SGP30.h"
#include <avr/eeprom.h>

Adafruit_SGP30 sgp30;
bool sgp30_calibrated = false;

bool init_sgp30_baseline() {
  uint16_t TVOC_base = eeprom_read_word(0);
  uint16_t eCO2_base = eeprom_read_word(2);

  // TODO: how to reset calibration?

  if (TVOC_base != 0x0000 && TVOC_base != 0xFFFF && eCO2_base != 0x0000 && eCO2_base != 0xFFFF) {
    if (sgp30.setIAQBaseline(eCO2_base, TVOC_base)) {
      return true;
    }
  }

  int count = 0;
  while (count <= 30) {
    delay(1000);

    wire_logger_send("SGP30 CAL");

    if (!sgp30.IAQmeasure() || !sgp30.IAQmeasureRaw()) {
      continue;
    }

    wire_logger_send("SGP30 CAL OK");
    count++;
  }

  if (!sgp30.getIAQBaseline(&eCO2_base, &TVOC_base)) {
    return false;
  }

  eeprom_write_word(0, TVOC_base);
  eeprom_write_word(2, eCO2_base);

  return true;
}

void sgp30_initialize() {
  if (!sgp30.begin()) {
    wire_logger_send("SGP30 INIT ERROR");
  }
}

void sgp30_calibrate_if_need() {
  if (sgp30_calibrated) {
    return sgp30_calibrated;
  }
  
  if (!init_sgp30_baseline()) {
    wire_logger_send("SGP30 BASELINE ERROR");
    sgp30_calibrated = true;
  } else {
    wire_logger_send("SGP30 OK");
  }
}

uint16_t sgp30_read_tvoc() {
  if (!sgp30.IAQmeasure()) {
    return 0xFFFF;
  }

  return sgp30.TVOC;
}
