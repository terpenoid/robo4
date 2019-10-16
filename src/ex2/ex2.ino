#include <SoftwareSerial.h>
SoftwareSerial hc06(10, 11);

#include "parse_serial.h"

#include "leg.h"
Leg leg1(0, 0, 1, 2), leg2(1, 4, 5, 6), leg3(2, 8, 9, 10), leg4(3, 12, 13, 14);

//#include "body.h"
//Body body();

#include "programs.h"


void setup() {
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println();


  hc06.begin(9600);
  hc06.println("Hello from Arduino");

  servosInit();

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




void loop() {


//  parsing(hc06);       // функция парсинга
    parsing(Serial);       // функция парсинга
  if (recievedFlag) {                           // если получены данные
    recievedFlag = false;
    Serial.println("[data]:");
    for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива
      Serial.print(intData[i]); Serial.print(" ");
    }
    Serial.println();

    if (intData[0] == 1) {
      
      leg1.goToPos(0, 60, -50);
      leg2.goToPos(50, 60, -50);
      leg3.goToPos(50, 60, -50);
      leg4.goToPos(0, 60, -50);

      progRun = true;
    }


    if (intData[0] == 2) {

      int Xc, Yc;

      switch (intData[1]) {
        case 1:

        Serial.println("-----------------------------------");
        Serial.println("Current:");
        Serial.println("L2: " + String(leg2.getX()) + "/" + String(leg2.getY()) + " (" + String(leg2.getAbsX()) + "/" + String(leg2.getAbsY()) + ")");
        Serial.println("L3: " + String(leg3.getX()) + "/" + String(leg3.getY()) + " (" + String(leg3.getAbsX()) + "/" + String(leg3.getAbsY()) + ")");
        Serial.println("L4: " + String(leg4.getX()) + "/" + String(leg4.getY()) + " (" + String(leg4.getAbsX()) + "/" + String(leg4.getAbsY()) + ")");
        
        Xc = (leg2.getAbsX() + leg3.getAbsX() + leg4.getAbsX())/3;
        Yc = (leg2.getAbsY() + leg3.getAbsY() + leg4.getAbsY())/3;
        Serial.println("C: " + String(Xc) + "/" + String(Yc));

        break;
        case 2:
          Xc = (leg1.getAbsX() + leg3.getAbsX() + leg4.getAbsX())/3;
          Yc = (leg1.getAbsY() + leg3.getAbsY() + leg4.getAbsY())/3;
        break;
        case 3:
          Xc = (leg1.getAbsX() + leg1.getAbsX() + leg4.getAbsX())/3;
          Yc = (leg1.getAbsY() + leg1.getAbsY() + leg4.getAbsY())/3;
        break;
        case 4:
          Xc = (leg1.getAbsX() + leg2.getAbsX() + leg3.getAbsX())/3;
          Yc = (leg1.getAbsY() + leg2.getAbsY() + leg3.getAbsY())/3;
        break;
      }


      int NaX2, NaY2, NaX3, NaY3, NaX4, NaY4;
      int nX2, nY2, nX3, nY3, nX4, nY4;

      NaX2 = Xc; NaY2 = Yc;
      NaX3 = Xc; NaY3 = Yc;
      NaX4 = Xc; NaY4 = Yc;

      nX2 = NaX2 - 35; nY2 = NaY2 - 35;
      nX3 = NaX3 - 35; nY3 = NaY3 - 35;
      nX4 = NaX4 - 35; nY4 = NaY4 - 35;
      

//      leg1.goToPos(leg1.getX() - Xc, leg1.getY() - Yc, leg1.getZ());
//      leg2.goToPos(leg2.getX() - Xc, leg2.getY() + Yc, leg2.getZ());
//      leg3.goToPos(leg3.getX() + Xc, leg3.getY() + Yc, leg3.getZ());
//      leg4.goToPos(leg4.getX() + Xc, leg4.getY() - Yc, leg4.getZ());
        
      progRun = true;
    }


    if (intData[0] == 8) {
      progRun = false;
      int pins[4][3] = {{0, 1, 2}, {4, 5, 6}, {8, 9, 10}, {12, 13, 14}};
      pwm.setPWM(pins[intData[1]][intData[2]], 0, angleToPulse(intData[3]));
    }

    if (intData[0] == 9) {      
      leg1.goToPos(intData[1], intData[2], intData[3]);
      leg2.goToPos(intData[1], intData[2], intData[3]);
      leg3.goToPos(intData[1], intData[2], intData[3]);
      leg4.goToPos(intData[1], intData[2], intData[3]);
      progRun = true;
    }
    
    if (intData[0] == -1) {      
      leg1.goToPos(0, 80, 0);
      leg2.goToPos(0, 80, 0);
      leg3.goToPos(0, 80, 0);
      leg4.goToPos(0, 80, 0);
      progRun = true;
    }

  }

  doOneProgramStep();

}
