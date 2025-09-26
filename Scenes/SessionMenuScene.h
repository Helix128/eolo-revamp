#ifndef SESSION_MENU_SCENE_H
#define SESSION_MENU_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../Drawing/SceneManager.h"
#include "../Drawing/GUI.h"

class SessionMenuScene : public IScene {
public:
    void enter(AppContext &context) override {
        context.input.resetCounter();
        context.seleccionMenu = 0;
    }

    void update(AppContext &context) override {
    int opciones = 8;
    context.seleccionMenu = context.input.getEncoderValue() % opciones;

        context.u8g2.clearBuffer();
        GUI::displayHeader(context);
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        const char *items[] = {
            "Toggle sensor PM",
            context.paused ? "Reanudar sesion" : "Pausar sesion",
            "Terminar sesion",
            "Modificar flujo",
            "Modificar hora fin",
            "Estado motores",
            "Reiniciar eolo",
            "Volver al dashboard",
        };

        for (int i = 0; i < opciones; i++) {
            if (i == context.seleccionMenu) {
                context.u8g2.drawStr(6, 24 + i * 10, ">");
            }
            context.u8g2.drawStr(12, 24 + i * 10, items[i]);
        }
        context.u8g2.sendBuffer();

        if (context.input.buttonJustPressed()) {
            context.input.resetButton();
            switch (context.seleccionMenu) {
                case 0: // toggle PM
                    context.usarSensorPM = !context.usarSensorPM;
                    break;
                case 1: // pause / resume
                    if (context.paused) {
                        context.resumeCapture();
                    } else {
                        context.pauseCapture();
                    }
                    break;
                    break;
                case 2: // stop
                    context.stopCapture();
                    SceneManager::setScene("end", context);
                    return;
                case 3: // modify flow
                    SceneManager::setScene("flujo", context);
                    return;
                case 4: // modify end time
                    SceneManager::setScene("hora", context);
                    return;
                case 5: // motor status
                    context.u8g2.clearBuffer();
                    GUI::displayHeader(context);
                    context.u8g2.setFont(u8g2_font_fivepx_tr);
                    for (int i = 0; i < context.motor.motorCount; i++) {
                        char buf[32];
                        snprintf(buf, sizeof(buf), "Pin %d PWM %d", context.motor.motors[i]->pin, context.motor.motors[i]->pwm);
                        context.u8g2.drawStr(6, 30 + i * 10, buf);
                    }
                    context.u8g2.sendBuffer();
                    // wait for button to continue (non-blocking) - next update will handle input
                    return;
                    break;
                case 6: // restart
#ifdef ESP32
                    ESP.restart();
#endif
                    break;
                case 7:
                    SceneManager::setScene("dashboard", context);
                    return;
            }
        }
    }
};

#endif
