/**************************************
 * Author      : Velazquez Ivan
 * Date        : Agosto 2019
 * 
 * Funciones generales entre los dispositivos
 * 
 */

//Devolver humedad en la tierra
float leer_suelo(int gpio_pin)
{
    float resultado = 0;
    int muestras = 100;
    for (int i = 0; i < muestras; i++)
    {
        resultado += analogRead(gpio_pin);
        delay(3);
    }
    delay(30);
    resultado = resultado / muestras;    
    resultado = map(resultado,1024,270,0,100);
    Serial.print("Humedad en suelo: ");
    Serial.println(resultado);
    return resultado;
}

//Devolver hora en milisegundos
int hora_mili(int hora)
{
    return hora * (3.6e+6);
}


