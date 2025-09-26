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
}; 

// Clase para manejar el datalogger en tarjeta SD.
// API mínimal: begin() inicializa el subsistema SD y capture() escribe una línea CSV.
class Logger
{
public:
    // Estado global del SD (útil para mostrar en UI)
    static SDStatus status;

    // Inicializa la tarjeta SD. Devuelve true si OK.
    // Esta es una función de instancia (no static) para evitar problemas
    // con el generador de prototipos de Arduino y para permitir futuras
    // extensiones de estado por-instancia si es necesario.
    bool begin();

    // Escribe una muestra en la SD (implementación en Logger.cpp)
    void capture(AppContext &context);
};

inline SDStatus Logger::status = SD_OK;
#endif