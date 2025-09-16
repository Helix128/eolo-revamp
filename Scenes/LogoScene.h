#ifndef LOGO_SCENE_H
#define LOGO_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Logos.h"
#include "../SceneManager.h"

// Logo scene for C+
class LogoScene : public IScene {
private:
    unsigned long startTime;
    static const unsigned long SPLASH_DURATION = 3000; // 3 seconds

public:
    void enter(AppContext& context) override {
        startTime = millis();
        
        // Draw the logo once when entering the scene
        context.u8g2.clearBuffer();
        context.u8g2.drawXBM(32, 0, 128, 64, cmas);
        context.u8g2.sendBuffer();
    }

    void update(AppContext& context) override {
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - startTime;

        // Switch scene after splash duration
        if (elapsedTime > SPLASH_DURATION) {
            SceneManager::setScene("home", context);
        }
    }
};
#endif