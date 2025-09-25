#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h> // APIs de Arduino

// Máx PWM ESP32
#define MAX_PWM 1023

typedef struct DCMotor{
  int pin;
  int pwm;
} DCMotor;

// Maneja motores DC
class MotorManager
{
public:
  DCMotor** motors = nullptr; // array dinámico
  int motorCount = 0;        // cantidad

  // Constructores

  // Permite MotorManager(pin1, pin2, ...)
  template<typename... Pins>
  MotorManager(Pins... pins)
  {
    motorCount = sizeof...(pins);
    motors = new DCMotor *[motorCount];
    int pinArray[] = {static_cast<int>(pins)...};
    for (int i = 0; i < motorCount; i++)
    {
      motors[i] = new DCMotor{pinArray[i], 0};
    }
  }

  // Permite MotorManager({pin1, pin2, ...})
  MotorManager(std::initializer_list<int> pinsList)
  {
    motorCount = (int)pinsList.size();
    motors = new DCMotor *[motorCount];
    int i = 0;
    for (int p : pinsList) {
      motors[i++] = new DCMotor{p, 0};
    }
  }

  // Destructor
  ~MotorManager()
  {
    for (int i = 0; i < motorCount; i++)
    {
      delete motors[i];
    }
    delete[] motors;
  }

  // Inicializa pines
  void begin()
  {
    for (int i = 0; i < motorCount; i++)
    {
      pinMode(motors[i]->pin, OUTPUT);
      analogWrite(motors[i]->pin, 0);
    }
  }

  // Asigna PWM total; llena motores en orden
  void setPWM(int pwm)
  {
    if (pwm > motorCount * MAX_PWM)
      pwm = motorCount * MAX_PWM;
    else if (pwm < 0)
      pwm = 0;

    for (int i = 0; i < motorCount; i++)
    {
      if (pwm >= MAX_PWM)
      {
        motors[i]->pwm = MAX_PWM;
        pwm -= MAX_PWM;
      }
      else
      {
        motors[i]->pwm = pwm;
        pwm = 0;
      }
      analogWrite(motors[i]->pin, motors[i]->pwm);
    }
  }

  // Recibe porcentaje (0-100)
  void setPowerPct(int powerPct)
  {
    if (powerPct > 100)
      powerPct = 100;
    else if (powerPct < 0)
      powerPct = 0;
    int totalMax = motorCount * MAX_PWM;
    int targetPWM = (totalMax * powerPct) / 100;
    setPWM(targetPWM);
  }
};
#endif