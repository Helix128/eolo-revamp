#ifndef LOGO_SCENE_H
#define LOGO_SCENE_H

#include <U8g2lib.h>
#include "../Input.h"
#include "IScene.h"
#include "../Logos.h"

// Escena del logo de C+
class LogoScene : public IScene
{
    public: 
    void draw(U8g2 &u8g2, Input &input) override
    {
        static unsigned long startTime = millis();
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - startTime;

        // Dibujar el logo en función del tiempo transcurrido
        u8g2.clearBuffer();
        u8g2.drawXBM(32, 0, 128, 64, cmas);
        u8g2.sendBuffer();
    }
};
#endif  