/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */
#define GPIO_PIN 13 //GPIO13 = D7

class Rele_class
{
    public:
    void setup()
    {
        pinMode(GPIO_PIN, OUTPUT);
        digitalWrite(GPIO_PIN, LOW);
        delay(3);
    }
    void encender()
    {
        digitalWrite(GPIO_PIN, HIGH);
    }
    void apagar()
    {
        digitalWrite(GPIO_PIN, LOW);
    }
    void loop()
    {
        digitalWrite(GPIO_PIN, HIGH);
        delay(1000);
        digitalWrite(GPIO_PIN, LOW);
    }
};