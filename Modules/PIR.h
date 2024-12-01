class PIR
{
    private:
        uint8_t pin;
        unsigned long lastCheck;
        unsigned long interval;

    public:
        PIR(uint8_t gpioPin, unsigned long checkInterval = 1000)
        : pin(gpioPin), lastCheck(0), interval(checkInterval) {}

    void setup()
    {
        pinMode(pin, INPUT);
    }
    bool loop()
    {
        unsigned long currentMillis = millis();
        
        if (currentMillis - lastCheck >= interval) {
            lastCheck = currentMillis;

            if (digitalRead(pin) == HIGH) {
                return true;
            } else {
                return false;
            }
        }
        
        return false;
    }
};