#include "power_manager.h"

#include "Arduino.h"
#include "Wire.h"
#include "led.h"
#include "controller.h"
#include <Adafruit_INA219.h>

#define POWER_MANAGER_PIN_LOCK  5

#define POWER_MANAGER_NOEVENT_POWEROFF_DELAY  20000

#define POWER_MANAGER_I2C_TIMEOUT             1000

#define POWER_MANAGER_CHARGER_I2C_ADDRESS      0x09

#define POWER_MANAGER_BAT_STATUS_I2C_ADDRESS   0x4A

#define POWER_MANAGER_CHARGER_I2C_RECHECK_CONFIG       5000

#define POWER_MANAGER_CHARGER_I2C_REG__VOLTAGE         0x15
#define POWER_MANAGER_CHARGER_I2C_REG__CURRENT         0x14
#define POWER_MANAGER_CHARGER_I2C_REG__INPUT_CURRENT   0x3F
#define POWER_MANAGER_CHARGER_I2C_REG__DISCH_CURRENT   0x39
#define POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_0       0x12
#define POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_1       0x3B
#define POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_2       0x38
#define POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_3       0x37
#define POWER_MANAGER_CHARGER_I2C_REG__PROCHOT_0       0x3C
#define POWER_MANAGER_CHARGER_I2C_REG__PROCHOT_1       0x3D
#define POWER_MANAGER_CHARGER_I2C_REG__PROCHOT_STATUS  0x3A

// 3.6V*2 = 7.2V = 4096mV[12] + 2048mV[11] + 1024mV[10] + 32mV[5]
#define POWER_MANAGER_VOLTAGE_VALUE (_BV(12) | _BV(11) | _BV(10) | _BV(5))

// 1A ~ 1024mA = bit10
//#define POWER_MANAGER_CURRENT_VALUE (_BV(10))
// 0.3A ~ 384mA = bit7 + bit8
#define POWER_MANAGER_CURRENT_VALUE (_BV(7) | _BV(8))


// 1.5A = 1024mA[10] + 512mA[9]
#define POWER_MANAGER_INPUT_CURRENT (_BV(10) | _BV(9)) 

// 0.5A = 512mA[9]
#define POWER_MANAGER_DISCH_CURRENT (_BV(9)) 

// EN_LWPWR - enable          [15 = 1]
// WDTMR_ADJ - disable        [14:13 = 00]
// freq = 800 kHz             [9:8 = 01]
// EN_LEARN - disable         [5 = 0]
// IADP_GAIN = 20x (unused)   [4 = 0]
// IDCHG Amplifier Gain = 8x  ]3 = 0]
// CHRG_INHIBIT enable charge [0 = 0]
#define POWER_MANAGER_OPTIONS_0 (_BV(15) | _BV(8))

// Battery Depletion Threshold = 60% [15:14 = 00]
// EN_IDCHG - disable        [[11 = 0]
// RSNS_RATIO - unused       [[13:12 = 11]
// EN_IDCHG - disable        [[11 = 0]
// EN_PMON - disable         [[10 = 0]
// PMON_RATIO - default      [[9 = 1]
// CMP_REF - unused          [[7 = 0]
// CMP_POL - unused          [[6 = 0]
// CMP_DEG - disable         [5:4 = 00]
// EN_FET_LATCHOFF - unused  [3 = 0]
// EN_SHIP_DCHG - disable    [1 = 0]
#define POWER_MANAGER_OPTIONS_1 (_BV(13) | _BV(12) | _BV(9))

// External Current Limit Enable = regs only [7 = 0]
// other bits - as default                   [9:8 = 11; 2 = 1]
#define POWER_MANAGER_OPTIONS_2 (_BV(9) | _BV(8) | _BV(2))

