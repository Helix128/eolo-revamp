// Librerías para display y comunicación I2C
#include <U8g2lib.h>
#include <Wire.h>

// Módulos del proyecto
#include "Logos.h"
#include "Input.h" 
#include "Config.h" 
#include "Logger.h" 
#include "Motor.h" 
#include "Battery.h"
#include "Plantower.h"
#include "SceneManager.h"

// Escenas de la interfaz
#include "Scenes/IScene.h" // Escena "base"
#include "Scenes/LogoScene.h"

// Definición del display
// (DisplayModel definido en Config.h, se reemplaza por el modelo real de pantalla)
DisplayModel u8g2(U8G2_R0, SCL_PIN, SDA_PIN);

// Definición del input manager (maneja comunicación con driver del encoder/botón)
Input input;

// Batería del EOLO
Battery battery;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Espera a que se abra el monitor serial
  Serial.println("EOLO Boot");

  // Inicializa el input y el display
  input.begin();
  u8g2.begin();
  
  // Inicializa las escenas y muestra el splash con el logo
  SceneManager::addScene("splash", new LogoScene());
  SceneManager::addScene("home", new HomeScene());
  SceneManager::setScene("splash");
}

void loop() {
  input.poll();
  SceneManager::draw(u8g2, input);
  delay(33); // "30" FPS
}
