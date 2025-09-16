// Librerías para display y comunicación I2C
#include <U8g2lib.h>
#include <Wire.h>

// Core application context and scene management
#include "AppContext.h"
#include "SceneManager.h"
#include "SceneRegistry.h"

// --- Global Instances ---
DisplayModel u8g2(U8G2_R0, SCL_PIN, SDA_PIN);
AppContext context(u8g2); // The single brain of the app!

void setup() {
  // Initialize all hardware and services through AppContext
  context.begin();

  // Register all available scenes
  registerAllScenes();
  
  // Set initial scene
  SceneManager::setScene("splash", context);
}

void loop() {
  // Update application state
  context.update();
  
  // Update current scene
  SceneManager::update(context);
  
  delay(33); // ~30 FPS
}
