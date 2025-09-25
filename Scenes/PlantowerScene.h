#ifndef PLANTOWER_SCENE_H
#define PLANTOWER_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/SceneManager.h"
#include "../Drawing/GUI.h"

// Escena principal con opciones de menú
class PlantowerScene : public IScene
{
public:
    void enter(AppContext& context) override {
        context.input.resetCounter();
    }

    void update(AppContext& context) override {
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);
        context.u8g2.sendBuffer();
    }
};
#endif // PLANTOWER_SCENE_H