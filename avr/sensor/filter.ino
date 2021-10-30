#define FILTER_ALARM_COUNT_BEFORE_SEND         10
#define FILTER_REPEAT_ALARM                    (1000000 * 30)
#define FILTER_ALARM_VALUE_TVOC                300
#define FILTER_ALARM_VALUE_MIN_VOLUME          300
#define FILTER_ALARM_VALUE_MIN_HORN_FREQ_MIN   600
#define FILTER_ALARM_VALUE_MIN_HORN_FREQ_MAX   1200
#define FILTER_TVOC_UNKNOWN                    0xFFFF

unsigned long filter_last_send_request = 0;
uint8_t filter_alarm_counter = 0;
bool filter_in_alarm_mode = false;

bool filter_check_alarm(uint16_t tvoc, const noise_data_t * noise) {
  if (tvoc > FILTER_ALARM_VALUE_TVOC && tvoc != FILTER_TVOC_UNKNOWN) {
    return true;
  }

  if (noise != NULL && noise->count > 0) {
    // 1. check max volume. It is 1st element..
    if (noise->volume[0] > FILTER_ALARM_VALUE_MIN_VOLUME) {
      return true;
    }

    // 2. check for a ambulance horn
    for (int i = 0; i<noise->count; i++) {
      if (noise->freq[i] > FILTER_ALARM_VALUE_MIN_HORN_FREQ_MIN &&
          noise->freq[i] < FILTER_ALARM_VALUE_MIN_HORN_FREQ_MAX) {
        return true;
      }
    }
  }

  return false;
}

bool is_need_send_sensor_data(int8_t temperature, uint16_t tvoc, const noise_data_t * noise) {
  if (filter_last_send_request == 0) {
    filter_last_send_request = micros();
    
    if (filter_check_alarm(tvoc, noise)) {
      filter_alarm_counter = 1;
    } else {
      filter_alarm_counter = 0;
    }
    
    return true;
  }

  if (filter_check_alarm(tvoc, noise)) {
    filter_alarm_counter++;
    if (filter_alarm_counter >= FILTER_ALARM_COUNT_BEFORE_SEND) {
      filter_alarm_counter = FILTER_ALARM_COUNT_BEFORE_SEND;
      
      if (!filter_in_alarm_mode) {
        filter_in_alarm_mode     = true;
        filter_last_send_request = micros();
        return true;
      } else if (micros() - filter_last_send_request > FILTER_REPEAT_ALARM) {
        filter_last_send_request = micros();
        return true;
     } else {
        // alarm mode not changed, time-to-repeat does not come, do nothing
        return false;
     }
    } else {
        return false;
    }
  } else {
    if (filter_alarm_counter == 1) {
      filter_alarm_counter = 0;

      if (filter_in_alarm_mode) {
        filter_in_alarm_mode     = false;
        filter_last_send_request = micros();
        return true;
      } else {
        return false;
      }
    } else {
      filter_alarm_counter--;
      return false;
    }
  }

  return false;
}
