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

enum SDStatus
{
    SD_OK,
    SD_WRITING,
    SD_ERROR
}; // <-- added missing semicolon

// Clase para manejar el datalogger en tarjeta SD
class Logger
{
public:
    static SDStatus status;
    static bool begin()
    {
        if (!SD.begin(SD_CS_PIN))
        {
            Serial.println("Fallo al inicializar SD");
            Logger::status = SD_ERROR;
            return false;
        }
        Serial.println("SD inicializada");
        Logger::status = SD_OK;
        return true;
    }

    // Solo declaración aquí
    void capture(AppContext &context);
};

inline SDStatus Logger::status = SD_OK;

#endif