#include <Arduino.h>

#define GREEN_BULB 25

void setup() {
  pinMode(GREEN_BULB, OUTPUT);
}

void loop() {
  digitalWrite(GREEN_BULB, HIGH);
  delay(50);
  digitalWrite(GREEN_BULB, LOW);
}