void setup() {
  DDRB |= 1;
  wire_logger_init();
}

void loop() {
  PORTB |= 1;  // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  PORTB &= 0xFE;   // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second

  wire_logger_send("Hello from atmega");
}
