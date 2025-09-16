#ifndef HOME_SCENE_H
#define HOME_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../SceneManager.h"
#include "../GUI.h"

// Home scene with menu options
class HomeScene : public IScene
{
private:
    int lastEncoderValue = 0;

public:
    void enter(AppContext& context) override {
        // Reset selection when entering the scene
        context.seleccionMenu = 0;
        context.input.resetCounter();
        lastEncoderValue = 0;
    }

    void update(AppContext& context) override {
        // Update selection based on encoder
        int optionCount = 4; // Increased to 4 options
        context.seleccionMenu = ((int)context.input.encoderCounter / 4) % optionCount;
        
        // Handle button press
        if (context.input.buttonPressed) {
            context.input.resetButton();
            
            // Handle menu selection
            switch (context.seleccionMenu) {
                case 0:
                    // "Iniciar captura inmediata"
                    context.startCapture();
                    Serial.println("Starting immediate capture");
                    break;
                case 1:
                    // "Continuar sesion anterior"
                    Serial.println("Continue previous session selected");
                    break;
                case 2:
                    // "Iniciar nueva sesion"
                    Serial.println("Start new session selected");
                    break;
                case 3:
                    // "Ajustar flujo objetivo"
                    SceneManager::setScene("setflow", context);
                    return;
            }
        }

        // Draw the scene
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);
        
        // Draw selection arrow with animation
        int selectAnim = (millis() % 600) / 400;
        context.u8g2.setFont(u8g2_font_twelvedings_t_all);
        context.u8g2.drawStr(selectAnim, 27 + context.seleccionMenu * 12, ">");
        
        // Draw menu options
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        const char* options[] = {
            "Iniciar captura inmediata", 
            "Continuar sesion anterior", 
            "Iniciar nueva sesion",
            "Ajustar flujo objetivo"
        };
        
        for (int i = 0; i < 4; i++) {
            context.u8g2.drawStr(12, 25 + i * 12, options[i]);
        }
        
        context.u8g2.sendBuffer();
    }
};
#endif