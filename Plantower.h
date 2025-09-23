#ifndef PLANTOWER_H
#define PLANTOWER_H

#define PT_TX 16
#define PT_RX 17
#define PT_PWR 4

// https://wiki.dfrobot.com/Air_Quality_Monitor__PM_2.5_Temperature_and_Humidity_Sensor__SKU__SEN0233
class Plantower {
private:
    unsigned char bufferRTT[32] = {}; // Buffer para datos recibidos
    
    bool validateChecksum() {
        unsigned int CR1 = (bufferRTT[30] << 8) + bufferRTT[31];
        unsigned int CR2 = 0;
        for (int i = 0; i < 30; i++)
            CR2 += bufferRTT[i];
        return (CR1 == CR2);
    }

public:
    float pm1 = 0.0;
    float pm25 = 0.0;
    float pm10 = 0.0;

    void begin() {
        Serial2.begin(9600, SERIAL_8N1, PT_RX, PT_TX);
        pinMode(PT_PWR, OUTPUT);
        digitalWrite(PT_PWR, HIGH); // Enciende el sensor
    }

    void setPower(bool active) {
        digitalWrite(PT_PWR, active ? HIGH : LOW); // Controla la alimentación 
    }

    void readData() {
        if (!Serial2.available()) return;
        
        while (Serial2.available() > 0) {
            // Lee 32 bytes de datos
            for (int i = 0; i < 32; i++) {
                if (Serial2.available()) {
                    bufferRTT[i] = Serial2.read();
                    delay(2);
                }
            }
            
            Serial2.flush();
            
            // Valida que el mensaje esté correcto
            if (validateChecksum()) {
                // PM 1.0
                unsigned int PMSa1 = bufferRTT[10];
                unsigned int PMSb1 = bufferRTT[11];
                unsigned int PMS1 = (PMSa1 << 8) + PMSb1;
                pm1 = (float)PMS1;
                
                // PM 2.5
                unsigned int PMSa2_5 = bufferRTT[12];
                unsigned int PMSb2_5 = bufferRTT[13];
                unsigned int PMS2_5 = (PMSa2_5 << 8) + PMSb2_5;
                pm25 = (float)PMS2_5;
                
                // PM 10
                unsigned int PMSa10 = bufferRTT[14];
                unsigned int PMSb10 = bufferRTT[15];
                unsigned int PMS10 = (PMSa10 << 8) + PMSb10;
                pm10 = (float)PMS10;
            } else {
                // Checksum fallido, asignar -1 
                // Especificar comportamiento 
                // Si se piden estos valores y el valor es -1
                // significa que el sensor está activado pero 
                // funciona mal
                pm1 = -1;
                pm25 = -1;
                pm10 = -1;
            }
        }
    }
};

#endif