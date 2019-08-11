/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
#include "/home/ivan/Documentos/GIT/InternetOfThings/Modules/General.h"
#define GPIO_PIN A0
//Humedad en el suelo
class Higrometro_class
{
    public:
    int MUESTRAS = 100;
    
    float leer()
    {
        float resultado = 0;
        for (int i = 0; i < MUESTRAS; i++)
        {
            resultado += analogRead(GPIO_PIN);
            delay(30);
        }
        resultado = resultado / MUESTRAS;    
        resultado = map(resultado,1024,270,0,100);
        Serial.print("Humedad en suelo: ");
        Serial.println(resultado);
        return resultado;
    }
    void loop()
    {
        float h_suelo = leer();
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
        
        Serial.println(leer());
    }
};

