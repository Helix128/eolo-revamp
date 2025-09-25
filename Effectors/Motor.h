#ifndef MOTOR_H
#define MOTOR_H

// Valor máximo de PWM de ESP32
#define MAX_PWM 1023

typedef struct DCMotor{
  int pin;
  int pwm;
} DCMotor;

// Clase para manejar los motores de vacío DC
class MotorManager
{
public:
  DCMotor** motors = nullptr; // Array dinámico de motores
  int motorCount = 0;         // Cantidad de motores

  // Constructor
  MotorManager(int... pins)
  {
    motorCount = sizeof...(pins);
    motors = new DCMotor *[motorCount];
    int pinArray[] = {pins...};
    for (int i = 0; i < motorCount; i++)
    {
      motors[i] = new DCMotor{pinArray[i], 0};
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

  // Inicialización de pines
  void begin()
  {
    for (int i = 0; i < motorCount; i++)
    {
      pinMode(motors[i]->pin, OUTPUT);
      analogWrite(motors[i]->pin, 0);
    }
  }

  // Función para asignar valor a PWM de forma directa
  // Enciende un motor hasta llegar al máximo antes de encender el segundo
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

  // Similar a setPWM pero con la facilidad de recibir un porcentaje (0%-100%)
  void setPowerPct(int powerPct)
  {
    if (powerPct > 100)
      powerPct = 100;
    else if (powerPct < 0)
      powerPct = 0;
    float targetPWM = (float)MAX_PWM;
    targetPWM *= powerPct;
    setPWM((int)targetPWM);
  }
};
#endif