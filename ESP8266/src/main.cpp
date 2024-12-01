#include <Arduino.h>
#include <../lib/WIFI.h>
#include <../lib/Pushover_notification.h>
#include <../../Modules/PIR.h>
#include <../../Modules/General.h>

PIR movementSensor(12);

void setup() {
  Serial.begin(115200);
  const char* id_dispositivo = "1";
  wifi_setup(id_dispositivo);
  
  String info = String("Device ID: ")
    + String(id_dispositivo) 
    + " - " + GetWiFiInfo();

  sendPushoverNotification(info);

  movementSensor.setup();
}

void loop() {
  wifi_loop();
  
  if (movementSensor.loop()) {
    log("¡Alerta! Se ha detectado movimiento.");
  }
}