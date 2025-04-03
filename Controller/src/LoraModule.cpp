#include "LoraModule.h"
#include "relay.h"
#include <ArduinoJson.h>

String gatewayId;
uint32_t waitDuration = 30 * 1000000;
bool LoraSender = false;

void LoraSetup() {
    pinMode(SPI1_NSS, OUTPUT);
    pinMode(SPI1_RESET, OUTPUT);
    digitalWrite(SPI1_RESET, HIGH);
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6)) {
        delay(5000);
    }
    LoRa.receive();
}

bool receiveLoraData(String &receivedData) {
    if (!LoraSender) {
        int packetSize = LoRa.parsePacket();
        if (packetSize) {
            receivedData = "";
            while (LoRa.available()) {
                receivedData += (char)LoRa.read();
            }
            return true;
        }
    }
    return false;
}

void processReceivedData(String &data) {
    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, data);
    
    if (!error) {
        int pin = doc["Pin"];
        int value = doc["Value"];
        
        // Đảm bảo pin nằm trong khoảng hợp lệ
        if (pin >= 1 && pin <= NUM_RELAYS) {
            ControlRelay(doc);
            
            // Gửi phản hồi dạng JSON
            DynamicJsonDocument respDoc(64);
            respDoc["Pin"] = pin;
            respDoc["Status"] = value;
            
            String response;
            serializeJson(respDoc, response);
            
            LoRa.beginPacket();
            LoRa.print(response);
            LoRa.endPacket();
        }
    }
}

void resetLoRaModule() {
    digitalWrite(SPI1_RESET, LOW);
    delay(10);
    digitalWrite(SPI1_RESET, HIGH);
    delay(10);
}

void beginSend() {
    LoraSender = true;
    resetLoRaModule();
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6)) {}
    LoRa.idle();
}

void endSend() {
    resetLoRaModule();
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6)) {}
    LoRa.receive();
    LoraSender = false;
}