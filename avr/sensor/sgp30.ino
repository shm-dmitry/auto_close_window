#include "Adafruit_SGP30.h"
#include <avr/eeprom.h>

// WARNING! This values unique for every sensor.
// If you want use fast-hardcoded-calibration - execute full calibration first time
// And write here your own numbers.
// You must change this numbers if you change sensor module!
#define SGP30_CALIBRADE_ECO2 0x8B46 
#define SGP30_CALIBRADE_TVOC 0x86D1

Adafruit_SGP30 sgp30;
bool sgp30_calibrated = false;

bool init_sgp30_baseline() {
  uint16_t TVOC_base = eeprom_read_word(0);
  uint16_t eCO2_base = eeprom_read_word(2);

  // TODO: how to reset calibration?
  if (TVOC_base != 0x0000 && TVOC_base != 0xFFFF && eCO2_base != 0x0000 && eCO2_base != 0xFFFF) {
    Serial.println("SGP30 Readed baseline from NVS");
    
    if (sgp30.setIAQBaseline(eCO2_base, TVOC_base)) {
      return true;
    }
  }

  #ifdef SGP30_CALIBRADE_ECO2 && SGP30_CALIBRADE_TVOC
  eCO2_base = SGP30_CALIBRADE_ECO2;
  TVOC_base = SGP30_CALIBRADE_TVOC;
  Serial.println("SGP30 Used hardcoded baseline: ");
  
  if (sgp30.setIAQBaseline(eCO2_base, TVOC_base)) {
    return true;
  }
  #endif

  Serial.println("SGP30 start calibration");

  int count = 0;
  while (count <= 30) {
    delay(1000);

    if (!sgp30.IAQmeasure() || !sgp30.IAQmeasureRaw()) {
      Serial.println("SGP30 Calibration err");
      continue;
    }

    count++;
  }

  if (!sgp30.getIAQBaseline(&eCO2_base, &TVOC_base)) {
    return false;
  }

  Serial.println("SGP30 Calibration done. Baseline: ");
  Serial.print(eCO2_base);
  Serial.print(" / ");
  Serial.println(TVOC_base);

  eeprom_write_word(0, TVOC_base);
  eeprom_write_word(2, eCO2_base);

  return true;
}

void sgp30_initialize() {
  if (!sgp30.begin()) {
    Serial.println("SGP30 INIT ERROR");
  }
}

void sgp30_calibrate_if_need() {
  if (sgp30_calibrated) {
    return;
  }
  
  if (!init_sgp30_baseline()) {
    Serial.println("SGP30 BASELINE ERROR");
  } else {
    sgp30_calibrated = true;
  }
}

uint16_t sgp30_read_tvoc() {
  if (!sgp30.IAQmeasure()) {
    return 0xFFFF;
  }

  return sgp30.TVOC;
}
