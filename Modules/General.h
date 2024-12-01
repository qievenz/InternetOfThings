#pragma once
#define GPIO_A0 A0  //Analogico: voltimetro e higrometro
#define GPIO_16 D0  //
#define GPIO_05 D1  //Rele
#define GPIO_04 D2  //
#define GPIO_00 D3  //
#define GPIO_02 D4  //
#define GPIO_14 D5  //
#define GPIO_12 D6  //
#define GPIO_13 D7  //
#define GPIO_15 D8  //
#define GPIO_03 RX  //
#define GPIO_01 TX  //

//Devolver hora en milisegundos
int hora_mili(int hora)
{
    return hora * (3.6e+6);
}

String CharToString(char* a)
{
    String s = a;
    return s;
}

String getTimestamp() {
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    return String(buffer);
}

void log(String message) {
    Serial.println(getTimestamp() + " - " + message);
}