#include "Grove_I2C_Motor_Driver.h"
#define I2C_ADDRESS 0x0f

void setup() {
  Motor.begin(I2C_ADDRESS);
}

void loop() {
  // Set speed of MOTOR1
  // Speeds are set as such: clockwise is positive, anticlockwise is negative
  // Speeds can be between -100 and 100
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 50);
  delay(2000);
  Motor.speed(MOTOR1, -50);
  delay(1000);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  delay(2000);

}
