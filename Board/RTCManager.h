#ifndef RTC_H
#define RTC_H

#include <Arduino.h>
#include <RTClib.h>

// Clase para manejar el RTC
class RTCManager{
public:
    void begin() {
        // Inicialización del RTC (simulada)
    }
    String getTimeString() {
        // Simulación de obtención de la hora actual
        return "12:00";
    }
};
#endif