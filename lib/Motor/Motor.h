// Adafruit Motor shield library
// for ESP8266 Wemos D1 R2

#ifndef _AFMotor_h_
#define _AFMotor_h_

#include <inttypes.h>
#define MOTORDEBUG 1
#include "stdlib_noniso.h"
#define MICROSTEPS 8
#define DC_MOTOR_PWM_RATE 5
#define STEPPER1_PWM_RATE 5
#define STEPPER2_PWM_RATE 5
// logic pins for "PWM"
#define MOTOR1_EN GPIO_NUM_11
#define MOTOR2_EN GPIO_NUM_3
#define MOTOR3_EN GPIO_NUM_6
#define MOTOR4_EN GPIO_NUM_5

// Bit positions in the 74HCT595 shift register output
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR3_A 5
#define MOTOR3_B 7
#define MOTOR4_A 0
#define MOTOR4_B 6

// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// Constants that the user passes in to the stepper calls
#define SINGLE 1
#define DOUBLE 2
#define INTERLEAVE 3
#define MICROSTEP 4

// Arduino pin names for interface to 74HCT595 latch
#define MOTORLATCH GPIO_NUM_12
#define MOTORCLK GPIO_NUM_4
#define MOTORENABLE GPIO_NUM_7 // used to be 7
#define MOTORDATA GPIO_NUM_8   // used to be 8

class AFMotorController
{
public:
  AFMotorController(void);
  void enable(void);
  friend class AF_DCMotor;
  void latch_tx(void);
  uint8_t TimerInitalized;
};

class AF_DCMotor
{
public:
  AF_DCMotor(uint8_t motornum, uint8_t freq = DC_MOTOR_PWM_RATE);
  void run(uint8_t);
  void setSpeed(uint8_t);

private:
  uint8_t motornum, pwmfreq;
};

#endif