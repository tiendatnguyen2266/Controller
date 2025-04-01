#include <Arduino.h>
#include "relay.h"
#include "LoraModule.h"

void setup() {
  setup();
  LoraSetup();
}

void loop() {
  String receivedData;
  if (receiveLoraData(receivedData)) {
    processReceivedData(receivedData);
  }
  delay(50);
}