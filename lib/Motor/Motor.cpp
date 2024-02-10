#if (ARDUINO >= 100)
#include "Arduino.h"
#endif

#include "Motor.h"

static uint8_t latch_state;

#if (MICROSTEPS == 8)
uint8_t microstepcurve[] = {0, 50, 98, 142, 180, 212, 236, 250, 255};
#elif (MICROSTEPS == 16)
uint8_t microstepcurve[] = {0, 25, 50, 74, 98, 120, 141, 162, 180, 197, 212, 225, 236, 244, 250, 253, 255};
#endif

AFMotorController::AFMotorController(void) {}

void AFMotorController::enable(void)
{
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);

    latch_state = 0;

    latch_tx();

    digitalWrite(MOTORENABLE, LOW);
}

void AFMotorController::latch_tx(void)
{
    uint8_t i;
    digitalWrite(MOTORLATCH, LOW);
    digitalWrite(MOTORDATA, LOW);

    for (i = 0; i < 8; i++)
    {
        digitalWrite(MOTORCLK, LOW);
        if (latch_state & _BV(7 - i))
        {
            digitalWrite(MOTORDATA, HIGH);
        }
        else
        {
            digitalWrite(MOTORDATA, LOW);
        }
        digitalWrite(MOTORCLK, HIGH);
    }
    digitalWrite(MOTORLATCH, HIGH);
}

static AFMotorController MC;

inline void initPWM1(uint8_t freq)
{
    pinMode(MOTOR1_EN, OUTPUT);
}

inline void setPWM1(uint8_t s)
{
    analogWrite(MOTOR1_EN, s);
}

inline void initPWM2(uint8_t freq)
{
    pinMode(MOTOR2_EN, OUTPUT);
}

inline void setPWM2(uint8_t s)
{
    analogWrite(MOTOR2_EN, s);
}

inline void initPWM3(uint8_t freq)
{
    pinMode(MOTOR3_EN, OUTPUT);
}

inline void setPWM3(uint8_t s)
{
    analogWrite(MOTOR3_EN, s);
}

inline void initPWM4(uint8_t freq)
{
    pinMode(MOTOR4_EN, OUTPUT);
}

inline void setPWM4(uint8_t s)
{
    analogWrite(MOTOR4_EN, s);
}

AF_DCMotor::AF_DCMotor(uint8_t num, uint8_t freq)
{
    motornum = num;
    pwmfreq = freq;

    MC.enable();

    switch (motornum)
    {
    case 1:
        latch_state = ~_BV(MOTOR1_A) & ~_BV(MOTOR1_B);
        MC.latch_tx();
        initPWM1(pwmfreq);
        break;
    case 2:
        latch_state = ~_BV(MOTOR2_A) & ~_BV(MOTOR2_B);
        MC.latch_tx();
        initPWM2(pwmfreq);
        break;
    case 3:
        latch_state = ~_BV(MOTOR3_A) & ~_BV(MOTOR3_B);
        MC.latch_tx();
        initPWM3(pwmfreq);
        break;
    case 4:
        latch_state = ~_BV(MOTOR4_A) & ~_BV(MOTOR4_B);
        MC.latch_tx();
        initPWM4(pwmfreq);
        break;
    }
}

void AF_DCMotor::run(uint8_t cmd)
{
    uint8_t a, b;

    switch (motornum)
    {
    case 1:
        a = MOTOR1_A;
        b = MOTOR1_B;
        break;
    case 2:
        a = MOTOR2_A;
        b = MOTOR2_B;
        break;
    case 3:
        a = MOTOR3_A;
        b = MOTOR3_B;
        break;
    case 4:
        a = MOTOR4_A;
        b = MOTOR4_B;
        break;
    }

    switch (cmd)
    {
    case FORWARD:
        latch_state |= _BV(a);
        latch_state &= ~_BV(b);
        MC.latch_tx();
        break;
    case BACKWARD:
        latch_state &= ~_BV(a);
        latch_state |= _BV(b);
        MC.latch_tx();
        break;
    case RELEASE:
        latch_state &= ~_BV(a);
        latch_state &= ~_BV(b);
        MC.latch_tx();
        break;
    }
}

// Complete the function for the speed
void AF_DCMotor::setSpeed(uint8_t speed)
{
    switch (motornum)
    {
    case 1:
        setPWM1(speed);
        break;
    case 2:
        setPWM2(speed);
        break;
    case 3:
        setPWM3(speed);
        break;
    case 4:
        setPWM4(speed);
        break;
    }
}
