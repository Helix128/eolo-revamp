#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <Wire.h>
#include "Config.h"

// Clase para manejar el input del encoder con botón
class Input
{
public:
  // Variables públicas de input
  volatile byte encoderDirection = 0;  // Dirección (Horario/Antihorario)
  volatile byte encoderCounter = 0;    // Contador de pasos del encoder
  volatile bool buttonPressed = false; // Estado del botón del encoder

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
    prevEncoderCounterRaw = encoderCounter;
    prevButtonRaw = buttonPressed;
    lastButtonChangeMs = millis();
  }

  // Función helper para actualizar datos del encoder
  void poll()
  {
    readEncoderData();
  }

  // Reiniciar valor del encoder via driver
  void resetCounter()
  {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_COUNTER);
    if (Wire.endTransmission() == 0)
    {
      encoderCounter = 0;
      prevEncoderCounterRaw = 0;
    }
  }

  // Reiniciar botón del encoder via driver
  void resetButton()
  {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_BUTTON);
    if (Wire.endTransmission() == 0)
    {
      buttonPressed = false;
      prevButtonRaw = false;
    }
  }

  // --- Nuevos helpers públicos ---
  // Devuelven true una vez por cada movimiento detectado en la dirección indicada.
  bool encoderMovedRight()
  {
    // Si hubo cambio y la dirección indica movimiento horario (asumimos 1 = horario)
    if (encoderCounter != prevEncoderCounterRaw && encoderDirection == 1)
    {
      prevEncoderCounterRaw = encoderCounter;
      return true;
    }
    return false;
  }

  bool encoderMovedLeft()
  {
    if (encoderCounter != prevEncoderCounterRaw && encoderDirection != 1)
    {
      prevEncoderCounterRaw = encoderCounter;
      return true;
    }
    return false;
  }

  // Devuelve true solo al detectar la transición no->sí del botón (con debounce simple)
  bool buttonJustPressed()
  {
    const unsigned long DEBOUNCE_MS = 50;
    if (buttonPressed != prevButtonRaw)
    {
      // valor cambió; aplicar debounce temporal
      unsigned long now = millis();
      if (now - lastButtonChangeMs >= DEBOUNCE_MS)
      {
        // Confirmar cambio estable
        bool justPressed = buttonPressed && !prevButtonRaw;
        prevButtonRaw = buttonPressed;
        lastButtonChangeMs = now;
        return justPressed;
      }
    }
    else
    {
      // No hay cambio: actualizar timestamp para evitar bloqueos en flancos siguientes
      lastButtonChangeMs = millis();
    }
    return false;
  }

private:
  // Función interna para leer datos del encoder
  void readEncoderData()
  {
    if (Wire.requestFrom(ATTINY_ADDRESS, 3) == 3)
    {
      byte prevDirection = encoderDirection;
      byte prevCounter = encoderCounter;
      bool prevButton = buttonPressed;

      encoderDirection = Wire.read();
      encoderCounter = Wire.read();
      buttonPressed = (Wire.read() == 1);

      if (encoderDirection != prevDirection)
      {
        Serial.print("Encoder: Direccion cambio a ");
        Serial.println(encoderDirection);
      }
      if (encoderCounter != prevCounter)
      {
        Serial.print("Encoder: Contador cambio a ");
        Serial.println(encoderCounter);
      }
      if (buttonPressed != prevButton)
      {
        Serial.print("Encoder: Boton pulsado? ");
        Serial.println(buttonPressed);
      }
    }
  }

  // Variables para detección de flancos / debounce
  byte prevEncoderCounterRaw = 0;
  bool prevButtonRaw = false;
  unsigned long lastButtonChangeMs = 0;
};

#endif // INPUT_H
