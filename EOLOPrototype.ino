// Librerías para display y comunicación I2C
#include <U8g2lib.h>
#include <Wire.h>

// Módulos principales 
#include "AppContext.h"
#include "SceneManager.h"
#include "SceneRegistry.h"

// Instancias globales
DisplayModel u8g2(U8G2_R0, SCL_PIN, SDA_PIN);
AppContext context(u8g2); // Aquí se procesa toda la lógica

void setup() {
  // Inicialización del contexto de la app
  context.begin();

  // Registrar todas las escenas (SceneRegistry)
  registerAllScenes();
  
  // Carga la escena inicial (splash)
  SceneManager::setScene("splash", context);
}

void loop() {
  // Actualizar el contexto de la app y la escena actual
  context.update();
  SceneManager::update(context);
  delay(33); // ~30 FPS
}
