#ifndef GUI_H
#define GUI_H

#include <U8g2lib.h>
#include "Logos.h"

class GUI {
private:
  DisplayModel& u8g2;
  Input& input;
  char*& pantallaActual;
  int& seleccionId;

public:
  GUI(DisplayModel& display, Input& input, char*& pantalla, int& seleccion) 
    : u8g2(display), input(input), pantallaActual(pantalla), seleccionId(seleccion) {}

  void begin() {
    u8g2.begin();
  }

  void drawSplash() {
    u8g2.clearBuffer();
    u8g2.drawXBM(32, 0, 128, 64, cmas);
    u8g2.sendBuffer();
  }

  void displayHeader() {
    u8g2.setFont(u8g2_font_fivepx_tr);
    u8g2.drawStr(108, 8, "100%");
    u8g2.drawStr(2, 8, "00:00");
    u8g2.drawStr(94, 8, "SD");
    u8g2.drawStr(55, 8, "eolo");
    u8g2.drawLine(0, 11, 127, 11);
    u8g2.drawLine(102, 1, 91, 1);
    u8g2.drawLine(91, 1, 91, 8);
    u8g2.drawLine(91, 9, 102, 9);
    u8g2.drawLine(103, 8, 103, 8);
    u8g2.drawLine(104, 7, 104, 7);
    u8g2.drawLine(105, 6, 105, 1);
    u8g2.drawLine(103, 1, 103, 1);
    u8g2.drawLine(105, 1, 104, 1);
  }

  void displayInicio() {
    u8g2.clearBuffer();
    displayHeader();
    int selectAnim = (millis() % 600) / 400;
    u8g2.setFont(u8g2_font_twelvedings_t_all);
    u8g2.drawStr((selectAnim), 27+seleccionId*15, ">");
    u8g2.setFont(u8g2_font_fivepx_tr);
    char* options[] = {"Iniciar captura inmediata", "Continuar sesion anterior", "Iniciar nueva sesion"};
    char* targets[] = {"capturaNow","session","flux"};
    int optionCount = 3;
    seleccionId = ((int)input.encoderCounter/4)%optionCount;
    for(int i = 0;i<3;i++){
      u8g2.drawStr(12,25+i*15,options[i]);
    }
    u8g2.sendBuffer();
  }

  void displayFlujo(){
    u8g2.clearBuffer();
    displayHeader();
    u8g2.setFont(u8g2_font_bitcasual_tr);
    u8g2.drawStr(56, 35, "5");
    u8g2.drawStr(65, 35, "0");
    u8g2.setFont(u8g2_font_fivepx_tr);
    u8g2.drawStr(30, 22, "Flujo de captura");
    u8g2.drawStr(54, 43, "l/min");
    u8g2.drawBox(63, 34, 1, 1);
    u8g2.sendBuffer();
  }
};

#endif // GUI_H
