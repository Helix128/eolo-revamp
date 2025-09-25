#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#define BATTERY_PIN 34

// Clase helper para leer el nivel de la batería
class Battery
{
public:
    static int getLevel()
    {
        // Simulación de lectura del nivel de batería
        return analogRead(34) / 4; // Convertir 0-1023 a 0-255
    }
};

#endif