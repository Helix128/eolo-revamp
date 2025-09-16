#ifndef GUI_H
#define GUI_H

#include <U8g2lib.h>

// Forward declaration
struct AppContext;

// Helper class for common interface elements
class GUI
{
public:
    // Display header with dynamic information from context
    static void displayHeader(AppContext& context) {
        context.u8g2.setFont(u8g2_font_fivepx_tr);
        
        // Display battery percentage
        char batteryStr[5];
        snprintf(batteryStr, sizeof(batteryStr), "%d%%", context.getBatteryPercentage());
        context.u8g2.drawStr(108, 8, batteryStr);
        
        // Display current time
        char timeStr[6];
        context.getTimeString(timeStr, sizeof(timeStr));
        context.u8g2.drawStr(2, 8, timeStr);
        
        // Display SD status (static for now)
        context.u8g2.drawStr(94, 8, "SD");
        
        // Display device name
        context.u8g2.drawStr(55, 8, "eolo");
        
        // Draw header separator line
        context.u8g2.drawLine(0, 11, 127, 11);
        
        // Draw battery icon outline
        context.u8g2.drawLine(102, 1, 91, 1);
        context.u8g2.drawLine(91, 1, 91, 8);
        context.u8g2.drawLine(91, 9, 102, 9);
        context.u8g2.drawLine(103, 8, 103, 8);
        context.u8g2.drawLine(104, 7, 104, 7);
        context.u8g2.drawLine(105, 6, 105, 1);
        context.u8g2.drawLine(103, 1, 103, 1);
        context.u8g2.drawLine(105, 1, 104, 1);
    }

    // Legacy method for compatibility (delegates to the new one)
    static void displayHeader(DisplayModel &u8g2) {
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