#include <Arduino.h>

#define FIXED_STATE_TIME 2500
#define SWITCH_STATE_TIME 1500
#define BLINK_TIME 500


void trafficlightsTask(int portGreen, int portRed, int portOrange) {
  enum Trafficlights {
    RedPhase,
    RedOrangePhase,
    GreenPhase,
    GreenBlinkPhase,
    OrgangeAfterGreenPhase,
    UndefinedState
  };

  uint8_t Trafficlights = RedPhase;

  switch (Trafficlights) {
    case RedPhase:
      digitalWrite(portRed, HIGH);
      digitalWrite(portGreen, LOW);
      digitalWrite(portOrange, LOW);
      delay(FIXED_STATE_TIME);
      Trafficlights = RedOrangePhase;
      break;
    case RedOrangePhase:
      digitalWrite(portRed, HIGH);
      digitalWrite(portOrange, HIGH);
      digitalWrite(portGreen, LOW);
      delay(SWITCH_STATE_TIME);
      Trafficlights = GreenPhase;
      break;
    case GreenPhase:
      digitalWrite(portRed, LOW);
      digitalWrite(portOrange, LOW);
      digitalWrite(portGreen, HIGH);
      delay(FIXED_STATE_TIME);
      Trafficlights = GreenBlinkPhase;
      break;
    case GreenBlinkPhase:
      digitalWrite(portRed, LOW);
      digitalWrite(portOrange, LOW);
      for(int i = 0; i < 4; i++) {
        digitalWrite(portGreen, LOW);
        delay(BLINK_TIME);
        digitalWrite(portGreen, HIGH);
        delay(BLINK_TIME);
      }
      Trafficlights = OrgangeAfterGreenPhase;
      break;
    case OrgangeAfterGreenPhase:
      digitalWrite(portRed, LOW);
      digitalWrite(portGreen, LOW);
      digitalWrite(portOrange, HIGH);
      delay(SWITCH_STATE_TIME);
      digitalWrite(portOrange, LOW);
      Trafficlights = RedPhase;
      break;
    case UndefinedState:
      while (true) {
        digitalWrite(portOrange, LOW);
        delay(BLINK_TIME);
        digitalWrite(portOrange, HIGH);
        delay(BLINK_TIME);
      }
  }
}