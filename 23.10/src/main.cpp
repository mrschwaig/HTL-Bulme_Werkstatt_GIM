#include <Arduino.h>
#include <morsen.h>

#define GREEN_BULB 25

int state = 0;

void setup()
{
  pinMode(GREEN_BULB, OUTPUT);
}

void loop()
{
  morsenCharacterS(GREEN_BULB);
  morsenCharacterO(GREEN_BULB);
  morsenCharacterS(GREEN_BULB);

  delay(5000);
}