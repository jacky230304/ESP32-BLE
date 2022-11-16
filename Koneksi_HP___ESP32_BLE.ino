// import library yang diperlukan
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// define UUID dari UUIB Generator (UUID berfunsgi sebagai identifikator dari service)
#define SERVICE_UUID        "670de345-edf7-46e7-bc84-f90765f7ac4a"
#define CHARACTERISTIC_UUID "9bbb69d3-a9b2-4ffa-b2c2-5aaf97c1dfb5"

void setup() {
  Serial.begin(115200);
  Serial.println("Memulai BLE");
  // mengatur esp32 menjadi sebuah ble server
  BLEDevice::init("ESP32");
  BLEServer *pServer = BLEDevice::createServer();
  // membuat sebuah service dengan UUID yang di define sebelumnya  
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // mengatur karakteristik dari service yang dibuat dalam kasus ini Read & Write 
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  //mengatur value/nilai dari karakteristik service yang dibuat (kasus ini masih string)
  pCharacteristic->setValue("Ganti Value String Ini Dengan Fungsi Membaca Berat Ayam");
  pService->start();
  //memulai service dan advertise esp32 agar bisa discan hp 
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // funsgi untuk masalah koneksi di Iphone
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Berat Ayam Terbaca, Sekarang Anda Bisa Membacanya Di HP Anda");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}
