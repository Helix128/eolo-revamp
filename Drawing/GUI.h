#ifndef GUI_H
#define GUI_H

#include <U8g2lib.h>

struct AppContext;

// Helper para dibujar elementos comunes en la UI
class GUI
{
public:
    // Header con batería, hora, SD, nombre del dispositivo
    static void displayHeader(AppContext &context)
    {
        context.u8g2.setFont(u8g2_font_fivepx_tr);

        // Bateria
        char batteryStr[5];
        snprintf(batteryStr, sizeof(batteryStr), "%d%%", context.getBatteryPercentage());
        context.u8g2.drawStr(108, 8, batteryStr);

        // Tiempo
        char timeStr[6];
        context.getTimeString(timeStr, sizeof(timeStr));
        context.u8g2.drawStr(2, 8, timeStr);

        // Estado de SD (estático por ahora)
        context.u8g2.drawStr(94, 8, "SD");

        // Nombre del dispositivo
        context.u8g2.drawStr(55, 8, "eolo");

        // Lineaa separadora
        context.u8g2.drawLine(0, 11, 127, 11);

        // Ícono de batería (simplificado)
        context.u8g2.drawLine(102, 1, 91, 1);
        context.u8g2.drawLine(91, 1, 91, 8);
        context.u8g2.drawLine(91, 9, 102, 9);
        context.u8g2.drawLine(103, 8, 103, 8);
        context.u8g2.drawLine(104, 7, 104, 7);
        context.u8g2.drawLine(105, 6, 105, 1);
        context.u8g2.drawLine(103, 1, 103, 1);
        context.u8g2.drawLine(105, 1, 104, 1);
    }
};

#endif