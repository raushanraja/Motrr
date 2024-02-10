#include <Arduino.h>
#include <Motor.h>

AF_DCMotor motor(1);

void setup()
{
  Serial.begin(9600);
  Serial.println("Motor test!");

  motor.setSpeed(200);
  motor.run(RELEASE);
}
void loop()
{
  uint8_t i;

  Serial.println("tick");
  motor.run(FORWARD);

  for (i = 0; i < 255; i++)
  {
    motor.setSpeed(i);
    delay(10);
  }

  for (i = 255; i != 0; i--)
  {
    motor.setSpeed(i);
    delay(10);
  }

  Serial.println("tock");
  motor.run(BACKWARD);

  for (i = 0; i < 255; i++)
  {
    motor.setSpeed(i);
    delay(10);
  }

  for (i = 255; i != 0; i--)
  {
    motor.setSpeed(i);
    delay(10);
  }

  Serial.println("tech");
  motor.run(RELEASE);
  delay(1000);
}
