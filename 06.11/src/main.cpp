#include <Arduino.h>

#define GREEN_BULB 25
#define YELLOW_BULB 27
#define RED_BULB 26

#define FIXED_STATE_TIME 2500
#define SWITCH_STATE_TIME 1500
#define BLINK_TIME 500

void setup()
{
  pinMode(GREEN_BULB, OUTPUT);
  pinMode(YELLOW_BULB, OUTPUT);
  pinMode(RED_BULB, OUTPUT);
}

enum Trafficlights {
    RedPhase,
    RedOrangePhase,
    GreenPhase,
    GreenBlinkPhase,
    OrgangeAfterGreenPhase,
    UndefinedState
  };

  uint8_t Trafficlights = RedPhase;

void loop() {

  switch (Trafficlights) {
    case RedPhase:
      digitalWrite(RED_BULB, HIGH);
      digitalWrite(GREEN_BULB, LOW);
      digitalWrite(YELLOW_BULB, LOW);
      delay(FIXED_STATE_TIME);
      Trafficlights = RedOrangePhase;
      break;
    case RedOrangePhase:
      digitalWrite(RED_BULB, HIGH);
      digitalWrite(YELLOW_BULB, HIGH);
      digitalWrite(GREEN_BULB, LOW);
      delay(SWITCH_STATE_TIME);
      Trafficlights = GreenPhase;
      break;
    case GreenPhase:
      digitalWrite(RED_BULB, LOW);
      digitalWrite(YELLOW_BULB, LOW);
      digitalWrite(GREEN_BULB, HIGH);
      delay(FIXED_STATE_TIME);
      Trafficlights = GreenBlinkPhase;
      break;
    case GreenBlinkPhase:
      digitalWrite(RED_BULB, LOW);
      digitalWrite(YELLOW_BULB, LOW);
      for(int i = 0; i < 4; i++) {
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
      delay(SWITCH_STATE_TIME);
      digitalWrite(YELLOW_BULB, LOW);
      Trafficlights = RedPhase;
      break;
    case UndefinedState:
      while (true) {
        digitalWrite(YELLOW_BULB, LOW);
        delay(BLINK_TIME);
        digitalWrite(YELLOW_BULB, HIGH);
        delay(BLINK_TIME);
      }
  }
}