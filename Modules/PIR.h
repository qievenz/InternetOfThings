/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
//#define GPIO_PIN 12//GPIO12 = D6

class PIR_class
{
    public:
    void setup()
    {
        pinMode(GPIO_12, INPUT);
    }
    bool loop()
    {
        bool resultado;
        if (digitalRead(GPIO_12) == HIGH)
        {
            Serial.println("Movimiento detectado!");
            resultado = true;
        }
        else
        {
            Serial.println("No se detecto una goma");
            resultado = false;
        }
        delay(1000);
        return resultado;
    }
};