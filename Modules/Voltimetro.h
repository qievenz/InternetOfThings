/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
//#define GPIO_PIN A0
//#define OFFSET 2424
#define OFFSET 240
//Voltaje
class Voltimetro_class
{
    public:
    int MUESTRAS = 100;
    
    void loop(float *voltaje)
    {
        for (int i = 0; i < MUESTRAS; i++)
        {
            *voltaje += analogRead(GPIO_A0);
            delay(30);
        }
        *voltaje = *voltaje / MUESTRAS;
        //Serial.print("Raw: ");
        //Serial.println(*voltaje);
        *voltaje = map(*voltaje,1.5,1023,0,2500) - OFFSET; //0 - 25000 mV
        //Serial.print("Raw map: ");
        //Serial.println(*voltaje);
        *voltaje /= 100;
        Serial.print("Voltaje: ");
        Serial.println(*voltaje);
        delay(500);
    }
};