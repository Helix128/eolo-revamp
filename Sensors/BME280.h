#ifndef BMESENSOR_H
#define BMESENSOR_H

#include <Adafruit_BME280.h>
// Clase para manejar el sensor BME280 (temperatura, humedad, presión)
class BME280
{
private:
    Adafruit_BME280 bme;

public:
    float temperature = 0.0;
    float humidity = 0.0;
    float pressure = 0.0;

    void begin()
    {
        bme.begin();
    }

    void readData()
    {
        temperature = bme.readTemperature();
        humidity = bme.readHumidity();
        pressure = bme.readPressure() / 100.0F; // Convertir Pa a hPa
    }
};

#endif