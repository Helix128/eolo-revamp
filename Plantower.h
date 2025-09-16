#ifndef PLANTOWER_H
#define PLANTOWER_H

#define PT_TX 16
#define PT_RX 17
#define PT_PWR 4

// TODO cuando tenga el plantower funcionando
// implementar lectura de datos y parseo
class Plantower {
public:
    float pm1 = 0.0;
    float pm25 = 0.0;
    float pm10 = 0.0;

    void begin() {
        Serial2.begin(9600, SERIAL_8N1, PT_RX, PT_TX);
        pinMode(PT_PWR, OUTPUT);
        digitalWrite(PT_PWR, HIGH); // Enciende el sensor
    }

    void readData() {
        // TODO implementar lectura y parseo de datos
        // Por ahora simula datos
        pm1 = 10.0;
        pm25 = 20.0;
        pm10 = 30.0;
    }
};

#endif