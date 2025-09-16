#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

// Clase para manejar el sensor de flujo de aire
// TODO
class FlowSensor {
public:
    float flowRate = 0.0; // Litros por minuto

    void begin() {
        // Inicialización del sensor (simulada)
    }

    void readData() {
        // Simulación de lectura de datos
        flowRate = 5.0; // Placeholder
    }
};

#endif