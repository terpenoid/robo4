#include <SoftwareSerial.h>
SoftwareSerial hc06(10, 11);

#include "parse_serial.h"

#include "leg.h"
Leg leg1(0, 0, 1, 2), leg2(1, 4, 5, 6), leg3(2, 8, 9, 10), leg4(3, 12, 13, 14);

#include "body.h"
Body body();

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



Stream &currentPort = hc06; // hc06/Serial


void loop() {

  parsing(currentPort); // функция парсинга
  
  if (recievedFlag) { // если получены данные
    
    recievedFlag = false;
    currentPort.print("[data]: ");
    for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива
      currentPort.print(intData[i]); currentPort.print(" ");
    }
    currentPort.println();

    if (intData[0] == 1) {
      currentPort.println("next PROG[" + String(intData[1]) + "]...");
      nextProgNum = intData[1];
      customParam[0] = intData[2];
      customParam[1] = intData[3];
      customParam[2] = intData[4];
      customParam[3] = intData[5];
      if (!progRun && progStep == 0) currentProgNum = intData[1];
      progRun = true;
    }

    if (intData[0] == 2 && intData[1] >= 0 && intData[1] < 100) {
      currentPort.println("set SPEED[" + String(intData[1]) + "]");
      leg1.setSpeed(intData[1]);
      leg2.setSpeed(intData[1]);
      leg3.setSpeed(intData[1]);
      leg4.setSpeed(intData[1]);
    }

    if (intData[0] == 3) {

      // zu
      if (intData[1] == 1) {
        if ((intData[2] < -20) && (intData[2] > zd)) {
          zu = intData[2];
          currentPort.println("set ZU[" + String(zu) + "]");
        }
      }

      // zd
      if (intData[1] == 2) {
        if ((intData[2] > -80) && (intData[2] < zu)) {
          zd = intData[2];
          currentPort.println("set ZD[" + String(zd) + "]");
        }
      }
      
    }

    

    ///////////////////////////////////////////////
    if (intData[0] == -1) {
      currentPort.println("STOP!");
      progRun = !progRun;
    }

    if (intData[0] == -2) {
      currentPort.println("RESET!");
      leg1.goToPos(0, 105, 80);
      leg2.goToPos(0, 105, 80);
      leg3.goToPos(0, 105, 80);
      leg4.goToPos(0, 105, 80);

      currentProgNum = nextProgNum = progStep = 0;
    }

    if (!currentProgNum) currentProgNum = nextProgNum;


  }

  doOneProgramStep();

}
