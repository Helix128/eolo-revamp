#ifndef ESPERA_SCENE_H
#define ESPERA_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/SceneManager.h"
#include "../Drawing/GUI.h"

// Escena de espera hasta hora de inicio, muestra flujo actual
class EsperaScene : public IScene
{
public:
    void enter(AppContext& context) override {
        context.input.resetCounter();
    }

    void update(AppContext& context) override {
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);

        int w = context.u8g2.getDisplayWidth();

        context.u8g2.setFont(u8g2_font_6x12_tr);
        context.u8g2.drawStr(8, 28, "INICIO:");

        unsigned long nowSecs = millis() / 1000;
        unsigned long startSecs = context.horaInicioCaptura;
        int startH = (startSecs / 3600) % 24;
        int startM = (startSecs / 60) % 60;
        char startBuf[6];
        snprintf(startBuf, sizeof(startBuf), "%02d:%02d", startH, startM);

        context.u8g2.setFont(u8g2_font_fub30_tr);
        int tw = context.u8g2.getStrWidth(startBuf);
        context.u8g2.drawStr(w - tw - 8, 34, startBuf);

        context.u8g2.setFont(u8g2_font_6x12_tr);
        context.u8g2.drawStr(8, 68, "FLUJO:");

        float flow = 0.0f;
        // TODO: adaptar según la API real del sensor de flujo
        flow = context.flowSensor.getFlow();

        char flowBuf[10];
        snprintf(flowBuf, sizeof(flowBuf), "%.1f", flow);

        context.u8g2.setFont(u8g2_font_fub24_tr);
        int fw = context.u8g2.getStrWidth(flowBuf);
        context.u8g2.drawStr(w - fw - 8, 64, flowBuf);

        context.u8g2.setFont(u8g2_font_6x10_tr);
        context.u8g2.drawStr(w - 8 - context.u8g2.getStrWidth("(L/Min)"), 82, "(L/Min)");

        context.u8g2.sendBuffer();

        if (startSecs > 0 && nowSecs >= startSecs && !context.capturaActiva) {
            context.startCapture();
        }

        // TODO: permitir inicio manual con context.input.buttonPressed()
    }
};

#endif // ESPERA_SCENE_H