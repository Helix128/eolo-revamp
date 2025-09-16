#ifndef SET_FLOW_SCENE_H
#define SET_FLOW_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../SceneManager.h"
#include "../GUI.h"

// Scene for setting the target flow rate
class SetFlowScene : public IScene {
private:
    static constexpr float MIN_FLOW = 1.0f;
    static constexpr float MAX_FLOW = 20.0f;
    static constexpr float FLOW_STEP = 0.1f;

public:
    void enter(AppContext& context) override {
        // When entering, sync encoder counter with current flow value
        context.input.resetCounter();
        context.input.encoderCounter = (int)(context.flujoObjetivo * 10);
        Serial.println("Entered SetFlowScene");
    }

    void update(AppContext& context) override {
        // 1. LOGIC: Update state from input
        float newFlow = context.input.encoderCounter * FLOW_STEP;
        
        // Constrain flow within valid range
        if (newFlow < MIN_FLOW) {
            newFlow = MIN_FLOW;
            context.input.encoderCounter = (int)(MIN_FLOW / FLOW_STEP);
        } else if (newFlow > MAX_FLOW) {
            newFlow = MAX_FLOW;
            context.input.encoderCounter = (int)(MAX_FLOW / FLOW_STEP);
        }
        
        context.flujoObjetivo = newFlow;
        
        // Handle button press - save and return to previous scene
        if (context.input.buttonPressed) {
            context.input.resetButton();
            Serial.print("Flow set to: ");
            Serial.println(context.flujoObjetivo);
            SceneManager::setScene("home", context);
            return;
        }

        // 2. DRAWING: Show current state
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);
        
        // Draw title
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(35, 25, "Ajustar Flujo");
        
        // Draw current flow value
        char buffer[10];
        dtostrf(context.flujoObjetivo, 4, 1, buffer);
        
        context.u8g2.setFont(u8g2_font_logisoso32_tr);
        int textWidth = context.u8g2.getStrWidth(buffer);
        int x = (128 - textWidth) / 2; // Center horizontally
        context.u8g2.drawStr(x, 50, buffer);
        
        // Draw units
        context.u8g2.setFont(u8g2_font_unifont_t_symbols);
        context.u8g2.drawStr(x + textWidth + 5, 50, "L/min");
        
        // Draw instructions
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(20, 60, "Girar: ajustar, Pulsar: guardar");
        
        context.u8g2.sendBuffer();
    }
};

#endif