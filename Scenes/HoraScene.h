#ifndef HORA_SCENE_H
#define HORA_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/SceneManager.h"
#include "../Drawing/GUI.h"

// Escena principal con opciones de menú
class HoraScene : public IScene
{
public:
    void enter(AppContext& context) override {
        context.input.resetCounter();
        context.seleccionMenu = 0;
        if (context.horaInicioCaptura == 0) context.horaInicioCaptura = 8 * 3600; // default 08:00 (seconds-of-day)
        if (context.horaFinCaptura == 3600) context.horaFinCaptura = 9 * 3600;   // default 09:00

        // decidir minuto inicial para el encoder (si horaInicioCaptura está en epoch, extraer minuto del día)
    unsigned long now = context.nowSeconds();
        int minutoActual = 0;
        if (context.horaInicioCaptura > 86400UL) {
            minutoActual = (context.horaInicioCaptura % 86400UL) / 60;
        } else {
            minutoActual = (context.horaInicioCaptura / 60) % 1440;
        }
        context.encoderVirtual = minutoActual;
        // sincronizar con el contador raw actual
        uint8_t raw = context.input.getEncoderValue(); (void)raw;
    }

    void update(AppContext& context) override {
    // Usar getEncoderDelta() para mover encoderVirtual proporcional al giro (wrap-aware)
    int delta = context.input.getEncoderDelta();
    if (delta != 0) context.encoderVirtual += delta;

        // Limitar rango 0..1439 (minutos del día)
        if (context.encoderVirtual < 0) context.encoderVirtual = 0;
        if (context.encoderVirtual > 1439) context.encoderVirtual = 1439;

        // Aplicar el valor a la selección actual
        int inicioMin = (context.horaInicioCaptura / 60) % 1440;
        int finMin = (context.horaFinCaptura / 60) % 1440;
        if (context.seleccionMenu == 0) inicioMin = context.encoderVirtual;
        else if (context.seleccionMenu == 1) finMin = context.encoderVirtual;

        // Formatear HH:MM
        auto formatHM = [](int totalMin, char* buf, size_t bufSize){
            int h = (totalMin / 60) % 24;
            int m = totalMin % 60;
            snprintf(buf, bufSize, "%02d:%02d", h, m);
        };
        char bufInicio[6], bufFin[6];
        formatHM(inicioMin, bufInicio, sizeof(bufInicio));
        formatHM(finMin, bufFin, sizeof(bufFin));

        // UI
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(24, 25, "Configurar Horas");
        context.u8g2.setFont(u8g2_font_profont17_tr);
        int yInicio = 40, yFin = 70, xLabel = 10, xValue = 80;

        // determinar si cada hora cae hoy o mañana para mostrar etiqueta
    unsigned long now = context.nowSeconds();
    unsigned long today0 = now - (now % 86400UL);
    unsigned long candInicio = context.epochForNextMinuteOfDay(inicioMin);
        bool inicioEsManana = false;
        if (candInicio < now) {
            candInicio += 86400UL;
            inicioEsManana = true;
        }
        unsigned long candFin = context.epochForNextMinuteOfDay(finMin);
        bool finEsManana = (candFin - now) >= 3600; // approximacion simple

        if (context.seleccionMenu == 0) {
            context.u8g2.drawBox(6, yInicio - 14, 116, 18);
            context.u8g2.setDrawColor(0);
            context.u8g2.drawStr(xLabel, yInicio, "Inicio:");
            context.u8g2.drawStr(xValue, yInicio, bufInicio);
            // mostrar si es Hoy/Mañana
            context.u8g2.setDrawColor(1);
            if (inicioEsManana) context.u8g2.drawStr(xValue + 40, yInicio, "Manana");
            else context.u8g2.drawStr(xValue + 40, yInicio, "Hoy");
        } else {
            context.u8g2.drawStr(xLabel, yInicio, "Inicio:");
            context.u8g2.drawStr(xValue, yInicio, bufInicio);
            if (inicioEsManana) context.u8g2.drawStr(xValue + 40, yInicio, "Manana");
            else context.u8g2.drawStr(xValue + 40, yInicio, "Hoy");
        }

        if (context.seleccionMenu == 1) {
            context.u8g2.drawBox(6, yFin - 14, 116, 18);
            context.u8g2.setDrawColor(0);
            context.u8g2.drawStr(xLabel, yFin, "Fin:");
            context.u8g2.drawStr(xValue, yFin, bufFin);
            context.u8g2.setDrawColor(1);
            if (finEsManana) context.u8g2.drawStr(xValue + 40, yFin, "Manana");
            else context.u8g2.drawStr(xValue + 40, yFin, "Hoy");
        } else {
            context.u8g2.drawStr(xLabel, yFin, "Fin:");
            context.u8g2.drawStr(xValue, yFin, bufFin);
            if (finEsManana) context.u8g2.drawStr(xValue + 40, yFin, "Manana");
            else context.u8g2.drawStr(xValue + 40, yFin, "Hoy");
        }

        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(10, 95, "Presione boton para siguiente");
        context.u8g2.sendBuffer();

        // Botón: avanzar selección / confirmar (usar helper con debounce)
        if (context.input.buttonJustPressed()) {
            context.input.resetButton();
            context.seleccionMenu++;
            if (context.seleccionMenu > 1) {
                // convertir selecciones (minutos del día) a epoch usando RTC
                unsigned long startEpoch = context.epochForNextMinuteOfDay(inicioMin);
                unsigned long endEpoch = context.epochForNextMinuteOfDay(finMin);
                if (endEpoch <= startEpoch) endEpoch += 86400UL;

                context.horaInicioCaptura = startEpoch;
                context.horaFinCaptura = endEpoch;

                // siguiente paso: seleccionar uso de Plantower
                SceneManager::setScene("plantower", context);
                return;
            }
            // sincronizar encoderVirtual con la nueva hora
            if (context.seleccionMenu == 1) {
                context.encoderVirtual = finMin;
            } else if (context.seleccionMenu == 0) {
                context.encoderVirtual = inicioMin;
            }
            // sincronizar raw con el encoder al cambiar selección
            uint8_t raw2 = context.input.getEncoderValue(); (void)raw2;
        }
    }
};

#endif // HORA_SCENE_H