/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
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
        Serial.print("Raw Voltaje: ");
        Serial.println(*voltaje);
        *voltaje = map(*voltaje,1.5,1023,0,2500) - OFFSET; //0 - 25000 mV
        *voltaje /= 100;
        Serial.print("Voltaje: ");
        Serial.println(*voltaje);
    }
};