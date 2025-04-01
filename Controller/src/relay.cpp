#include "relay.h"

int elayPins[NUM_RELAYS] = {PA0, PA1, PA2, PA3, PA11, PA12, PA15, PB3, PB4, PB5, PB9};

void SetupRelay() {
    for (int i = 0; i < NUM_RELAYS; i++) {
        pinMode(elayPins[i], OUTPUT);
        digitalWrite(elayPins[i], LOW);
    }
}

void ControlRelay(JsonDocument doc) {
    int pin = doc["Pin"];
    int value = doc["Value"];
    
    if (pin >= 1 && pin <= NUM_RELAYS) {
        int relayPin = elayPins[pin-1];
        digitalWrite(relayPin, value ? HIGH : LOW);
    }
}