// EN_IDCHG_REG - disable      [15 = 1]
// ACOK_DEG - deglich 1.3 sec  [12 = 1]
// EN_ACOC  - enable           [10 = 1]
// ACOC_VTH - 200%             [9  = 1]
// IFAULT_HI - enable          [7  = 1]
// IFAULT_LO - enable          [6  = 1]
// FDPM_VTH - default          [5  = 0]
// FDPM_DEG - default          [4:3 = 00]
// EN_BOOST - disable          [2 = 0]
#define POWER_MANAGER_OPTIONS_3 (_BV(15) | _BV(12) | _BV(10) | _BV(9) | _BV(7) | _BV(6))

// ICRIT Threshold = 110% [15:11 == 00000]
// ICRIT_DEG = 800 μs [10:9 = 11]
// VSYS_VTH = 5.75 V [7:6 = 00]
// EN_PROCHOT_EXT en [5 = 1]
// PROCHOT Pulse Width 10 ms [4:3 = 10]
// PROCHOT_CLEAR [2 = 1]
// INOM_DEG = 60mS [1 = 1]
#define POWER_MANAGER_PROCHOT_0 (_BV(10) | _BV(9) | _BV(5) | _BV(4) | _BV(2) | _BV(1))

// IDCHG_VTH = 16384 mA [15:10 = 100000]
// IDCHG_DEG = 12 ms [9:8 = 11]
// PROCHOT PROFILE = all except VSYS [6:0 = 1111011]
#define POWER_MANAGER_PROCHOT_1 (_BV(15) | _BV(9) | _BV(8) | _BV(6) | _BV(5) | _BV(4) | _BV(3) | _BV(1) | _BV(0))

#define POWER_MANAGER_I2C_READ_8T_WITH_TIMEOUT(timeout, var, return_timeout_value) \
          while(!Wire.available()) { \
            if (millis() > timeout) { \
              Wire.endTransmission(); \
              return return_timeout_value; \
            } \
          } \
          var = Wire.read();

#define POWER_MANAGER_NOEVENT_TIMER_ENABLED  true

#define POWER_MANAGER_MIN_CHARGE_CURRENT_TO_STOP_CHARGER 10

#if POWER_MANAGER_NOEVENT_TIMER_ENABLED
unsigned long power_manager_noevent_timer = 0;
#endif
unsigned long power_manager_i2c_next_recheck_config = 0;

Adafruit_INA219 ina219(POWER_MANAGER_BAT_STATUS_I2C_ADDRESS);         // Создаем объект ina219

void power_manager_batstatus_shutdown();
void power_manager_configure_charger();
void power_manager_configure_batstatus();
uint16_t power_manager_read_16t(uint8_t reg, uint8_t address);
void power_manager_write_16t(uint8_t reg, uint16_t value, uint8_t address);
void power_manager_check_write_16t(uint8_t reg, uint16_t value, uint8_t address);

void power_manager_init() {
  pinMode(POWER_MANAGER_PIN_LOCK, OUTPUT);
  digitalWrite(POWER_MANAGER_PIN_LOCK, HIGH);

  Wire.begin();

  power_manager_configure_charger();
  power_manager_configure_batstatus();

#if POWER_MANAGER_NOEVENT_TIMER_ENABLED
  power_manager_noevent_timer = millis() + POWER_MANAGER_NOEVENT_POWEROFF_DELAY;
#endif
}

void power_manager_configure_charger() {
  // charger may be allready configured, but every start we will re-check it's configuration.

  // 1. battery voltage
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__VOLTAGE, POWER_MANAGER_VOLTAGE_VALUE, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 2. charge current limit
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__CURRENT, POWER_MANAGER_CURRENT_VALUE, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 3. input current limit
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__INPUT_CURRENT, POWER_MANAGER_INPUT_CURRENT, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 4. input current limit
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__DISCH_CURRENT, POWER_MANAGER_DISCH_CURRENT, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 5. opt-0
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_0, POWER_MANAGER_OPTIONS_0, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 6. opt-1
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_1, POWER_MANAGER_OPTIONS_1, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 7. opt-2
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_2, POWER_MANAGER_OPTIONS_2, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 8. opt-3
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_3, POWER_MANAGER_OPTIONS_3, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 9. prochot-0
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__PROCHOT_0, POWER_MANAGER_PROCHOT_0, POWER_MANAGER_CHARGER_I2C_ADDRESS);

  // 9. prochot-1
  power_manager_check_write_16t(POWER_MANAGER_CHARGER_I2C_REG__PROCHOT_1, POWER_MANAGER_PROCHOT_1, POWER_MANAGER_CHARGER_I2C_ADDRESS);
}

