#ifndef FLUJO_SCENE_H
#define FLUJO_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../SceneManager.h"
#include "../GUI.h"

// Escena para configurar el flujo objetivo
class FlujoScene : public IScene {
private:
    static constexpr float MIN_FLUJO = 1.0f;
    static constexpr float MAX_FLUJO = 20.0f;
    static constexpr float PASO_FLUJO = 0.1f;

public:
    void enter(AppContext& context) override {
        // Al entrar, sincronizar contador del encoder con el valor actual de flujo
        context.input.resetCounter();
        context.input.encoderCounter = (int)(context.flujoObjetivo * 10);
        Serial.println("Entrando a FlujoScene");
    }

    void update(AppContext& context) override {
        // Actualizar estado desde input
        float nuevoFlujo = context.input.encoderCounter * PASO_FLUJO;
        
        // Restringir flujo dentro del rango válido
        if (nuevoFlujo < MIN_FLUJO) {
            nuevoFlujo = MIN_FLUJO;
            context.input.encoderCounter = (int)(MIN_FLUJO / PASO_FLUJO);
        } else if (nuevoFlujo > MAX_FLUJO) {
            nuevoFlujo = MAX_FLUJO;
            context.input.encoderCounter = (int)(MAX_FLUJO / PASO_FLUJO);
        }
        
        context.flujoObjetivo = nuevoFlujo;
        
        // Manejar presión del botón - guardar y regresar a escena anterior
        if (context.input.buttonPressed) {
            context.input.resetButton();
            Serial.print("Flujo configurado a: ");
            Serial.println(context.flujoObjetivo);
            // TODO -> crear dashboard
            SceneManager::setScene("dashboard", context);
            return;
        }

        // Mostrar estado actual
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);
        
        // Dibujar título
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(35, 25, "Ajustar Flujo");
        
        // Dibujar valor actual del flujo
        char buffer[10];
        dtostrf(context.flujoObjetivo, 4, 1, buffer);
        
        context.u8g2.setFont(u8g2_font_logisoso32_tr);
        int anchoTexto = context.u8g2.getStrWidth(buffer);
        int x = (128 - anchoTexto) / 2; // Centrar horizontalmente
        context.u8g2.drawStr(x, 50, buffer);
        
        // Dibujar unidades
        context.u8g2.setFont(u8g2_font_unifont_t_symbols);
        context.u8g2.drawStr(x + anchoTexto + 5, 50, "L/min");
        
        // Dibujar instrucciones
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(20, 60, "Girar: ajustar, Pulsar: guardar");
        
        context.u8g2.sendBuffer();
    }
};

#endif