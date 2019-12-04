/**************************************
 * Author      : Velazquez Ivan
 * Date        : Diciembre 2019
 * Recibir la tecla por request
 * Enviar la tecla raw al pin ir de salida
 */

#include "/mnt/Media/Documentos/03.Software/01.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/General.h"
#include "/mnt/Media/Documentos/03.Software/01.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/WIFI.h"
#include "/mnt/Media/Documentos/03.Software/01.Proyectos/01. Domotica/02. NodeMCU/InternetOfThings/Modules/IR_Codes.h"
//ID unica del dispositivo
const char *id_dispositivo = "003";

void request_control()
{
    String dispositivo = "";
    String boton = "";
    //Obtener dispositivo y boton del request recibido
    if (server.hasArg("dispositivo") && server.hasArg("boton"))
    {
        dispositivo = server.arg("dispositivo");
        boton = server.arg("boton");
        if (dispositivo.length() > 1 && boton.length() > 1)
        {
            //TODO:Buscar señal. buscar(dispositivo, boton)
        }
    }
}
void setup()
{
    delay(200);
    Serial.begin(115200);
    wifi_setup(id_dispositivo);
    //TODO:Pin led IR
    server.on("/wificonnect", request_softAP);
    //TODO:request /control?dispositivo=xxxxx&boton=xxxxxxx
    server.on("/control", request_control);
    server.begin();
    delay(300);
}

void loop()
{
}