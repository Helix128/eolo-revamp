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

public:
    void enter(AppContext& context) override {
        // Al entrar, solo resetear el contador del encoder
        context.input.resetCounter();
        Serial.println("Entrando a FlujoScene");
    }

    void update(AppContext& context) override {
        // Actualizar estado desde input
        // Mapear encoder (0-255) al rango de flujo (MIN_FLUJO - MAX_FLUJO)
        float rangoFlujo = MAX_FLUJO - MIN_FLUJO;
        float nuevoFlujo = MIN_FLUJO + (context.input.encoderCounter / 255.0f) * rangoFlujo;
        
        context.flujoObjetivo = nuevoFlujo;
        
        // Manejar presión del botón - guardar y regresar a escena anterior
        if (context.input.buttonPressed) {
            context.input.resetButton();
            Serial.print("Flujo configurado a: ");
            Serial.println(context.flujoObjetivo);
            // TODO -> crear dashboard
            if(context.capturaActiva) // si está en modo activo
                SceneManager::setScene("dashboard", context); // captura ahora, no pide hora
                return;
            else{ // pide hora para capturar después
                SceneManager::setScene("hora", context);
                return;
            }
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
        
        context.u8g2.setFont(u8g2_font_profont17_tr);
        int anchoTexto = context.u8g2.getStrWidth(buffer);
        int x = (128 - anchoTexto) / 2; // Centrar horizontalmente
        context.u8g2.drawStr(x, 50, buffer);
        
        // Dibujar unidades
        context.u8g2.setFont(u8g2_font_unifont_t_symbols);
        context.u8g2.drawStr(x + anchoTexto + 5, 50, "L/min");
    
        context.u8g2.sendBuffer();
    }
};

#endif