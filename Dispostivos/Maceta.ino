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
//ID unica del dispositivo
const char *id_dispositivo = "001";
//Temperatura y humedad ambiente
//DHT12 dht12(0, true);
//Humedad en el suelo
int raw = A0;
float leer_suelo()
{
    float resultado = 0;
    for (int i = 0; i < 100; i++)
    {
        resultado += analogRead(raw);
        delay(3);
    }
    delay(30);
    resultado = resultado / 100;    
    resultado = map(resultado,1024,270,0,100);
    Serial.print("Humedad en suelo: ");
    Serial.println(resultado);
    return resultado;
}
int hora_mili(int hora)
{
    return hora * (3.6e+6);
}
void setup() 
{
    delay(200);
    Serial.begin(115200);
    wifi_setup(id_dispositivo);
    //TODO:DHT_setup();
    //dht12.begin();
    //TODO:higrometro_setup();
    //TODO:motor_setup();
    
}
void loop() 
{
    wifi_loop();
    //TODO:DHT_loop();
    //float humedad = dht12.readHumidity();
    //float temperatura = dht12.readTemperature();
    //TODO:suelo_loop();
    /*float h_suelo = leer_suelo();
    if (h_suelo < 30)
    {
        //TODO:regar(float temp);
        ESP.deepSleep(hora_mili(6));
    }
    if (h_suelo > 30 && h_suelo < 40)
    {
        ESP.deepSleep(hora_mili(2));
    }
    if (h_suelo > 40)
    {
        ESP.deepSleep(hora_mili(4));
    }
     */
    //Serial.println(leer_suelo());
    //Peticiones entrantes
    server.handleClient();
}