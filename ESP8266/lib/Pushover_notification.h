#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* pushoverApiUrl = "https://api.pushover.net:443/1/messages.json";
const char* userKey = "u94yahbfhoadc9uayst96duv2y4ibm";
const char* apiToken = "amb5bgatxuy7uamwm5xchfe79w7i7g";


void sendPushoverNotification(String message) {
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, pushoverApiUrl);
  http.addHeader("Content-Type", "application/json");
  
  String jsonData = "{";
  jsonData += "\"user\":\"" + String(userKey) + "\",";
  jsonData += "\"token\":\"" + String(apiToken) + "\",";
  jsonData += "\"message\":\"" + message + "\"";
  jsonData += "}";

  int httpCode = http.POST(jsonData);
  String payload = http.getString();
  
  Serial.println(payload);
  Serial.println(httpCode);

  if (httpCode > 0) {
    Serial.println("Notificación enviada correctamente.");
  } else {
    Serial.println("Error al enviar notificación");
  }
  
  http.end();
}