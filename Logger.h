#ifndef LOGGER_H
#define LOGGER_H
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 5
#define SD_MOSI_PIN 23
#define SD_MISO_PIN 19
#define SD_SCK_PIN 18

const char* logFile = "log.csv";

class Logger {
public:
    static bool begin() {
        if (!SD.begin(SD_CS_PIN)) {
            Serial.println("Fallo al inicializar SD");
            return false;
        }
        Serial.println("SD inicializada");
        return true;
    }
};

#endif