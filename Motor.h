#ifndef MOTOR_H
#define MOTOR_H

#define MAX_PWM 1023
class MotorManager{
    public:
    // pines
    int motorA;
    int motorB;
    // velocidades 
    int pwmA;
    int pwmB;

    MotorManager(int motorAPin, int motorBPin){
        motorA = motorAPin;
        motorB = motorBPin;
        pwmA = 0;
        pwmB = 0;
    }

    void begin(){
        pinMode(motorA, OUTPUT);
        pinMode(motorB, OUTPUT);
        analogWrite(motorA, 0);
        analogWrite(motorB, 0);
    }

    void setPWM(int pwm){
        if(pwm < MAX_PWM){ 
            pwmA = pwm;
        }
        else{
            pwmA = MAX_PWM;
            pwmB = MAX_PWM - pwmA;
    }}
}
#endif