#ifndef PLANTOWER_SCENE_H
#define PLANTOWER_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/SceneManager.h"
#include "../Drawing/GUI.h"

// Escena para activar/desactivar sensor Plantower
class PlantowerScene : public IScene
{
public:
    void enter(AppContext& context) override {
        context.seleccionMenu = context.usarSensorPM ? 0 : 1;
        context.input.resetCounter();
    }

    void update(AppContext& context) override {
        const char* aviso = "(DISMINUYE DURACIÓN BATERÍA)";
        const char* optSi = "SI";
        const char* optNo = "NO";

        context.u8g2.clearBuffer();
        GUI::displayHeader(context);

        int w = context.u8g2.getDisplayWidth();

        context.u8g2.setFont(u8g2_font_7x14B_tr);
        context.u8g2.drawStr(8, 24, "¿USAR SENSOR DE MATERIAL");
        context.u8g2.drawStr(8, 44, "PARTICULADO?");

        context.u8g2.setFont(u8g2_font_5x8_tr);
        context.u8g2.drawStr(8, 58, aviso);

        const int optY = 80;
        const int boxW = 48;
        const int boxH = 18;
        const int siX = 24;
        const int noX = w - boxW - 24;

        if (context.seleccionMenu == 0) {
            context.u8g2.setDrawColor(1);
            context.u8g2.drawBox(siX, optY - boxH + 4, boxW, boxH);
            context.u8g2.setDrawColor(0);
            context.u8g2.setFont(u8g2_font_7x14B_tr);
            int tw = context.u8g2.getStrWidth(optSi);
            context.u8g2.drawStr(siX + (boxW - tw)/2, optY - 4, optSi);

            context.u8g2.setDrawColor(1);
            context.u8g2.setFont(u8g2_font_7x14_tr);
            context.u8g2.drawStr(noX + 8, optY - 4, optNo);
        } else {
            context.u8g2.setDrawColor(1);
            context.u8g2.setFont(u8g2_font_7x14_tr);
            context.u8g2.drawStr(siX + 8, optY - 4, optSi);

            context.u8g2.drawBox(noX, optY - boxH + 4, boxW, boxH);
            context.u8g2.setDrawColor(0);
            context.u8g2.setFont(u8g2_font_7x14B_tr);
            int tw = context.u8g2.getStrWidth(optNo);
            context.u8g2.drawStr(noX + (boxW - tw)/2, optY - 4, optNo);
            context.u8g2.setDrawColor(1);
        }

        context.u8g2.setDrawColor(1);
        context.u8g2.sendBuffer();

        // Manejo del encoder: moverse entre opciones y confirmar con botón
        if (context.input.encoderMovedRight()) {
            context.seleccionMenu = min(1, context.seleccionMenu + 1);
        }
        if (context.input.encoderMovedLeft()) {
            context.seleccionMenu = max(0, context.seleccionMenu - 1);
        }
        if (context.input.buttonJustPressed()) {
            // Confirmar selección: SI -> usarSensorPM = true (seleccionMenu == 0)
            context.usarSensorPM = (context.seleccionMenu == 0);
            // Reiniciar estado del botón en el driver para evitar retriggers
            context.input.resetButton();
            // Pequeña retroalimentación por serial
            Serial.print("Plantower uso: ");
            Serial.println(context.usarSensorPM ? "SI" : "NO");
            // Navegar según si la captura ya está activa
            if (context.capturaActiva) {
                SceneManager::setScene("dashboard", context);
            } else {
                SceneManager::setScene("espera", context);
            }
        }
    }
};

#endif // PLANTOWER_SCENE_H