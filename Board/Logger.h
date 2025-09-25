#ifndef LOGGER_H
#define LOGGER_H

// Definiciones para el datalogger

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 5
#define SD_MOSI_PIN 23
#define SD_MISO_PIN 19
#define SD_SCK_PIN 18

#define logFile "log.csv"

struct AppContext; // Declaración adelantada para evitar dependencias circulares

enum SDStatus{
    OK,
    WRITING,
    ERROR
}

// Clase para manejar el datalogger en tarjeta SD
class Logger {
public:
    SDStatus status = OK;
    static bool begin() {
        if (!SD.begin(SD_CS_PIN)) {
            Serial.println("Fallo al inicializar SD");
            status = ERROR;
            return false;
        }
        Serial.println("SD inicializada");
        return true;
    }
    
    // Solo declaración aquí
    void capture(AppContext& context);
};

#endif