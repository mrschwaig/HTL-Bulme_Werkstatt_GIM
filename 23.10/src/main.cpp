#include <Arduino.h>

#define GREEN_BULB 25

void setup() {
  pinMode(GREEN_BULB, OUTPUT);
}

void loop() {
  for (int i = 1000; i > 0; i--) {
    digitalWrite(GREEN_BULB, HIGH);
    delayMicroseconds(i);
    digitalWrite(GREEN_BULB, LOW);
    delayMicroseconds(1000 - i);
  }

  delay(1000);

  for (int i = 1000; i > 0; i--) {
          digitalWrite(GREEN_BULB, LOW);
          delayMicroseconds(i);
          digitalWrite(GREEN_BULB, HIGH);
          delayMicroseconds(1000 - i);
    }
}