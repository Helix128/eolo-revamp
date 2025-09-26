#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <Wire.h>
#include "Config.h"

// Clase para manejar el input del encoder con botón
class Input
{
public:
  // Constructor
  Input() {}

  void begin()
  {
    Wire.begin(SDA_PIN, SCL_PIN); // Inicializa Wire para comunicación I2C
    Wire.setClock(100000);        // 100kHz
    Serial.println("Encoder inicializado");
    delay(100);
    resetButton();
    resetCounter();
    readEncoderData(); // Leer estado inicial

    // Inicializar estados previos para detección de cambios
    prevEncoderCounterRaw = rawCounter;
    prevButtonRaw = rawButton;
    lastButtonChangeMs = millis();
  }

  // Poll: actualizar lecturas desde el driver
  void poll()
  {
    readEncoderData();
  }

  // Reiniciar valor del encoder via driver
  bool resetCounter()
  {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_COUNTER);
    bool ok = (Wire.endTransmission() == 0);
    if (ok)
    {
      rawCounter = 0;
      prevEncoderCounterRaw = 0;
    }
    return ok;
  }

  // Reiniciar botón del encoder via driver
  bool resetButton()
  {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_BUTTON);
    bool ok = (Wire.endTransmission() == 0);
    if (ok)
    {
      rawButton = false;
      prevButtonRaw = false;
    }
    return ok;
  }

  // --- API limpia solicitada ---
  // Devuelve la dirección actual del encoder: -1 = izquierda, 0 = sin movimiento, 1 = derecha
  // Esta función detecta el cambio de rawCounter y consume el flanco (actualiza prev).
  int getEncoderDirection()
  {
    // Calcular el delta entre el contador actual y el previo manejando el wrap 0..255.
    // Esto evita interpretar 255->0 como giro en sentido contrario.
    if (rawCounter != prevEncoderCounterRaw)
    {
      int delta = (int)rawCounter - (int)prevEncoderCounterRaw;
      // Ajustar por wrap-around
      if (delta > 127) delta -= 256;
      else if (delta < -127) delta += 256;

      prevEncoderCounterRaw = rawCounter;
      if (delta > 0) return 1;
      if (delta < 0) return -1;
    }
    return 0;
  }

  // Alternativa compatibilidad: devuelve true si hubo movimiento a la derecha/izquierda (no recomendado)
  bool encoderMovedRight() { return getEncoderDirection() == 1; }
  bool encoderMovedLeft() { return getEncoderDirection() == -1; }

  // Devuelve el delta signed entre la lectura actual y la previa, manejando wrap (valor puede ser >1 si se giró rápido)
  // Actualiza prevEncoderCounterRaw para consumir el flanco.
  int getEncoderDelta()
  {
    if (rawCounter == prevEncoderCounterRaw) return 0;
    int delta = (int)rawCounter - (int)prevEncoderCounterRaw;
    if (delta > 127) delta -= 256;
    else if (delta < -127) delta += 256;
    prevEncoderCounterRaw = rawCounter;
    return delta;
  }

  // Devuelve el valor raw actual del encoder (0..255) para usos que requieran un valor absoluto
  uint8_t getEncoderValue() const { return rawCounter; }

  // Devuelve el estado actual del botón (true = pulsado)
  bool getButtonState() const { return rawButton; }

  // Devuelve true solo al detectar la transición no->sí del botón (con debounce simple)
  bool buttonJustPressed()
  {
    const unsigned long DEBOUNCE_MS = 50;
    if (rawButton != prevButtonRaw)
    {
      unsigned long now = millis();
      if (now - lastButtonChangeMs >= DEBOUNCE_MS)
      {
        bool justPressed = rawButton && !prevButtonRaw;
        prevButtonRaw = rawButton;
        lastButtonChangeMs = now;
        return justPressed;
      }
    }
    else
    {
      lastButtonChangeMs = millis();
    }
    return false;
  }

private:
  // Lecturas crudas mantenidas internamente
  volatile byte rawCounter = 0;   // Contador raw (0..255)
  volatile bool rawButton = false; // Estado del botón (raw)

  // Función interna para leer datos del encoder desde el ATTiny
  void readEncoderData()
  {
    if (Wire.requestFrom(ATTINY_ADDRESS, 3) == 3)
    {
      byte prevCounter = rawCounter;
      bool prevButton = rawButton;

      // Nota: el ATTiny devuelve (direccion, contador, boton). Ignoramos la dirección
      // porque ahora calculamos el sentido mediante delta wrap-aware.
      (void)Wire.read(); // descartamos dirección
      rawCounter = Wire.read();
      rawButton = (Wire.read() == 1);

      if (rawCounter != prevCounter)
      {
        Serial.print("Encoder: Contador cambio a ");
        Serial.println(rawCounter);
      }
      if (rawButton != prevButton)
      {
        Serial.print("Encoder: Boton pulsado? ");
        Serial.println(rawButton);
      }
    }
  }

  // Variables para detección de flancos / debounce
  byte prevEncoderCounterRaw = 0;
  bool prevButtonRaw = false;
  unsigned long lastButtonChangeMs = 0;
};

#endif // INPUT_H
