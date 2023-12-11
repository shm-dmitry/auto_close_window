#include "power_manager_monitor.h"

#include "power_manager.h"

#include "Arduino.h"
#include "Wire.h"

#define POWER_MANAGER_CHARGER_I2C_ADDRESS      0x09
#define POWER_MANAGER_CHARGER_I2C_TIMEOUT      1000

#define POWER_MANAGER_MON_I2C_READ_8T_WITH_TIMEOUT(timeout, var, return_timeout_value) \
          while(!Wire.available()) { \
            if (millis() > timeout) { \
              Wire.endTransmission(); \
              return return_timeout_value; \
            } \
          } \
          var = Wire.read();

uint16_t power_manager_monitor_read_16t(uint8_t reg) {
  Wire.beginTransmission(POWER_MANAGER_CHARGER_I2C_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(POWER_MANAGER_CHARGER_I2C_ADDRESS, 2, false);

  unsigned long now = millis() + POWER_MANAGER_CHARGER_I2C_TIMEOUT;

  uint8_t low = 0;
  POWER_MANAGER_MON_I2C_READ_8T_WITH_TIMEOUT(now, low,  0xFFFF);
  uint8_t high = 0;
  POWER_MANAGER_MON_I2C_READ_8T_WITH_TIMEOUT(now, high, 0xFFFF);
  
  Wire.endTransmission();

  return (high << 8) + low;
}

void power_manager_mon_write_16t(uint8_t reg, uint16_t value) {
  Wire.beginTransmission(POWER_MANAGER_CHARGER_I2C_ADDRESS);
  Wire.write(reg);

  Wire.write((uint8_t)(value - ((value >> 8) << 8)));
  Wire.write((uint8_t)(value >> 8));

  Wire.endTransmission();
}
void power_manager_monitor_process() {
  power_manager_init();

  uint8_t size = 13;
  uint8_t regs[size] = { 0x12, 0x3B, 0x38, 0x37, 0x3C, 0x3D, 0x3A, 0x14, 0x15, 0x39, 0x3F, 0xFE, 0xFF };

  uint16_t values[size] = {0};

  for (uint8_t i = 0; i<size; i++) {
    values[i] = power_manager_monitor_read_16t(regs[i]);
  }

  for (uint8_t i = 0; i<size; i++) {
    Serial.print(regs[i], HEX);
    Serial.print(" = ");
    Serial.println(values[i], HEX);
    delay(10);
  }

  Serial.println("---");

  while(true) {
    for (uint8_t i = 0; i<size; i++) {
      uint16_t x = power_manager_monitor_read_16t(regs[i]);; 
      if (values[i] != x) {
        Serial.print(regs[i], HEX);
        Serial.print(" = ");
        Serial.println(x, HEX);
        values[i] = x;
      }

      if (regs[i] == 0x14 && x == 0) {
        power_manager_mon_write_16t(regs[i], _BV(9));
      }
    }
  }
}
