#include <Arduino.h>
#include "relay.h"
#include "LoraModule.h"

void setup() {
  initRelays();
  LoraSetup();
}

void loop() {
  String receivedData;
  if (receiveLoraData(receivedData)) {
    processReceivedData(receivedData);
  }
  delay(50);
}