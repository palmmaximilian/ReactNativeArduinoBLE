#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <Preferences.h>

#include <FastLED.h>

#include "time.h"

#include "RTClib.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <global_variables.h>

// BLE SECTION
BLEServer *pServer = NULL;

BLECharacteristic *message_characteristic = NULL;
BLECharacteristic *box_characteristic = NULL;
String boxValue = "0";
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define MESSAGE_CHARACTERISTIC_UUID "6d68efe5-04b6-4a85-abc4-c2670b7bf7fd"
#define BOX_CHARACTERISTIC_UUID "f27b53ad-c63d-49a0-8c0f-9f297e6cc520"

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("Connected");
  };

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("Disconnected");
  }
};

class CharacteristicsCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    Serial.print("Value Written ");
    Serial.println(pCharacteristic->getValue().c_str());

    if (pCharacteristic == box_characteristic)
    {
      boxValue = pCharacteristic->getValue().c_str();
      box_characteristic->setValue(boxValue);
      box_characteristic->notify();
    }
  }
}

void
setup()
{
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("BLEExample");
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pService = pServer->createService(GENERAL_SERVICE_UUID);
  delay(100);

  // Create a BLE Characteristic
  nightmode_characteristic = pNightService->createCharacteristic(
      NIGHTMODE_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);

  nightmodebright_characteristic = pNightService->createCharacteristic(
      NIGHTMODEBRIGHT_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);

  // Start the BLE service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();

  nightmode_characteristic->setValue("Message one");
  nightmode_characteristic->setCallbacks(new CharacteristicsCallbacks());

  nightmodebright_characteristic->setValue("0");
  nightmodebright_characteristic->setCallbacks(new CharacteristicsCallbacks());

  Serial.println("Waiting for a client connection to notify...");
}

void loop()
{
  nightmode_characteristic->setValue("Message one");
  nightmode_characteristic->setCallbacks(new CharacteristicsCallbacks());

  delay(1000);

  nightmode_characteristic->setValue("Message Two");
  nightmode_characteristic->setCallbacks(new CharacteristicsCallbacks());

  delay(1000);
}