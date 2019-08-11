/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
//#include "/home/ivan/Documentos/GIT/InternetOfThings/Modules/General.h"
#define GPIO_PIN A0
//Humedad en el suelo
class Higrometro_class
{
    public:
    int MUESTRAS = 100;
    
    void loop(float *humedad)
    {
        for (int i = 0; i < MUESTRAS; i++)
        {
            *humedad += analogRead(GPIO_PIN);
            delay(30);
        }
        *humedad = *humedad / MUESTRAS;    
        *humedad = map(*humedad,1024,270,0,100);
        Serial.print("Humedad en suelo: ");
        Serial.println(*humedad);
    }
};

