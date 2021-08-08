void setup() {
  wire_logger_init();
  noise_init();
  bmp280_initialize();
  sgp30_initialize();
}

void loop() {\
  sgp30_calibrate_if_need();

  
  while (true) {
    wire_logger_send("T = %i", bmp280_read_temperature());
    wire_logger_send("TVOC = %i", sgp30_read_tvoc());
    uint8_t noise_level[7];
    noise_read_level(noise_level);
    wire_logger_send("NOISE = %i %i %i %i %i %i %i", noise_level[0], noise_level[1], noise_level[2], noise_level[3], noise_level[4], noise_level[5], noise_level[6]);
    delay(1000);
  }
}
