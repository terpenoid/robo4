#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

/**
   Servos PINs on ServoShield
   Ex: array[i][j], where
   i = leg (FL, FR, BL, BR)
   j = servo (coxa, femur, tibia)
*/
const int servoPin[5][3] = { {0, 1, 2}, {4, 5, 6}, {8, 9, 10}, {12, 13, 14} };


/**
   Map angle of 0 to 180 to Servo min and Servo max
*/
int angleToPulse(int angle) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

/**
   Initialisation for ServoShield (for `setup()` function)
*/
void servosInit() {
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}
