#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <Wire.h>
#include "Config.h"

class Input {
public:
  // variables públicas de input
  volatile byte encoderDirection = 0;
  volatile byte encoderCounter = 0;
  volatile bool buttonPressed = false;

  Input() {
  }

  void begin() {
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(100000);
    Serial.println("INPUT INIT");
  }
  void poll() {
    readEncoderData();
  }

  void resetCounter() {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_COUNTER);
    if (Wire.endTransmission() == 0) {
      encoderCounter = 0;
    }
  }

  void resetButton() {
    Wire.beginTransmission(ATTINY_ADDRESS);
    Wire.write(CMD_RESET_BUTTON);
    if (Wire.endTransmission() == 0) {
      buttonPressed = false;
    }
  }

private:
  void readEncoderData() {
    if (Wire.requestFrom(ATTINY_ADDRESS, 3) == 3) {
      byte prevDirection = encoderDirection;
      byte prevCounter = encoderCounter;
      bool prevButton = buttonPressed;
      
      encoderDirection = Wire.read();
      encoderCounter = Wire.read();
      buttonPressed = (Wire.read() == 1);
      
      if (encoderDirection != prevDirection) {
      Serial.print("Direction changed to: ");
      Serial.println(encoderDirection);
      }
      if (encoderCounter != prevCounter) {
      Serial.print("Counter changed to: ");
      Serial.println(encoderCounter);
      }
      if (buttonPressed != prevButton) {
      Serial.print("Button pressed: ");
      Serial.println(buttonPressed);
      }
    }
  }
};

#endif  // INPUT_H
