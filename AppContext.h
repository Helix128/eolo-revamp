#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

// Incluye TODOS los módulos
#include "Input.h"
#include "Motor.h"
#include "RTCManager.h"
#include "FlowSensor.h"
#include "Plantower.h"
#include "BMESensor.h"
#include "Battery.h"
#include "Logger.h"
#include "Config.h"
#include <U8g2lib.h>

typedef struct AppContext {
  // --- MÓDULOS DE HARDWARE ---
  DisplayModel& u8g2;     // Referencia al display
  Input input;            // Manejo entradas (encoder/botón)
  MotorManager motor;     // Control de motor
  FlowSensor flowSensor;  // Sensor de flujo
  Plantower plantower;    // Sensor Plantower
  BMESensor bme;          // Sensor BME280
  Battery battery;        // Monitoreo del nivel de batería
  Logger logger;          // Registro de datos en SD
  RTCManager rtc;         // Manejo RTC

  // --- ESTADO DE LA APLICACIÓN ---
  // Flujo y temporización de la aplicación
  float flujoObjetivo = 5.0;             // Flujo objetivo en L/min
  unsigned long horaInicioCaptura = 0;   // Timestamp de inicio
  unsigned long horaFinCaptura = 3600;   // Timestamp de fin
  bool usarSensorPM = true;              // Usar sensor plantower (PM)

  // Estado de la interfaz (para selectores de opciones)
  int seleccionMenu = 0;

  // Estado de la sesión
  bool capturaActiva = false;            // Whether capture is currently active
  unsigned long tiempoTranscurrido = 0;  // Elapsed time in current session

  // Constructor: Initialize modules and receive display reference
  AppContext(DisplayModel& display)
    : u8g2(display), motor(PIN_MOTOR_A, PIN_MOTOR_B) {
  }

  // Method to initialize all systems
  void begin() {
    Serial.begin(115200);
    while (!Serial) delay(10);
    Serial.println("EOLO Boot");

    // Inicializa todos los módulos
    u8g2.begin();
    input.begin();
    motor.begin();
    flowSensor.begin();
    bme.begin();
    plantower.begin();
    rtc.begin();

    // Inicializa el datalogger
    if (logger.begin()) {
      Serial.println("Logger iniciado correctamente");
    } else {
      Serial.println("Advertencia: Fallo en la inicialización del logger");
    }

    Serial.println("Inicialización de AppContext completa");
  }

  // Método para actualizar el contexto de la app
  void update() {
    input.poll();

    // Actualiza tiempo de captura si está activa
    if (capturaActiva) {
      tiempoTranscurrido = (millis() - horaInicioCaptura) / 1000;

      // Termina la captura si se ha alcanzado la duración
      if (tiempoTranscurrido >= duracionCaptura) {
        stopCapture();
      }
    }
  }

  // Helpers para operaciones comunes
  void startCapture() {
    horaInicioCaptura = millis();
    tiempoTranscurrido = 0;
    capturaActiva = true;
    Serial.println("Capture started");
  }

  void stopCapture() {
    capturaActiva = false;
    Serial.println("Capture stopped");
  }

  // Formatea tiempo transcurrido como HH:MM
  void getTimeString(char* buffer, size_t bufferSize) {
    unsigned long currentTime = millis() / 1000;
    int hours = (currentTime / 3600) % 24;
    int minutes = (currentTime / 60) % 60;
    snprintf(buffer, bufferSize, "%02d:%02d", hours, minutes);
  }

  // Helper para obtener % de batería para display
  int getBatteryPercentage() {
    int rawLevel = battery.getLevel();
    return map(rawLevel, 0, 255, 0, 100);
  }
} AppContext;

#endif