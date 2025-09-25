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
        // Bateria
        char batteryStr[5];
        snprintf(batteryStr, sizeof(batteryStr), "%d%%", context.getBatteryPercentage());
        context.u8g2.drawStr(108, 8, batteryStr);

        // Tiempo
        char timeStr[6];
        context.getTimeString(timeStr, sizeof(timeStr));

        u8g2.setFont(u8g2_font_TimesNewPixel_tr);
        // Nombre del dispositivo
        u8g2.drawStr(51, 11, "eolo");
        u8g2.setFont(u8g2_font_fivepx_tr);

        // Estado de la SD
        char* sdStatus = "OK!";
        if (Logger::status == SD_ERROR)
            sdStatus = "ERR!";
        else if (Logger::status == SD_WRITING)
            sdStatus = "I/O";
        u8g2.drawStr(111, 9, sdStatus);
        u8g2.drawStr(98, 9, "SD:");

        // Baterías
        u8g2.drawFrame(89, 1, 6, 11);
        u8g2.drawFrame(82, 1, 6, 11);

        // Línea separadora
        u8g2.drawLine(0, 13, 127, 13);
    }
};

#endif