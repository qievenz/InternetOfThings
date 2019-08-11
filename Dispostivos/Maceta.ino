/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * Leer humedad en el suelo
 * si el valor leido es menor a X: 
 *  regar
 *  dormir 4 hs
 * si es mayor: 
 *  dormir 4 hs
 * si es igual:
 *  dormir 2 hs
 */

#include "/home/ivan/Documentos/GIT/InternetOfThings/Modules/WIFI.h"
#include "/home/ivan/Documentos/GIT/InternetOfThings/Modules/DHT12.h"
#include "/home/ivan/Documentos/GIT/InternetOfThings/Modules/Higrometro.h"

//ID unica del dispositivo
const char *id_dispositivo = "001";
Higrometro_class higrometro;
DHT12_class dht12;

void setup() 
{
    delay(200);
    Serial.begin(115200);
    wifi_setup(id_dispositivo);
    dht12.setup();
    //TODO:higrometro_setup();
    //TODO:motor_setup();
    
}
void loop() 
{
    wifi_loop();
    float humedad, temperatura;
    dht12.loop(&humedad, &temperatura);
    //higrometro.loop();
    //Peticiones entrantes
    //server.handleClient();
}