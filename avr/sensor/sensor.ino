struct noise_data_t {
   uint16_t * freq;
   uint16_t * volume;
   uint8_t count;
} ;

void setup() {
  Serial.begin(9600);

  bmp280_initialize();
  sgp30_initialize();
  noise_init();
  data_transfer_init();
}

void loop() {
  test_filter();
//  delay(2000);
}

void test_filter() {
  noise_data_t * noise = noise_read_level();
  int8_t temperature = 0;//bmp280_read_temperature();
  uint16_t tvoc = 0;//sgp30_read_tvoc();

  if (is_need_send_sensor_data(temperature, tvoc, noise) || true) {
    Serial.println("Send datva: ");
    Serial.print("T = ");
    Serial.println(temperature);
    Serial.print("TVOC = ");
    Serial.println(tvoc);
    if (noise != NULL) {
      Serial.println("Noise: ");
  
      for (int i = 0; i<noise->count; i++) {
        Serial.print("Major freq[");
        Serial.print(noise->freq[i]);
        Serial.print("] = ");
        Serial.println(noise->volume[i]);
      }
    } else {
      Serial.println("No noise");
    }

    data_transfer_send(temperature, tvoc, noise);
  }

  if (noise != NULL) {
    free(noise->freq);
    free(noise->volume);
    free(noise);
  }
}
