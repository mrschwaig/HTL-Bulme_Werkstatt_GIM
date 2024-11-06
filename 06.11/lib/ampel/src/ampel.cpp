#include <Arduino.h>


void blinken(int port) {
  for(int i = 0; i < 4; i++) {
    digitalWrite(port, LOW);
    delay(500);
    digitalWrite(port, HIGH);
    delay(500);
  }
}

void rotZuGruen(int portGruen, int portRot, int portGelb) {
    digitalWrite(portGelb, HIGH);
    delay(1000);
    digitalWrite(portGelb, LOW);
    digitalWrite(portRot, LOW);
    digitalWrite(portGruen, HIGH);
}

void gruenZuRot(int portGruen, int portGelb) {
    blinken(portGruen);
    digitalWrite(portGruen, LOW);
    digitalWrite(portGelb, HIGH);
    delay(1000);
    digitalWrite(portGelb, LOW);
}

void ampelphaseRot(int portGruen, int portRot, int portGelb) {
    digitalWrite(portRot, HIGH);
    digitalWrite(portGruen, LOW);
    digitalWrite(portGelb, LOW);
    delay(2500);
    rotZuGruen(portGruen, portRot,portGelb);
}

void ampelphaseGruen(int portGruen, int portRot, int portGelb) {
    digitalWrite(portRot, LOW);
    digitalWrite(portGruen, HIGH);
    digitalWrite(portGelb, LOW);
    delay(2500);
    gruenZuRot(portGruen, portGelb);
    digitalWrite(portRot, HIGH);
}