#include "relay.h"

int relayPins[11] = {PA0, PA1, PA2, PA3, PA11, PA12, PA15, PB3, PB4, PB5, PB9};

void initRelays() {
    for (int i = 0; i < 11; i++) {
        pinMode(relayPins[i], OUTPUT);
        digitalWrite(relayPins[i], LOW);
    }
}

void controlRelay(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}

void relayControl(JsonDocument doc) {
    int pin = doc["Pin"];
    int value = doc["Value"];

    bool validPin = false;
    for (int i = 1; i <= 11; i++) {
        if (i == pin) {
            int relayPin = relayPins[i-1];
            controlRelay(relayPin, value == 1);
            validPin = true;
            break;
        }
    }
}