#ifndef LOGO_SCENE_H
#define LOGO_SCENE_H

#include "../Config.h"
#include <U8g2lib.h>
#include "../Input.h"
#include "IScene.h"
#include "../SceneManager.h"
#include "../GUI.h"

// Escena del logo de C+
class HomeScene : public IScene
{
public:
    void draw(DisplayModel &u8g2, Input &input) override
    {
        u8g2.clearBuffer();
        GUI::displayHeader(u8g2);
        int selectAnim = (millis() % 600) / 400;
        u8g2.setFont(u8g2_font_twelvedings_t_all);
        u8g2.drawStr((selectAnim), 27 + seleccionId * 15, ">");
        u8g2.setFont(u8g2_font_fivepx_tr);
        char *options[] = {"Iniciar captura inmediata", "Continuar sesion anterior", "Iniciar nueva sesion"};
        char *targets[] = {"capturaNow", "session", "flux"};
        int optionCount = 3;
        seleccionId = ((int)input.encoderCounter / 4) % optionCount;
        for (int i = 0; i < 3; i++)
        {
            u8g2.drawStr(12, 25 + i * 15, options[i]);
        }
        u8g2.sendBuffer();
    }
};
#endif