#include <Arduino.h>

#define GREEN_BULB 25
#define YELLOW_BULB 27
#define RED_BULB 26
#define TASTER 32
#define POTI 33

#define FIXED_STATE_TIME 2500
#define SWITCH_STATE_TIME 1500
#define BLINK_TIME 500

unsigned long previousMillis = 0;
unsigned long currentMillis = millis();

bool oldState = 0;
bool actualButtonState = 0;

void setup()
{
  pinMode(GREEN_BULB, OUTPUT);
  pinMode(YELLOW_BULB, OUTPUT);
  pinMode(RED_BULB, OUTPUT);
  pinMode(TASTER, INPUT);
  pinMode(POTI, INPUT);

  Serial.begin(9600);
}

enum Trafficlights
{
  RedPhase,
  RedOrangePhase,
  GreenPhase,
  GreenBlinkPhase,
  OrgangeAfterGreenPhase,
  UndefinedState,
  pedestrianGreen,
  pedestrianRed,
  pedestrianStart
};

uint8_t Trafficlights = RedPhase;

void loop()
{
  Serial.print(digitalRead(POTI));
  Serial.printf(" ");
  Serial.println(digitalRead(TASTER));

  actualButtonState = digitalRead(POTI);

  if (actualButtonState != oldState)
  {
    oldState = actualButtonState;
    if (!actualButtonState)
    {
      Trafficlights = RedPhase;
    }
    else if (actualButtonState)
    {
      Trafficlights = pedestrianStart;
    }
  }

  switch (Trafficlights)
  {
  case RedPhase:
    digitalWrite(RED_BULB, HIGH);
    digitalWrite(GREEN_BULB, LOW);
    digitalWrite(YELLOW_BULB, LOW);
    currentMillis = millis();
    if (currentMillis - previousMillis >= FIXED_STATE_TIME)
    {
      previousMillis = currentMillis;
    }
    Trafficlights = RedOrangePhase;
    break;
  case RedOrangePhase:
    digitalWrite(RED_BULB, HIGH);
    digitalWrite(YELLOW_BULB, HIGH);
    digitalWrite(GREEN_BULB, LOW);
    currentMillis = millis();
    if (currentMillis - previousMillis >= SWITCH_STATE_TIME)
    {
      previousMillis = currentMillis;
    }
    Trafficlights = GreenPhase;
    break;
  case GreenPhase:
    digitalWrite(RED_BULB, LOW);
    digitalWrite(YELLOW_BULB, LOW);
    digitalWrite(GREEN_BULB, HIGH);
    currentMillis = millis();
    if (currentMillis - previousMillis >= FIXED_STATE_TIME)
    {
      previousMillis = currentMillis;
    }
    Trafficlights = GreenBlinkPhase;
    break;
  case GreenBlinkPhase:
    digitalWrite(RED_BULB, LOW);
    digitalWrite(YELLOW_BULB, LOW);
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(GREEN_BULB, LOW);
      delay(BLINK_TIME);
      digitalWrite(GREEN_BULB, HIGH);
      delay(BLINK_TIME);
    }
    Trafficlights = OrgangeAfterGreenPhase;
    break;
  case OrgangeAfterGreenPhase:
    digitalWrite(RED_BULB, LOW);
    digitalWrite(GREEN_BULB, LOW);
    digitalWrite(YELLOW_BULB, HIGH);
    currentMillis = millis();
    if (currentMillis - previousMillis >= SWITCH_STATE_TIME)
    {
      previousMillis = currentMillis;
    }
    digitalWrite(YELLOW_BULB, LOW);
    Trafficlights = RedPhase;
    break;
  case UndefinedState:
    while (true)
    {
      digitalWrite(YELLOW_BULB, LOW);
      currentMillis = millis();
      if (currentMillis - previousMillis >= BLINK_TIME)
      {
        previousMillis = currentMillis;
      }
      digitalWrite(YELLOW_BULB, HIGH);
      currentMillis = millis();
      if (currentMillis - previousMillis >= BLINK_TIME)
      {
        previousMillis = currentMillis;
      }
    }
  case pedestrianRed:
    digitalWrite(RED_BULB, LOW);
    digitalWrite(GREEN_BULB, HIGH);
    digitalWrite(YELLOW_BULB, LOW);
    currentMillis = millis();
    if (currentMillis - previousMillis >= FIXED_STATE_TIME)
    {
      previousMillis = currentMillis;
    }
    Trafficlights = pedestrianGreen;
  case pedestrianGreen:
    digitalWrite(RED_BULB, HIGH);
    digitalWrite(GREEN_BULB, LOW);
    digitalWrite(YELLOW_BULB, LOW);
    if (digitalRead(TASTER) == 1)
    {
      Trafficlights = pedestrianRed;
    }
  case pedestrianStart:
    for (int i = 0; i < 2; i++)
    {
      digitalWrite(YELLOW_BULB, LOW);
      delay(BLINK_TIME);
      digitalWrite(YELLOW_BULB, HIGH);
      delay(BLINK_TIME);
    }
    Trafficlights = pedestrianGreen;
  }
}