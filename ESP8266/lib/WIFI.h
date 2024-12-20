/**************************************
 * Author      : Velazquez Ivan
 * Date        : Julio 2019
 * conectar a la red principal en EEPROM
 * si no hay eeprom ingresar la hardcodeada
 * si no esta diconible levantar un AP
 * ingresar la red y clave a la cual conectarse
 */
#include "EEPROM_Handler.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <../../Modules/General.h>

EEPROM_Handler eeprom;
ESP8266WebServer server(80);
WiFiClient client;
//Funciones
void conectar_AP(String essid, String passwd)
{
    Serial.println("Iniciando WiFi...");
    //Configurar
    WiFi.mode(WIFI_AP_STA);
    //Conectar al AP ingresado
    Serial.print("ESSID: ");
    Serial.println(essid);
    Serial.print("PASSWORD: ");
    Serial.println(passwd);
    WiFi.begin(essid.c_str(), passwd.c_str());
    delay(5000);
    //IPAddress ip = WiFi.localIP();
    Serial.print("Obteniendo IP...");
    //if (ip.toString() == "(IP unset)")
    while (WiFi.localIP().toString() == "(IP unset)")
    {
        Serial.print("...");
        delay(5000);
    }
    Serial.println("");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP().toString());
}

void page_softAP()
{
    //TODO: Agregar el alta del dispositivo en la BD. Ingresar nombre del dispositivo, descripcion
    int Tnetwork = 0;
    String html = "";
    String html_networks = "";
    Tnetwork = WiFi.scanNetworks(); //Scan for total networks available
    html_networks = "<ul>";
    for (int i = 0; i < Tnetwork; ++i)
    {
        // Print SSID and RSSI for each network found
        html_networks += "<li>";
        html_networks += i + 1;
        html_networks += ": ";
        html_networks += WiFi.SSID(i);
        html_networks += " (";
        html_networks += WiFi.RSSI(i);
        html_networks += ")";
        html_networks += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
        html_networks += "</li>";
    }
    html_networks += "</ul>";
    html = "\n\r\n<!DOCTYPE HTML>\r\n<html><h1> Ingresar red</h1> ";
    html += "<p>";
    html += html_networks;
    html += "<form method='get' action='wificonnect'>";
    //ESSID
    html += "<label>SSID: </label><input name='ssid' length=32>";
    //ESSID pass
    html += "<label>Paswoord: </label><input name='pass' length=64>";
    //IP de RaspberryPi
    html += "<label>IP RaspberryPi: </label><input name='iprpi' length=15>";
    html += "<input type='submit'></form>";
    html += "</html>\r\n\r\n";
    //Serial.println(html);
    server.send(200, "text/html", html);
}
void request_softAP()
{
    String ssid = "";
    String pass = "";
    String iprpi = "";
    String html = "";
    //Obtener essid y pass del request recibido
    if (server.hasArg("ssid") && server.hasArg("pass") && server.hasArg("iprpi"))
    {
        ssid = server.arg("ssid");
        pass = server.arg("pass");
        iprpi = server.arg("iprpi");

        if (ssid.length() > 1 && pass.length() > 1 && iprpi.length() > 1)
        {
            Serial.print("ESSID ingresada: ");
            Serial.println(ssid);
            Serial.print("Pass ingresada: ");
            Serial.println(pass);
            Serial.print("IP de RaspberryPi ingresada: ");
            Serial.println(iprpi);
            //Guardar los datos en memoria
            strncpy(eeprom.ESSID, ssid.c_str(), sizeof(eeprom.ESSID));
            strncpy(eeprom.EPASS, pass.c_str(), sizeof(eeprom.EPASS));
            strncpy(eeprom.IP_rpi, iprpi.c_str(), sizeof(eeprom.IP_rpi));
            //Armar html de respuesta
            html = "\r\n\r\n<!DOCTYPE HTML>\r\n<html><h1>Node MCU</h1> ";
            html += "<p>Presione el boton FLASH para guardar los datos y luego RESET para conectarse a la red ingresada.</html>\r\n\r\n";
        }
    }
    Serial.println(html);
    server.send(200, "text/html", html);
}
void levantar_AP()
{
    Serial.println("Levantar AP");
    const char *essid_ap = "NodeMCU";
    //Configurar AP
    WiFi.mode(WIFI_AP_STA);
    IPAddress local_IP(192, 168, 4, 1);
    IPAddress gateway(192, 168, 4, 254);
    IPAddress subnet(255, 255, 255, 0);
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "SoftAPConfig Ready" : "SoftAPConfig Failed!");
    //Levantar AP
    Serial.println(WiFi.softAP(essid_ap) ? "SoftAP Ready" : "SoftAP Failed!");
    Serial.print("ESSID: ");
    Serial.println(essid_ap);
    Serial.print("Obteniendo IP...");
    while (WiFi.softAPIP().toString() == "(IP unset)")
    {
        Serial.print("...");
        delay(5000);
    }
    Serial.print("\nIP: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("In Ap Mode");
    //Setear servicios web
    server.on("/", page_softAP);
    server.on("/wificonnect", request_softAP);
    server.begin();
    delay(300);
}

void wifi_setup(const char *id_dispositivo)
{
    pinMode(0, INPUT); //Boton FLASH
    eeprom.inicializar();
    eeprom.leer();
    if (CharToString(eeprom.ESSID).length() > 0 && CharToString(eeprom.EPASS).length() > 0)
    {
        Serial.println("Conecctar ap");
        //Conectarse al AP ingresado
        conectar_AP(CharToString(eeprom.ESSID), CharToString(eeprom.EPASS));
    }
    else
    {
        Serial.println("Formatear");
        //Levantar AP para ingresar los datos y grabarlos en memoria
        eeprom.formatear();
        /*for (int i = 0; i < sizeof(eeprom.ID_mcu); i++)
        {
            eeprom.ID_mcu[i] = id_dispositivo[i];
        } */
        strncpy(eeprom.ID_mcu, id_dispositivo, sizeof(eeprom.ID_mcu));
        levantar_AP();
    }
    //Fecha y hora
    configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    Serial.println("Waiting for Internet time");
    while (!time(nullptr))
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("wifi_setup OK");
}
void wifi_loop()
{
    if (digitalRead(0) == LOW && eeprom.validar())
    {
        eeprom.grabar();
        Serial.println("Datos grabados con exito!");
    }
    server.handleClient();
}

String GetWiFiInfo()
{
    String info = "";
    
    info +=  "ESSID: " + WiFi.SSID();
    info += " - ";
    info +=  "IP: " + WiFi.localIP().toString();
    
    return info;
}