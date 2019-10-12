#include <SoftwareSerial.h>
SoftwareSerial hc06(10, 11);

#include "parse_serial.h"

#include "leg.h"

Leg leg1(0, 0, 1, 2), leg2(1, 4, 5, 6), leg3(2, 8, 9, 10), leg4(3, 12, 13, 14);

#include "programs.h"


void setup() {
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println();

  
  hc06.begin(9600);
  hc06.println("Hello from Arduino");
  
  servosInit();

  //  for (int i = 0; i < 4; i++) {
  //    for (int j = 0; j < 3; j++) {
  //      pwm.setPWM(servoPin[i][j], 0, angleToPulse(90));
  //    }
  //  }

  pwm.setPWM(leg1.getCoxaPin(), 0, angleToPulse(180));
  pwm.setPWM(leg1.getFemurPin(), 0, angleToPulse(100));
  pwm.setPWM(leg1.getTibiaPin(), 0, angleToPulse(160));

  pwm.setPWM(leg2.getCoxaPin(), 0, angleToPulse(0));
  pwm.setPWM(leg2.getFemurPin(), 0, angleToPulse(80));
  pwm.setPWM(leg2.getTibiaPin(), 0, angleToPulse(20));

  pwm.setPWM(leg3.getCoxaPin(), 0, angleToPulse(180));
  pwm.setPWM(leg3.getFemurPin(), 0, angleToPulse(100));
  pwm.setPWM(leg3.getTibiaPin(), 0, angleToPulse(160));

  pwm.setPWM(leg4.getCoxaPin(), 0, angleToPulse(0));
  pwm.setPWM(leg4.getFemurPin(), 0, angleToPulse(80));
  pwm.setPWM(leg4.getTibiaPin(), 0, angleToPulse(20));


  leg1.goToPos(0, 80, 0);
  leg2.goToPos(0, 80, 0);
  leg3.goToPos(0, 80, 0);
  leg4.goToPos(0, 80, 0);

}


int progNum = 0;

void loop() {


  parsing(hc06);       // функция парсинга
  if (recievedFlag) {                           // если получены данные
    recievedFlag = false;
    Serial.println("[data]:");
    for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива
      Serial.print(intData[i]); Serial.print(" ");
    }
    Serial.println();

    hc06.println("doing PROG[" + String(intData[0]) + "]...");

    if (intData[0] == 1) {
      progNum = 1;
      progStep = 0;
      leg1.setSpeed(10);
      leg2.setSpeed(10);
      leg3.setSpeed(10);
      leg4.setSpeed(10);
      progRun = true;
    }

    if (intData[0] == 2) {
      progNum = 2;
      progStep = 0;
      leg1.setSpeed(20);
      leg2.setSpeed(20);
      leg3.setSpeed(20);
      leg4.setSpeed(20);
      progRun = true;
    }

    if (intData[0] == -1) {
      progNum = 0;
      progStep = 0;
      progRun = false;
    }


  }


  switch (progNum) {
    case 1: doOneProgramStep(programRunForward); break;
    case 2: doOneProgramStep(programRunUpDown); break;
  }


}
