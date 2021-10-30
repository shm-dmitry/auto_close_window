#define DEBUG_SERIAL

#include <Adafruit_BMP280.h>
 
Adafruit_BMP280 bmp280;

void bmp280_initialize() {
  if (!bmp280.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    Serial.println("BMP280 INIT ERROR");
  } else {
    bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,
                       Adafruit_BMP280::SAMPLING_X2,
                       Adafruit_BMP280::SAMPLING_X16,
                       Adafruit_BMP280::FILTER_X16,
                       Adafruit_BMP280::STANDBY_MS_500);

    Serial.println("BMP280 OK");
  }
}

int8_t bmp280_read_temperature() {
  return bmp280.readTemperature();
}
