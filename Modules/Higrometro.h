/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
//#include "/home/ivan/Documentos/GIT/InternetOfThings/Modules/General.h"
//Humedad en el suelo
class Higrometro_class
{
    public:
    int MUESTRAS = 100;
    
    void loop(float *humedad)
    {
        for (int i = 0; i < MUESTRAS; i++)
        {
            *humedad += analogRead(GPIO_A0);
            delay(30);
        }
        *humedad = *humedad / MUESTRAS;
        Serial.print("Raw Humedad: ");
        Serial.println(*humedad);  
        *humedad = map(*humedad,1024,270,0,100);
        Serial.print("Humedad en suelo: ");
        Serial.println(*humedad);
    }
};

