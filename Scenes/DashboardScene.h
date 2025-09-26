#ifndef DASHBOARD_SCENE_H
#define DASHBOARD_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/SceneManager.h"
#include "../Drawing/GUI.h"

// Escena principal con opciones de menú
class DashboardScene : public IScene
{
public:
    void enter(AppContext& context) override {
        context.input.resetCounter();
    }

    void update(AppContext& context) override {
        // actualizar sensores
        context.flowSensor.readData();
        context.bme.readData();
        if (context.usarSensorPM) context.plantower.readData();

    unsigned long now = context.nowSeconds();

        // calcular volumen (m3)
        float elapsedMinutes = context.tiempoTranscurrido / 60.0f;
        float volumen = (context.flowSensor.flow * elapsedMinutes) / 1000.0f;

        // tiempo restante
        long remaining = 0;
        if (context.horaFinCaptura > now) remaining = context.horaFinCaptura - now;

        context.u8g2.clearBuffer();
        GUI::displayHeader(context);

        // mostrar flujo y volumen
        context.u8g2.setFont(u8g2_font_6x12_tr);
        context.u8g2.drawStr(6, 28, "Flujo:");
        char buf[32];
        snprintf(buf, sizeof(buf), "%.1f L/min", context.flowSensor.flow);
        context.u8g2.drawStr(60, 28, buf);

        context.u8g2.drawStr(6, 44, "Volumen:");
        snprintf(buf, sizeof(buf), "%.3f m3", volumen);
        context.u8g2.drawStr(60, 44, buf);

        // mostrar BME
        context.u8g2.drawStr(6, 60, "T/H/P:");
        snprintf(buf, sizeof(buf), "%.1fC %.0f%% %.0fhPa", context.bme.temperature, context.bme.humidity, context.bme.pressure);
        context.u8g2.drawStr(60, 60, buf);

        // mostrar PM rotativo cada 3s
        static unsigned long lastCycle = 0;
        static int cycleIndex = 0;
        if (now - lastCycle >= 3)
        {
            lastCycle = now;
            cycleIndex = (cycleIndex + 1) % 3;
        }

        if (context.usarSensorPM)
        {
            if (cycleIndex == 0) snprintf(buf, sizeof(buf), "PM1: %.1f", context.plantower.pm1);
            else if (cycleIndex == 1) snprintf(buf, sizeof(buf), "PM2.5: %.1f", context.plantower.pm25);
            else snprintf(buf, sizeof(buf), "PM10: %.1f", context.plantower.pm10);
            context.u8g2.drawStr(6, 76, buf);
        }

        // mostrar objetivo y tiempos
        snprintf(buf, sizeof(buf), "Objetivo: %.1f L/min", context.flujoObjetivo);
        context.u8g2.drawStr(6, 92, buf);
        snprintf(buf, sizeof(buf), "Transcurrido: %lus", context.tiempoTranscurrido);
        context.u8g2.drawStr(6, 104, buf);
        snprintf(buf, sizeof(buf), "Restante: %lds", remaining);
        context.u8g2.drawStr(6, 116, buf);

        context.u8g2.sendBuffer();

        // boton abre menu de sesion
        if (context.input.buttonJustPressed())
        {
            context.input.resetButton();
            SceneManager::setScene("session_menu", context);
            return;
        }
    }
};
#endif // DASHBOARD_SCENE_H