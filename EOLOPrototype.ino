// Librerías para display y comunicación I2C
#include <U8g2lib.h>
#include <Wire.h>

// Módulos del proyecto
#include "Logos.h"
#include "Input.h" 
#include "Config.h" 
#include "Logger.h" 
#include "Motor.h" 

// Escenas de la interfaz
#include "Scenes/IScene.h" // Escena "base"
#include "Scenes/HomeScene.h"

// Definición del display
// (DisplayModel definido en Config.h, se reemplaza por el modelo real de pantalla)
DisplayModel u8g2(U8G2_R0, SCL_PIN, SDA_PIN);

// Definición del input manager (maneja comunicación con driver del encoder/botón)
Input input;

// Escena actual
Scene* currentScene;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Espera a que se abra el monitor serial
  Serial.println("EOLO Boot");
  input.begin();
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.drawXBM(32, 0, 128, 64, cmas);
  u8g2.sendBuffer();
  delay(3000);
  input.resetCounter();
}

void loop() {
  input.poll();
  currentScene->draw(u8g2, input);
  delay(16);
}