void  power_manager_configure_batstatus() {
  ina219.begin();
}

uint16_t power_manager_read_16t(uint8_t reg, uint8_t address) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(address, 2, false);

  unsigned long now = millis() + POWER_MANAGER_I2C_TIMEOUT;

  uint8_t low = 0;
  POWER_MANAGER_I2C_READ_8T_WITH_TIMEOUT(now, low,  0xFFFF);
  uint8_t high = 0;
  POWER_MANAGER_I2C_READ_8T_WITH_TIMEOUT(now, high, 0xFFFF);
  
  Wire.endTransmission();

  return (high << 8) + low;
}

void power_manager_write_16t(uint8_t reg, uint16_t value, uint8_t address) {
  Wire.beginTransmission(address);
  Wire.write(reg);

  Wire.write((uint8_t)(value - ((value >> 8) << 8)));
  Wire.write((uint8_t)(value >> 8));

  Wire.endTransmission();
}

void power_manager_check_write_16t(uint8_t reg, uint16_t val, uint8_t address)  {
  if (power_manager_read_16t(reg, address) != val) { 
    power_manager_write_16t(reg, val, address); 
  }
}

bool power_manager_is_charging() {
  uint16_t value = power_manager_read_16t(POWER_MANAGER_CHARGER_I2C_REG__OPTIONS_3, POWER_MANAGER_CHARGER_I2C_ADDRESS);
  if (value == 0xFFFF) {
    return false;
  }

  if (!(value & _BV(11))) { // chech adapter present
    return false;
  }

  uint16_t v = 0;
  int16_t i = 0;

  power_manager_read_batstatus(v, i);

  return i > POWER_MANAGER_MIN_CHARGE_CURRENT_TO_STOP_CHARGER;
}

void power_manager_on_event() {
  #if POWER_MANAGER_NOEVENT_TIMER_ENABLED
  if (power_manager_noevent_timer == 0) {
    digitalWrite(POWER_MANAGER_PIN_LOCK, HIGH); // restore HIGH state - user interacted with us during shutdown-delay

    power_manager_configure_batstatus();
  }

  power_manager_noevent_timer = millis() + POWER_MANAGER_NOEVENT_POWEROFF_DELAY;
  #endif
}

void power_manager_on_main_loop() {
#if POWER_MANAGER_NOEVENT_TIMER_ENABLED
  if (power_manager_noevent_timer > 0 && millis() > power_manager_noevent_timer) {
    power_manager_batstatus_shutdown();

    digitalWrite(POWER_MANAGER_PIN_LOCK, LOW);
    power_manager_noevent_timer = 0;
  }
#endif

  if (millis() > power_manager_i2c_next_recheck_config) {
    // check prochot to print error
    uint16_t prochot_status = power_manager_read_16t(POWER_MANAGER_CHARGER_I2C_REG__PROCHOT_STATUS, POWER_MANAGER_CHARGER_I2C_ADDRESS);
    if (prochot_status != 0 && prochot_status != 0b00000001) {
      Serial.print("PROCHOT STATUS ERR ");
      Serial.println(prochot_status, HEX);

      controller_on_charger_error(prochot_status);
    }
    
    power_manager_i2c_next_recheck_config = millis() + POWER_MANAGER_CHARGER_I2C_RECHECK_CONFIG;
    power_manager_configure_charger();
  }
}

void power_manager_batstatus_shutdown() {
  ina219.powerSave(true);
}

void power_manager_read_batstatus(uint16_t & voltage_mv, int16_t & current_ma) {
  current_ma = -(int16_t)(ina219.getCurrent_mA() * 10.0);
  voltage_mv = (uint16_t)(ina219.getBusVoltage_V() * 1000.0);
}

