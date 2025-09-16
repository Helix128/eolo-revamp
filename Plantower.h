#ifndef PLANTOWER_H
#define PLANTOWER_H

#define PT_TX 16
#define PT_RX 17
#define PT_PWR 4

class Plantower {
public:
    void begin() {
        Serial2.begin(9600, SERIAL_8N1, PT_RX, PT_TX);
        pinMode(PT_PWR, OUTPUT);
        digitalWrite(PT_PWR, HIGH); // Enciende el sensor
    }
};

#endif