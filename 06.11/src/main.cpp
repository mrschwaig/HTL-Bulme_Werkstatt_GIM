#include <Arduino.h>
#include "ampel.h"

#define GREEN_BULB 25
#define YELLOW_BULB 27
#define RED_BULB 26

void setup()
{
  pinMode(GREEN_BULB, OUTPUT);
  pinMode(YELLOW_BULB, OUTPUT);
  pinMode(RED_BULB, OUTPUT);
}

void loop()
{
  ampelphaseGruen(GREEN_BULB, RED_BULB, YELLOW_BULB);
  delay(2500);
  ampelphaseRot(GREEN_BULB, RED_BULB, YELLOW_BULB);
  delay(2500);
}