#include <Arduino.h>

void morsenPunkt(int port) {
    digitalWrite(port, HIGH);
    delay(500);
    digitalWrite(port, LOW);
    delay(250);
}

void morsenStrich(int port) {
    digitalWrite(port, HIGH);
    delay(1500);
    digitalWrite(port, LOW);
    delay(250);
}

void morsenCharacterS(int port) {
    for (int i = 0; i < 3; i++) {
        morsenPunkt(port);
    }
}

void morsenCharacterO(int port) {
    for (int i = 0; i < 3; i++) {
        morsenStrich(port);
    }
}

