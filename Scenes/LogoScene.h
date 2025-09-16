#ifndef LOGO_SCENE_H
#define LOGO_SCENE_H

#include "../Config.h"
#include <U8g2lib.h>
#include "../Input.h"
#include "IScene.h"
#include "../Logos.h"
#include "../SceneManager.h"

// Escena del logo de C+
class LogoScene : public IScene {
public:
  bool isDrawn = false;
  unsigned long startTime;
  unsigned long currentTime;
  unsigned long elapsedTime;
  void draw(DisplayModel &u8g2, Input &input) override {
    
    // Solo dibuja una vez
    if (!isDrawn) {
      startTime = millis();

      // Dibujar el logo por tres segundos, luego pasa a la siguiente escena
      u8g2.clearBuffer();
      u8g2.drawXBM(32, 0, 128, 64, cmas);
      u8g2.sendBuffer();
    }

    // Calcular tiempo
    currentTime = millis();
    elapsedTime = currentTime - startTime;

    // Cambio de escena
    if(elapsedTime>3000){
        SceneManager::setScene("home");
    }
  }
};
#endif