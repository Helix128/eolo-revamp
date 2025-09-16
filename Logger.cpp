#include "Logger.h"
#include "AppContext.h" 

// Implementación de los métodos del Logger
// Esto es necesario porque si no se forma una dependencia circular 
// entre AppContext.h y Logger.h
// (y va más acorde a las buenas prácticas de oop con c++ supongo)

void Logger::capture(AppContext& context) {
    File dataFile = SD.open(logFile, FILE_APPEND);
    if (dataFile) {
        // Timestamp
        dataFile.print(context.rtc.getTimeString().c_str()); // reemplazar con tiempo real de rtc
        dataFile.print(",");
        
        // Flujo observado 
        dataFile.print(context.flowSensor.flowRate); // Reemplazar con lectura real
        dataFile.print(",");

        // Flujo objetivo/seteado
        dataFile.print(context.flujoObjetivo);
        dataFile.print(",");

        // Temperatura ºC 
        dataFile.print(context.bme.temperature); // Reemplazar con lectura real
        dataFile.print(",");
        
        // Humedad %RH
        dataFile.print(context.bme.humidity); // Reemplazar con lectura real
        dataFile.print(",");

        // Presión hPa 
        dataFile.print(context.bme.pressure); // Reemplazar con lectura real
        dataFile.print(",");

        // PM1.0 (DE ESTAR DESACTIVADO, DEBE SER -1)
        dataFile.print(context.plantower.pm1); // Reemplazar con lectura real
        dataFile.print(","); 

        // PM2.5 (DE ESTAR DESACTIVADO, DEBE SER -1)
        dataFile.print(context.plantower.pm25); // Reemplazar con lectura real
        dataFile.print(",");

        // PM10 (DE ESTAR DESACTIVADO, DEBE SER -1)
        dataFile.print(context.plantower.pm10); // Reemplazar con lectura real
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