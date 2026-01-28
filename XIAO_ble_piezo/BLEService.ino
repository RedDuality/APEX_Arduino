/* Secondary File: BLEService.ino
   Logic: Handles all Bluetooth stack initialization and callbacks
*/

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;
bool _deviceConnected = false;

// Callbacks to handle connection events
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) { 
      Serial.println("Bluetooth Connected");
      _deviceConnected = true; 
    };
    void onDisconnect(BLEServer* pServer) { 
      _deviceConnected = false;
      BLEDevice::startAdvertising(); 
    }
};

// Initialize BLE
void setupBLE(const char* deviceName) {
  BLEDevice::init(deviceName);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  
  BLEDevice::getAdvertising()->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();
}

// Check connection status
bool isBLEConnected() {
  return _deviceConnected;
}

// Format and send the data
void sendPiezoData(int sensorNum, int value) {
  String message = "S" + String(sensorNum) + ":" + String(value);
  pCharacteristic->setValue(message.c_str());
  pCharacteristic->notify();
}