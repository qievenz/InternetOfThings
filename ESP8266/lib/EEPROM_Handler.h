#include <Arduino.h>
#include <EEPROM.h>
class EEPROM_Handler
{
public:
    const int MAX_SIZE = 512;
    char ESSID[32];
    char EPASS[64];
    char IP_rpi[15];
    char ID_mcu[3];

    void inicializar()
    {
        EEPROM.begin(MAX_SIZE);
    }

    void formatear()
    {
        for (int i = 0; i < sizeof(ESSID); i++)
        {
            ESSID[i] = 255;
        }
        for (int i = 0; i < sizeof(EPASS); i++)
        {
            EPASS[i] = 255;
        }
        for (int i = 0; i < sizeof(IP_rpi); i++)
        {
            IP_rpi[i] = 255;
        }
        for (int i = 0; i < sizeof(ID_mcu); i++)
        {
            ID_mcu[i] = 255;
        }
        for (int i = 0; i < MAX_SIZE; i++)
        {
            EEPROM.write(i, 255);
        }
        delay(10);
    }
    void leer()
    {
        //cout << "Buscando datos en memoria...";
        unsigned int longitud = 0;
        unsigned int posicion = 0;
        unsigned int i = 0;
        longitud += sizeof(ESSID);
        for (posicion; posicion < longitud; posicion++)
        {
            if (EEPROM.read(posicion) != 255)
            {
                ESSID[i] += char(EEPROM.read(posicion));
                i++;
            }
        }
        i = 0;
        longitud += sizeof(EPASS);
        for (posicion; posicion < longitud; posicion++)
        {
            if (EEPROM.read(posicion) != 255)
            {
                EPASS[i] += char(EEPROM.read(posicion));
                i++;
            }
        }
        i = 0;
        longitud += sizeof(IP_rpi);
        for (posicion; posicion < longitud; posicion++)
        {
            if (EEPROM.read(posicion) != 255)
            {
                IP_rpi[i] += char(EEPROM.read(posicion));
                i++;
            }
        }
        i = 0;
        longitud += sizeof(ID_mcu);
        for (posicion; posicion < longitud; posicion++)
        {
            if (EEPROM.read(posicion) != 255)
            {
                ID_mcu[i] += char(EEPROM.read(posicion));
                i++;
            }
        }
    }
    void grabar()
    {
        unsigned int longitud = 0;
        unsigned int posicion = 0;
        unsigned int i = 0;
        longitud += sizeof(ESSID);
        for (posicion; posicion < longitud; posicion++)
        {
            EEPROM.write(posicion, ESSID[i]);
            i++;
        }
        i = 0;
        longitud += sizeof(EPASS);
        for (posicion; posicion < longitud; posicion++)
        {
            EEPROM.write(posicion, EPASS[i]);
            i++;
        }
        i = 0;
        longitud += sizeof(IP_rpi);
        for (posicion; posicion < longitud; posicion++)
        {
            EEPROM.write(posicion, IP_rpi[i]);
            i++;
        }
        i = 0;
        longitud += sizeof(ID_mcu);
        for (posicion; posicion < longitud; posicion++)
        {
            EEPROM.write(posicion, ID_mcu[i]);
            i++;
        }
        EEPROM.commit();
    }
    bool validar()
    {
        bool resultado = false;
        String str_ESSID = ESSID;
        String str_EPASS = EPASS;
        String str_IP_rpi = IP_rpi;
        String str_ID_mcu = ID_mcu;
        if (str_ESSID.length() > 0 &&
            str_EPASS.length() > 0 &&
            str_IP_rpi.length() > 0 &&
            str_ID_mcu.length() > 0)
        {
            resultado = true;
        }
        else
        {
            resultado = false;
        }
        return resultado;
    }
};