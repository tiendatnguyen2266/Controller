#ifndef LORAMODULE_H
#define LORAMODULE_H

#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#define SPI1_NSS  PA4
#define SPI1_SCK  PA5
#define SPI1_RESET PB0

extern String gatewayId;
extern uint32_t waitDuration;

void resetLoRaModule();
void LoraSetup(void);
bool receiveLoraData(String &receivedData);
void processReceivedData(String &data);
void beginSend(void);
void endSend(void);

#endif