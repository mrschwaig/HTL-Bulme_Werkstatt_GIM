#include <Arduino.h>

void switchDimmingOn(int port)
{
  for (int i = 1000; i > 0; i--)
  {
    digitalWrite(port, HIGH);
    delayMicroseconds(i);
    digitalWrite(port, LOW);
    delayMicroseconds(1000 - i);
  }
}

void switchDimmingOff(int port)
{
  for (int i = 1000; i > 0; i--)
  {
    digitalWrite(port, LOW);
    delayMicroseconds(i);
    digitalWrite(port, HIGH);
    delayMicroseconds(1000 - i);
  }
}