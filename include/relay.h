#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include <ArduinoJson.h>

extern int relayPins[11];

void initRelays(void);
void controlRelay(int pin, bool state);
void relayControl(JsonDocument doc);

#endif // RELAY_H