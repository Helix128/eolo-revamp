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
        if (context.horaInicioCaptura == 0) context.horaInicioCaptura = 8 * 3600;
        if (context.horaFinCaptura == 3600) context.horaFinCaptura = 9 * 3600;

        // Inicializar encoderVirtual y prev raw según la hora actualmente editable
        int minutoActual = (context.horaInicioCaptura / 60) % 1440;
        context.encoderVirtual = minutoActual;
        context.prevEncoderRaw = context.input.encoderCounter;
    }

    void update(AppContext& context) override {
        // Leer raw y calcular delta con detección de wrap (0..255)
        uint8_t raw = context.input.encoderCounter;
        int8_t delta = (int8_t)(raw - context.prevEncoderRaw);
        if (delta > 127) delta -= 256;
        else if (delta < -127) delta += 256;
        context.prevEncoderRaw = raw;

        // Si cambio de selección, inicializar encoderVirtual con ese valor
        if (context.seleccionMenu == 0) {
            // editar inicio
            // si no se ha movido desde la entrada, encoderVirtual ya tiene valor; aplicamos delta
            context.encoderVirtual += delta;
        } else if (context.seleccionMenu == 1) {
            // editar fin
            // si acabamos de pasar a esta selección el encoderVirtual debe sincronizarse
            // pero para simplicidad: cuando se incrementa seleccion se resetea prev raw y encoderVirtual
            context.encoderVirtual += delta;
        }

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

        if (context.seleccionMenu == 0) {
            context.u8g2.drawBox(6, yInicio - 14, 116, 18);
            context.u8g2.setDrawColor(0);
            context.u8g2.drawStr(xLabel, yInicio, "Inicio:");
            context.u8g2.drawStr(xValue, yInicio, bufInicio);
            context.u8g2.setDrawColor(1);
        } else {
            context.u8g2.drawStr(xLabel, yInicio, "Inicio:");
            context.u8g2.drawStr(xValue, yInicio, bufInicio);
        }

        if (context.seleccionMenu == 1) {
            context.u8g2.drawBox(6, yFin - 14, 116, 18);
            context.u8g2.setDrawColor(0);
            context.u8g2.drawStr(xLabel, yFin, "Fin:");
            context.u8g2.drawStr(xValue, yFin, bufFin);
            context.u8g2.setDrawColor(1);
        } else {
            context.u8g2.drawStr(xLabel, yFin, "Fin:");
            context.u8g2.drawStr(xValue, yFin, bufFin);
        }

        context.u8g2.setFont(u8g2_font_fivepx_tr);
        context.u8g2.drawStr(10, 95, "Presione boton para siguiente");
        context.u8g2.sendBuffer();

        // Botón: avanzar selección / confirmar
        if (context.input.buttonPressed) {
            context.input.resetButton();
            context.seleccionMenu++;
            if (context.seleccionMenu > 1) {
                context.horaInicioCaptura = inicioMin * 60UL;
                context.horaFinCaptura = finMin * 60UL;
                if (context.capturaActiva) {
                    SceneManager::setScene("dashboard", context);
                    return;
                } else {
                    SceneManager::setScene("espera", context);
                    return;
                }
            }
            // al cambiar selección sincronizar encoderVirtual con la nueva hora y resetear prev raw
            if (context.seleccionMenu == 1) {
                context.encoderVirtual = finMin;
            } else if (context.seleccionMenu == 0) {
                context.encoderVirtual = inicioMin;
            }
            context.prevEncoderRaw = context.input.encoderCounter;
        }
    }
};
#endif // HORA_SCENE_H