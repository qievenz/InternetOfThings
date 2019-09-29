/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 */

class Rele_class
{
    public:
    int speed;
    void setup()
    {
        pinMode(GPIO_05, OUTPUT);
        digitalWrite(GPIO_05, LOW);
        delay(3);
    }
    void encender()
    {
        Serial.println("Encendiendo rele");
        digitalWrite(GPIO_05, HIGH);
    }
    void apagar()
    {

        Serial.println("Apagando rele");
        digitalWrite(GPIO_05, LOW);
    }
    void loop()
    {
        encender();
        delay(5000);
        apagar();
        delay(5000);
    }
};