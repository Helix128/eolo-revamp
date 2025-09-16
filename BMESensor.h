#ifndef BMESENSOR_H
#define BMESENSOR_H


// Clase para manejar el sensor BME280 (temperatura, humedad, presión)
class BMESensor {
public:
    float temperature = 0.0;
    float humidity = 0.0;
    float pressure = 0.0;
    void begin() {
        // Inicialización del sensor (simulada)
    }

    void readData() {
        // Simulación de lectura de datos
        temperature = 25.0; // Placeholder
        humidity = 50.0;    // Placeholder
        pressure = 1013.25; // Placeholder
    }
};

#endif