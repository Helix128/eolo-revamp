#ifndef LOGO_SCENE_H
#define LOGO_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/Logos.h"
#include "../Drawing/SceneManager.h"

// Escena de logo/splash al iniciar la app
class LogoScene : public IScene
{
private:
    unsigned long startTime;
    static const unsigned long SPLASH_DURATION = 3000; // 3 segundos

public:
    void enter(AppContext &context) override
    {
        startTime = millis();

        // Dibujar el logo una vez al entrar en la escena
        context.u8g2.clearBuffer();
        context.u8g2.drawXBM(32, 0, 128, 64, cmas);
        context.u8g2.sendBuffer();
    }

    void update(AppContext &context) override
    {
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - startTime;

        // Cambiar de escena después de la duración del splash
        if (elapsedTime > SPLASH_DURATION)
        {
            SceneManager::setScene("home", context);
        }
    }
};
#endif