void setup() {
  gpio_logger_init();
//  noise_init();
  bmp280_initialize();
//  sgp30_initialize();
}

void loop() {
  //test_noise_level();
  test_bmp280();
  delay(1000);
}

void test_bmp280() {
  gpio_logger_send_message("T = %i", bmp280_read_temperature());
}

void test_sgp30() {
  sgp30_calibrate_if_need();
  gpio_logger_send_message("TVOC = %u", sgp30_read_tvoc());
}

void test_noise_level() {
    uint16_t freq[7] = { 63, 160, 400, 1000, 2500, 6250, 16000 };
    uint16_t noise_level[7] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF};
    noise_read_level(noise_level);
    for (int i = 0; i<7; i++) {
      gpio_logger_send_message("F %i = %u", freq[i], noise_level[i]);
    }
    gpio_logger_send_message("------");
}
