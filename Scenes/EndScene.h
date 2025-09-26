#ifndef END_SCENE_H
#define END_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/SceneManager.h"
#include "../Drawing/GUI.h"

class EndScene : public IScene {
public:
    void enter(AppContext &context) override {
        context.input.resetCounter();
    }

    void update(AppContext &context) override {
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);

        char buf[32];
        // Mostrar resumen: inicio, fin, flujo objetivo
        unsigned long start = context.horaInicioCaptura;
        unsigned long end = context.horaFinCaptura;
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        snprintf(buf, sizeof(buf), "Inicio: %lu", start);
        context.u8g2.drawStr(6, 30, buf);
        snprintf(buf, sizeof(buf), "Fin: %lu", end);
        context.u8g2.drawStr(6, 42, buf);
        snprintf(buf, sizeof(buf), "Flujo: %.1f L/min", context.flujoObjetivo);
        context.u8g2.drawStr(6, 54, buf);

        // volumen estimado
        float elapsedMin = context.tiempoTranscurrido / 60.0;
        float volumen = (context.flujoObjetivo * elapsedMin) / 1000.0; // m3
        snprintf(buf, sizeof(buf), "Volumen: %.3f m3", volumen);
        context.u8g2.drawStr(6, 66, buf);

        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(6, 84, "Boton: Reiniciar | Volver");
        context.u8g2.sendBuffer();

        if (context.input.buttonJustPressed()) {
            context.input.resetButton();
            // Reiniciar al menu principal (home)
            SceneManager::setScene("home", context);
        }
    }
};

#endif
