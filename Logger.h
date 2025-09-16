#ifndef LOGGER_H
#define LOGGER_H
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "AppContext.h"

#define SD_CS_PIN 5
#define SD_MOSI_PIN 23
#define SD_MISO_PIN 19
#define SD_SCK_PIN 18

const char* logFile = "log.csv";

// Declaración adelantada
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
    
    // Registra un snapshot del estado actual en el archivo de log
    void capture(AppContext& context) {
        File dataFile = SD.open(logFile, FILE_APPEND);
        if (dataFile) {
            // Timestamp
            dataFile.print(millis());
            dataFile.print(",");
            
            // Flujo observado
            dataFile.print(context.flujoObjetivo); // Placeholder, reemplazar con valor real
            dataFile.print(",");

            // Flujo objetivo/seteado
            dataFile.print(context.flujoObjetivo);
            dataFile.print(",");

            // Temperatura ºC (placeholder)
            dataFile.print(25.0); // Reemplazar con lectura real
            dataFile.print(",");
            
            // Humedad %RH (placeholder)
            dataFile.print(50.0); // Reemplazar con lectura real
            dataFile.print(",");

            // Presión hPa (placeholder)
            dataFile.print(1013.25); // Reemplazar con lectura real
            dataFile.print(",");

            // PM1.0 (placeholder) (DE ESTAR DESACTIVADO, USAR -1)
            dataFile.print(10); // Reemplazar con lectura real
            dataFile.print(","); 

            // PM2.5 (placeholder) (DE ESTAR DESACTIVADO, USAR -1)
            dataFile.print(20); // Reemplazar con lectura real
            dataFile.print(",");

            // PM10 (placeholder) (DE ESTAR DESACTIVADO, USAR -1)
            dataFile.print(30); // Reemplazar con lectura real
            dataFile.print(",");

            // Batería %
            dataFile.print(context.getBatteryPercentage());
            dataFile.print("\n");
            
            dataFile.close();
            Serial.println("Datos guardados en SD");
        } else {
            Serial.println("Error guardando datos en SD");
        }
    }
};

#endif