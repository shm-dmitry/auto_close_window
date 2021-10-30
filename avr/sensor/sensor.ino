struct noise_data_t {
   uint16_t * freq;
   uint16_t * volume;
   uint8_t count;
} ;

void setup() {
  gpio_logger_init();
  noise_init();
  bmp280_initialize();
  sgp30_initialize();
  data_transfer_init();
}

void loop() {
  test_filter();
 // test_noise_level();
 // test_bmp280();
  delay(2000);
}

void test_filter() {
  noise_data_t * noise = noise_read_level();
  int8_t temperature = bmp280_read_temperature();
  uint16_t tvoc = sgp30_read_tvoc();

  if (is_need_send_sensor_data(temperature, tvoc, noise)) {
    gpio_logger_send_message("Send data: ");
    gpio_logger_send_message("T = %i", temperature);
    gpio_logger_send_message("TVOC = %u", tvoc);
    if (noise != NULL) {
      gpio_logger_send_message("Noise: ");
  
      for (int i = 0; i<noise->count; i++) {
        gpio_logger_send_message("Major freq[%u] = %u", noise->freq[i], noise->volume[i]);
      }
    } else {
      gpio_logger_send_message("No noise");
    }

    data_transfer_send(temperature, tvoc, noise);
  }

  if (noise != NULL) {
    free(noise->freq);
    free(noise->volume);
    free(noise);
  }
}

void test_bmp280() {
  gpio_logger_send_message("T = %i", bmp280_read_temperature());
}

void test_sgp30() {
  sgp30_calibrate_if_need();
  gpio_logger_send_message("TVOC = %u", sgp30_read_tvoc());
}

void test_noise_level() {
    gpio_logger_send_message("Start measurement");
    noise_data_t * data = noise_read_level();
    if (data == NULL) {
      return;
    }

    gpio_logger_send_message("----- count == %d ------", data->count);

    for (int i = 0; i<data->count; i++) {
      gpio_logger_send_message("Major freq[%d] = %d", data->freq[i], data->volume[i]);
    }

    free(data->freq);
    free(data->volume);
    free(data);
}
