#ifndef MOTOR_H
#define MOTOR_H

// Valor máximo de PWM de ESP32
#define MAX_PWM 1023

// Clase para manejar los motores de vacío DC
class MotorManager
{
public:
  // Pines de PWM para motores
  int motorA;
  int motorB;
  // Velocidades actuales
  int pwmA;
  int pwmB;

  // Constructor
  MotorManager(int motorAPin, int motorBPin)
  {
    motorA = motorAPin;
    motorB = motorBPin;
    pwmA = 0;
    pwmB = 0;
  }

  // Inicialización de pines
  void begin()
  {
    pinMode(motorA, OUTPUT);
    pinMode(motorB, OUTPUT);
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
  }

  // Función para asignar valor a PWM de forma directa
  // Enciende un motor hasta llegar al máximo antes de encender el segundo
  void setPWM(int pwm)
  {
    if (pwm < MAX_PWM)
    {
      pwmA = pwm;
      pwmB = 0;
    }
    else
    {
      pwmA = MAX_PWM;
      pwmB = MAX_PWM - pwmA;
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