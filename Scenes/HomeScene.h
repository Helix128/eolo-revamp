#ifndef HOME_SCENE_H
#define HOME_SCENE_H

#include "IScene.h"
#include "../AppContext.h"
#include "../SceneManager.h"
#include "../GUI.h"

// Escena principal con opciones de menú
class HomeScene : public IScene
{
private:
    int ultimoValorEncoder = 0;

public:
    void enter(AppContext& context) override {
        // Reiniciar selección al entrar a la escena
        context.seleccionMenu = 0;
        context.input.resetCounter();
        ultimoValorEncoder = 0;
    }

    void update(AppContext& context) override {
        // Actualizar selección basado en encoder
        int cantidadOpciones = 3;
        context.seleccionMenu = ((int)context.input.encoderCounter / 4) % cantidadOpciones;

        // Manejar presión del botón
        if (context.input.buttonPressed) {
            context.input.resetButton();
            
            // Manejar selección del menú
            switch (context.seleccionMenu) {
                case 0:
                    // "Iniciar captura inmediata"
                    context.startCapture();
                    Serial.println("Iniciando captura inmediata");
                    SceneManager::setScene("flujo", context);
                    break;
                case 1:
                    // "Continuar sesion anterior"
                    // TODO cargar flujo previo (?) confirmar con sebas
                    // TODO crear dashboard
                    Serial.println("Continuar sesión anterior seleccionado");
                    SceneManager::setScene("dashboard", context);
                    break;
                case 2:
                    // "Iniciar nueva sesion"
                    Serial.println("Iniciar nueva sesión seleccionado");
                    SceneManager::setScene("flujo", context);
                    break;
            }
        }

        // Dibujar la escena
        context.u8g2.clearBuffer();
        GUI::displayHeader(context);
        
        // Dibujar flecha de selección con animación
        int animSeleccion = (millis() % 600) / 400;
        context.u8g2.setFont(u8g2_font_twelvedings_t_all);
        context.u8g2.drawStr(animSeleccion, 27 + context.seleccionMenu * 12, ">");
        
        // Dibujar opciones del menú
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        const char* opciones[] = {
            "Iniciar captura inmediata", 
            "Continuar sesion anterior", 
            "Iniciar nueva sesion",
        };
        
        for (int i = 0; i < cantidadOpciones; i++) {
            context.u8g2.drawStr(12, 25 + i * 12, opciones[i]);
        }
        
        context.u8g2.sendBuffer();
    }
};
#endif