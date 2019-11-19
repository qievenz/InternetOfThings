/*
 * IRremoteESP8266: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 Sept, 2015
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus
 *   (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
//#include "/mnt/Media/Documentos/03.Software/01.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/General.h"
//#include "/mnt/Media/Documentos/03.Software/01.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/WIFI.h"
#include <stdlib.h> /* strtoul */
#include <IRsend.h>
IRsend irsend(4);
decode_results results;
using namespace std;
// Wifi
String SSID = "Internets";
String PASSWORD = "Movis956D3#FT";
ESP8266WebServer server(80);
String codigos = "";
//-----
//ID unica del dispositivo
const char *id_dispositivo = "002";
int contador = 30;
// an IR detector/demodulator is connected to GPIO pin 14 D5
uint16_t RECV_PIN = 14;
IRrecv irrecv(RECV_PIN);
// Wifi
void handleRecord()
{
  // /record/?modo=
  String modo = "";
  String speed = "";
  String flap = "";
  String temp = "";
  int cont = 0;
  if (server.hasArg("modo") && server.hasArg("speed") && server.hasArg("flap") && server.hasArg("temp"))
  {
    modo = server.arg("modo");
    speed = server.arg("speed");
    flap = server.arg("flap");
    temp = server.arg("temp");
    int iTemp = temp.toInt();
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", "Grabando");
    while (true)
    {
      if (irrecv.decode(&results))
      {
        //codigos += dump(&results, iTemp);
        dump(&results, iTemp);
        irrecv.resume(); // Receive the next value
        iTemp--;
      }
      if (iTemp > 30 || iTemp < 16)
      {
        Serial.println("Finaliza grabado");
        break;
      }
      delay(500);
    }
  }
  else
  {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", "Faltan parametros");
  }
}
void handleResult()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", codigos);
  codigos = "";
}
//-----
void setup()
{
  delay(200);
  Serial.begin(115200);
  // WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/record", handleRecord);
  server.on("/result", handleResult);

  server.begin();
  //-----
  irsend.begin();
  irrecv.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

String dump(decode_results *results, int temp)
{
  String respuesta = "";
  uint16_t count = results->rawlen;
  Serial.print(F("//HEX: "));
  respuesta += "//HEX: ";
  serialPrintUint64(results->value, 16);
  respuesta += (results->value, 16);
  Serial.println();
  Serial.print("uint16_t mseco_sauto_fauto_");
  respuesta += "\nuint16_t mseco_sauto_fauto_";
  Serial.print(temp);
  respuesta += temp;
  Serial.print("[");
  respuesta += "[";
  Serial.print(count, DEC);
  respuesta += (count, DEC);
  Serial.print("]={\n\t");
  respuesta += "]={\n\t";
  for (uint16_t i = 1; i < count; i++)
  {
    if (i % 100 == 0)
      yield();
    Serial.print(results->rawbuf[i] * RAWTICK, DEC);
    respuesta += results->rawbuf[i] * RAWTICK, DEC;
    Serial.print(F(", "));
    respuesta += ", ";
    if ((i % 10) == 0)
      Serial.print(F("\n\t"));
    respuesta += "\n\t";
  }
  Serial.println(F("1000};"));
  respuesta += "1000};\n";
  Serial.println();
  return respuesta;
  //}
}
void loop()
{ /*
  if (irrecv.decode(&results))
  {
    codigos = dump(&results, contador);
    irrecv.resume(); // Receive the next value
    contador--;
  }*/
  server.handleClient();
}
