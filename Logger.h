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

// Forward declaration
struct AppContext;

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
    
    // Log a data snapshot using AppContext
    void logSnapshot(AppContext& context) {
        File dataFile = SD.open(logFile, FILE_APPEND);
        if (dataFile) {
            // Log timestamp
            dataFile.print(millis());
            dataFile.print(",");
            
            // Log target flow
            dataFile.print(context.flujoObjetivo);
            dataFile.print(",");
            
            // Log battery level
            dataFile.print(context.getBatteryPercentage());
            dataFile.print(",");
            
            // Log capture status
            dataFile.print(context.capturaActiva ? 1 : 0);
            dataFile.print(",");
            
            // Log elapsed time
            dataFile.println(context.tiempoTranscurrido);
            
            dataFile.close();
            Serial.println("Data logged to SD");
        } else {
            Serial.println("Error opening log file");
        }
    }
};

#endif