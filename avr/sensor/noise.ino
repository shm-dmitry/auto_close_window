#define NOISE_STROBE_PIN 1
#define NOISE_RESET_PIN 1
#define NOISE_OUT_PIN 1

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

bool noise_read_level(uint8_t * buffer) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(NOISE_STROBE_PIN, LOW);
    delayMicroseconds(100);

    buffer[i] = map(analogRead(NOISE_OUT_PIN), 0, 1023, 0, 255);

    digitalWrite(NOISE_STROBE_PIN, HIGH);
    delayMicroseconds(100);
  }
}
