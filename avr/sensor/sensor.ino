void setup() {
  DDRB |= 1;
}

void loop() {
  PORTB |= 1;  // turn the LED on (HIGH is the voltage level)
  delay(getcount(2));              // wait for a second
  PORTB &= 0xFE;   // turn the LED off by making the voltage LOW
  delay(getcount(3));              // wait for a second
}
