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
struct CR
{
    char *nombre;
    uint16_t *raw;
};

CR ac_apagar;
ac_apagar.nombre = "ac_apagar";
ac_apagar.raw = {
    3322, 1652, 410, 444, 386, 420, 410, 420, 410, 420,
    410, 420, 410, 420, 410, 1260, 412, 420, 410, 444,
    386, 420, 410, 420, 410, 420, 410, 420, 410, 420,
    410, 420, 410, 418, 412, 420, 410, 420, 410, 1260,
    410, 418, 412, 1258, 412, 420, 410, 420, 412, 418,
    412, 420, 410, 420, 410, 418, 412, 418, 410, 420,
    412, 418, 412, 402, 428, 1258, 412, 1258, 412, 1258,
    412, 418, 412, 418, 412, 418, 412, 418, 412, 1258,
    412, 418, 412, 418, 412, 418, 412, 418, 412, 418,
    412, 402, 430, 418, 412, 1258, 414, 1256, 414, 418,
    412, 418, 412, 1258, 412, 1258, 412, 418, 412, 1258,
    414, 418, 412, 418, 412, 418, 412, 418, 412, 418,
    412, 418, 412, 418, 412, 418, 412, 1256, 414, 418,
    414, 1258, 412, 1258, 412, 418, 414, 416, 414, 418,
    412, 418, 412, 418, 414, 418, 412, 418, 412, 418,
    412, 418, 412, 418, 412, 418, 412, 418, 414, 418,
    412, 416, 414, 416, 414, 416, 414, 418, 412, 1258,
    414, 416, 414, 1258, 414, 1256, 414, 416, 414, 416,
    414, 418, 414, 416, 414, 418, 414, 416, 414, 418,
    414, 416, 412, 418, 414, 416, 414, 416, 414, 416,
    414, 416, 414, 416, 414, 418, 414, 416, 414, 416,
    414, 416, 414, 1258, 414, 416, 414, 416, 414, 418,
    414, 416, 414, 416, 414, 418, 414, 416, 414, 416,
    414, 416, 414, 416, 414, 416, 414, 416, 414, 416,
    414, 416, 414, 416, 414, 416, 414, 416, 414, 416,
    414, 416, 414, 416, 414, 418, 414, 416, 414, 1256,
    414, 416, 414, 416, 414, 416, 414, 416, 414, 416,
    414, 1256, 414, 416, 414, 1000};

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
            //TODO:buscar(dispositivo, boton)
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