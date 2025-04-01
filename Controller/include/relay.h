#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include <ArduinoJson.h>

const int NUM_RELAYS = 11;
extern int elayPins[NUM_RELAYS];

void SetupRelay(void);
void ControlRelay(JsonDocument doc);

#endif