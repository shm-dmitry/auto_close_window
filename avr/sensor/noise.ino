#define NOISE_STROBE_PIN PIN_PA6
#define NOISE_RESET_PIN PIN_PA7
#define NOISE_OUT_PIN PIN_PA5

void noise_init() {
  pinMode(NOISE_STROBE_PIN, OUTPUT);
  pinMode(NOISE_RESET_PIN,  OUTPUT);
  pinMode(NOISE_OUT_PIN,    INPUT);

  digitalWrite(NOISE_RESET_PIN,  LOW);
  digitalWrite(NOISE_STROBE_PIN, LOW);
  delay(1);

  digitalWrite (NOISE_RESET_PIN,  HIGH);
  delay(1);
  digitalWrite (NOISE_RESET_PIN,  LOW);
  digitalWrite (NOISE_STROBE_PIN, HIGH);
  delay(1);
}

bool noise_read_level(uint16_t * buffer) {
  digitalWrite(NOISE_RESET_PIN,  HIGH);
  digitalWrite(NOISE_STROBE_PIN, HIGH);
  delayMicroseconds(100);
  digitalWrite(NOISE_STROBE_PIN, LOW);
  delayMicroseconds(200);
  digitalWrite (NOISE_RESET_PIN,  LOW);
  delayMicroseconds(10);

  for (int i = 0; i < 7; i++) {
    digitalWrite(NOISE_STROBE_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(NOISE_STROBE_PIN, LOW);
    delayMicroseconds(35);

    buffer[i] = analogRead(NOISE_OUT_PIN);
//    buffer[i] = map(analogRead(NOISE_OUT_PIN), 0, 1023, 0, 255);

    delayMicroseconds(300);
  }
}
