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

#include "/media/NAS4/Documentos/03.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/General.h"
#include "/media/NAS4/Documentos/03.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/WIFI.h"
#include "/media/NAS4/Documentos/03.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/DHT12.h"
#include "/media/NAS4/Documentos/03.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/Higrometro.h"
#include "/media/NAS4/Documentos/03.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/Rele.h"
#include "/media/NAS4/Documentos/03.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/PIR.h"
#include "/media/NAS4/Documentos/03.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/Voltimetro.h"
//ID unica del dispositivo
const char *id_dispositivo = "001";
//Higrometro_class higrometro;
//DHT12_class dht12;
//Rele_class rele;
//PIR_class pir;
Voltimetro_class voltimetro;

void setup() 
{
    delay(200);
    Serial.begin(115200);
    wifi_setup(id_dispositivo);
    //dht12.setup();
    //rele.setup();
    //pir.setup();

}
void loop() 
{
    wifi_loop();
    float humedad_ambiente, temperatura_ambiente, humedad_suelo, voltaje;
    //dht12.loop(&humedad_ambiente, &temperatura_ambiente);
    //higrometro.loop(&humedad_suelo);
    //rele.loop();
    //voltimetro.loop(&voltaje);
    //Peticiones entrantes
    //server.handleClient();
    digitalWrite(GPIO_04, HIGH);
    voltimetro.loop(&voltaje);
}