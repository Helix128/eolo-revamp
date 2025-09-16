#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <Wire.h>
#include "Config.h"

class Input {
public:

  // Variables públicas de input
  volatile byte encoderDirection = 0; // Dirección (Horario/Antihorario)
  volatile byte encoderCounter = 0; // Contador de pasos del encoder
  volatile bool buttonPressed = false; // Estado del botón del encoder

  void begin() {
    Wire.begin(SDA_PIN, SCL_PIN); // Inicializa Wire para comunicación I2C
    Wire.setClock(100000); // 100kHz
    Serial.println("Encoder inicializado");
    delay(100);
    resetButton();
    resetCounter();
    readEncoderData(); // Leer estado inicial
  }

  // Función helper para actualizar datos del encoder
  void poll() {
    readEncoderData();
  }

  // Reiniciar valor del encoder via driver
  void resetCounter() {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_COUNTER);
    if (Wire.endTransmission() == 0) {
      encoderCounter = 0;
    }
  }

  // Reiniciar botón del encoder via driver
  void resetButton() {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_BUTTON);
    if (Wire.endTransmission() == 0) {
      buttonPressed = false;
    }
  }

  
private:
  // Función interna para leer datos del encoder
  void readEncoderData() {
    if (Wire.requestFrom(ATTINY_ADDRESS, 3) == 3) {
      byte prevDirection = encoderDirection;
      byte prevCounter = encoderCounter;
      bool prevButton = buttonPressed;
      
      encoderDirection = Wire.read();
      encoderCounter = Wire.read();
      buttonPressed = (Wire.read() == 1);
      
      if (encoderDirection != prevDirection) {
      Serial.print("Encoder: Direccion cambio a ");
      Serial.println(encoderDirection);
      }
      if (encoderCounter != prevCounter) {
      Serial.print("Encoder: Contador cambio a ");
      Serial.println(encoderCounter);
      }
      if (buttonPressed != prevButton) {
      Serial.print("Encoder: Boton pulsado? ");
      Serial.println(buttonPressed);
      }
    }
  }
};

#endif  // INPUT_H
