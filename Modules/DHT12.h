/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
#include <DHT12.h>
#define GPIO_PIN 4//D2 = GPIO 4
//Temperatura y humedad ambiente
DHT12 SENSOR(GPIO_PIN, true);

class DHT12_class
{
    public:
    int MUESTRAS = 100;
    
    void setup()
    {
        SENSOR.begin();
    }

    void loop(float *humedad, float *temperatura)
    {
        int muestras = 100;
        for (int i = 0; i < muestras; i++)
        {
            *humedad += SENSOR.readHumidity();
            *temperatura += SENSOR.readTemperature();
            delay(30);
        }
        *humedad = *humedad / muestras;
        *temperatura = *temperatura / muestras;
        Serial.print("Humedad ambiente: ");
        Serial.println(*humedad);
        Serial.print("Temperatura ambiente: ");
        Serial.println(*temperatura);
    }
};