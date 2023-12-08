#include "power_manager.h"

#include "Arduino.h"
#include "Wire.h"
#include "led.h"

#define POWER_MANAGER_PIN_LOCK  5

#define POWER_MANAGER_NOEVENT_POWEROFF_DELAY  20000

#define POWER_MANAGER_CHARGER_I2C_ADDRESS      0x9
#define POWER_MANAGER_CHARGER_I2C_TIMEOUT      1000

#define POWER_MANAGER_CHARGER_I2C_REG__VOLTAGE   0x15
#define POWER_MANAGER_CHARGER_I2C_REG__CURRENT   0x14
#define POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_3 0x37

// 3.6V*2 = 7.2V = 4096mV[12] + 2048mV[11] + 1024mV[10] + 32mV[5]
#define POWER_MANAGER_VOLTAGE_VALUE (_BV(12) | _BV(11) | _BV(10) | _BV(5))

// 1A ~ 1024mA = bit10
#define POWER_MANAGER_CURRENT_VALUE (_BV(10))

#define POWER_MANAGER_I2C_READ_8T_WITH_TIMEOUT(timeout, var, return_timeout_value) \
          while(!Wire.available()) { \
            if (millis() > timeout) { \
              Wire.endTransmission(); \
              return return_timeout_value; \
            } \
          } \
          var = Wire.read();

unsigned long power_manager_noevent_timer = 0;

void power_manager_configure_charger();
uint16_t power_manager_read_16t(uint8_t reg);
void power_manager_write_16t(uint8_t reg, uint16_t value);

void power_manager_init() {
  pinMode(POWER_MANAGER_PIN_LOCK, OUTPUT);
  digitalWrite(POWER_MANAGER_PIN_LOCK, HIGH);

  Wire.begin();

  power_manager_configure_charger();

  power_manager_noevent_timer = millis() + POWER_MANAGER_NOEVENT_POWEROFF_DELAY;
}

void power_manager_configure_charger() {
  // charger may be allready configured, but every start we will re-check it's configuration.

  bool ok = true;

  // 1. battery voltage
  if (power_manager_read_16t(POWER_MANAGER_CHARGER_I2C_REG__VOLTAGE) != POWER_MANAGER_VOLTAGE_VALUE) {
    power_manager_write_16t(POWER_MANAGER_CHARGER_I2C_REG__VOLTAGE, POWER_MANAGER_VOLTAGE_VALUE);
    if (power_manager_read_16t(POWER_MANAGER_CHARGER_I2C_REG__VOLTAGE) != POWER_MANAGER_VOLTAGE_VALUE) {
      ok = false;
    }
  }

  // 2. charge current limit
  if (power_manager_read_16t(POWER_MANAGER_CHARGER_I2C_REG__CURRENT) != POWER_MANAGER_CURRENT_VALUE) {
    power_manager_write_16t(POWER_MANAGER_CHARGER_I2C_REG__CURRENT, POWER_MANAGER_CURRENT_VALUE);
    if (power_manager_read_16t(POWER_MANAGER_CHARGER_I2C_REG__CURRENT) != POWER_MANAGER_CURRENT_VALUE) {
      ok = false;
    }
  }

  led_run_inform(ok ? LED_POWER_MANAGER_OK : LED_POWER_MANAGER_ERR);
}

uint16_t power_manager_read_16t(uint8_t reg) {
  Wire.beginTransmission(POWER_MANAGER_CHARGER_I2C_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(POWER_MANAGER_CHARGER_I2C_ADDRESS, 2, false);

  unsigned long now = millis() + POWER_MANAGER_CHARGER_I2C_TIMEOUT;

  uint8_t low = 0;
  POWER_MANAGER_I2C_READ_8T_WITH_TIMEOUT(now, low,  0xFFFF);
  uint8_t high = 0;
  POWER_MANAGER_I2C_READ_8T_WITH_TIMEOUT(now, high, 0xFFFF);
  
  Wire.endTransmission();

  return (high << 8) + low;
}

void power_manager_write_16t(uint8_t reg, uint16_t value) {
  Wire.beginTransmission(POWER_MANAGER_CHARGER_I2C_ADDRESS);
  Wire.write(reg);

  Wire.write((uint8_t)(value - ((value >> 8) << 8)));
  Wire.write((uint8_t)(value >> 8));

  Wire.endTransmission();
}

bool power_manager_is_charging() {
  uint16_t value = power_manager_read_16t(POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_3);
  if (value == 0xFFFF) {
    return false;
  }

  return (value & _BV(11)) ? true : false;
}

void power_manager_on_event() {
  if (power_manager_noevent_timer == 0) {
    digitalWrite(POWER_MANAGER_PIN_LOCK, HIGH); // restore HIGH state - user interacted with us during shutdown-delay
  }

  power_manager_noevent_timer = millis() + POWER_MANAGER_NOEVENT_POWEROFF_DELAY;
}

void power_manager_on_main_loop() {
  if (power_manager_noevent_timer > 0 && millis() > power_manager_noevent_timer) {
    digitalWrite(POWER_MANAGER_PIN_LOCK, LOW);
    power_manager_noevent_timer = 0;
  }
}

