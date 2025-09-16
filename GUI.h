#ifndef GUI_H
#define GUI_H

#include <U8g2lib.h>
#include "../Input.h"

// Clase helper para guardar elementos comunes de la interfaz
class GUI
{
public:
    static void displayHeader(DisplayModel &u8g2)
    {
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
};

#endif