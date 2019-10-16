#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

////////////////////////////////////////////////////////////////////////////////

void servosInit() {
  // Serial.println("16 channel Servo init!");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}
int angleToPulse(int angle) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

////////////////////////////////////////////////////////////////////////////////



int anglesFix[4][3] = {{0, +20, +10}, {+12, +5, +15}, {0, +7, +5}, {+13, +5, +10}};



class Leg {

    int legNum = 0; // 0-3

    // dimensions
    int bodyWidth = 70;
    int bodyHeight = 70;
    int coxaZShift = 26;
    int coxaLength = 27;
    int femurLength = 54;
    int tibiaLength = 78;

    // servo pins
    int coxaPin, femurPin, tibiaPin;

    // servo positions
    float coxaPosNow, femurPosNow, tibiaPosNow;
    float coxaPosExpect, femurPosExpect, tibiaPosExpect;

    //last leg XYZ position
    int legX, legY, legZ;

    // servo speed
    float speedC, speedF, speedT;

    int updateSpeed = 50;
    unsigned long lastUpdate;

  public:
    Leg(){}
    Leg(int leg, int coxa, int femur, int tibia)
    {
      legNum = leg;

      coxaPin = coxa;
      femurPin = femur;
      tibiaPin = tibia;

      coxaPosExpect = coxaPosNow = 90;
      femurPosExpect = femurPosNow = 180;
      tibiaPosExpect = tibiaPosNow = 90;

      speedC = speedF = speedT = 1;

    }

    void setSpeed(int s) {
      updateSpeed = s;
    }

    int getSpeed() {
      return updateSpeed;
    }

    int getCoxaPin() {
      return coxaPin;
    }
    int getFemurPin() {
      return femurPin;
    }
    int getTibiaPin() {
      return tibiaPin;
    }


    int getX() {
      return legX;
    }
    int getY() {
      return legY;
    }
    int getZ() {
      return legZ;
    }

    int getAbsX() {
      switch (legNum) {
        case 0: return legX + bodyWidth/2; break;
        case 1: return legX + bodyWidth/2; break;
        case 2: return -legX - bodyWidth/2; break;
        case 3: return -legX - bodyWidth/2; break;
      }
    }
    int getAbsY() {
      switch (legNum) {
        case 0: return legY + bodyHeight/2; break;
        case 1: return -legY - bodyHeight/2; break;
        case 2: return -legY - bodyHeight/2; break;
        case 3: return legY + bodyHeight/2; break;
      }
    }


    

    int getRealAngleForServo (int servo, int angle) {

      switch (legNum) {
        case 0:
          switch (servo) {
            case 0: angle = angle + 90; break;
            case 1: angle = angle - 90; break;
            case 2: angle = angle; break;
          }
          break;
        case 1:
          switch (servo) {
            case 0: angle = 90 - angle; break;
            case 1: angle = 270 - angle; break;
            case 2: angle = 180 - angle; break;
          }
          break;
        case 2:
          switch (servo) {
            case 0: angle = angle + 90; break;
            case 1: angle = angle - 90; break;
            case 2: angle = angle; break;
          }
          break;
        case 3:
          switch (servo) {
            case 0: angle = 90 - angle; break;
            case 1: angle = 270 - angle; break;
            case 2: angle = 180 - angle; break;
          }
          break;
      }

      return angle + anglesFix[legNum][servo];
    }

    void computeExpectPos (float expectedX, float expectedY, float expectedZ) {

      // @TODO: fix possible errors for coords out from possible
      //  if (expectedX < 0) expectedX = 0;
      //  if (expectedY < 0) expectedY = 0;
      //  if (expectedZ < -50) expectedZ = -50;
      // and so on

      float alphaR, alphaD;
      float betaR, betaD;
      float gammaR, gammaD;

      float Xb, Yb, Xd, Yd, Xc, Yc;
      float AD1, AC2, BD2;

      float x1, y1, r1, x2, y2, r2;
      float d, b, a, h, x, y, x3, y3, x4, y4;

      float A, B, C;


      ////////////////////////////////
      // on Grid1:
      //----------------------

      // alpha
      if (expectedX != 0) {
        // Serial.println(expectedY);
        // Serial.println(expectedX);
        float rrr = expectedY / expectedX;
        // Serial.println(expectedY / expectedX);
        // Serial.println(rrr);
        alphaR = atan(expectedY / expectedX);
      } else {
        alphaR = PI / 2;
        // Serial.println(PI);
      }
      alphaD = alphaR * 180 / PI;
      // Serial.print("alpha: "); // Serial.print(alphaD); // Serial.print("("); // Serial.print(alphaR); // Serial.println(")");

      // coxa B(X/Y)
      Xb = cos(alphaR) * coxaLength;
      Yb = sin(alphaR) * coxaLength;

      // AD (on grid 1)
      AD1 = sqrt(sq(expectedX) + sq(expectedY));
      //// Serial.print("AD1: "); // Serial.println(AD1);

      ////////////////////////////////
      // on Grid2:
      //----------------------

      Xb = coxaLength;
      Yb = coxaZShift;

      Xd = AD1;
      Yd = expectedZ;

      //////////////////////////////
      // intersections
      // http://www.cyberforum.ru/pascal/thread106540.html
      // https://planetcalc.ru/8098/?license=1
      x1 = Xb;
      y1 = Yb;
      r1 = femurLength;

      x2 = Xd;
      y2 = Yd;
      r2 = tibiaLength;

      d = sqrt(sq(x1 - x2) + sq(y1 - y2));
      //// Serial.print("D: "); // Serial.println(d);

      b = (sq(r2) - sq(r1) + sq(d)) / (2 * d);
      a = d - b;
      h = sqrt(sq(r2) - sq(b));
      x = x1 + (x2 - x1) / (d / a);
      y = y1 + (y2 - y1) / (d / a);
      x3 = x - (y - y2) * h / b;
      y3 = y + (x - x2) * h / b;
      x4 = x + (y - y2) * h / b;
      y4 = y - (x - x2) * h / b;

      //// Serial.print("X1: "); // Serial.print(x3); // Serial.print("\nY1: "); // Serial.println(y3);
      //// Serial.print("X2: "); // Serial.print(x4); // Serial.print("\nY2: "); // Serial.print(y4);

      // C (on grid 2)
      //  if (y3 > y4) {
      //    Xc = x3;
      //    Yc = y3;
      //  } else {
      //    Xc = x4;
      //    Yc = y4;
      //  }

      Xc = x4;
      Yc = y4;

      //      // Serial.print("Xc: "); // Serial.print(Xc); // Serial.print("\nYc: "); // Serial.println(Yc);
      ///////////////


      // AC (on grid 2)
      AC2 = sqrt(sq(Xc) + sq(Yc - coxaZShift));
      //// Serial.print("AC2: "); // Serial.println(AC2);


      // BD (on grid 2)
      BD2 = sqrt(sq(Xd - Xb) + sq(Yd - Yb));
      //// Serial.print("BD2: "); // Serial.println(BD2);

      // https://www.calc.ru/raschet-treugolnika.html

      // gamma
      A = femurLength;
      B = tibiaLength;
      C = BD2;
      //// Serial.print("A: "); // Serial.print(A); // Serial.print("\nB: "); // Serial.print(B); // Serial.print("\nC: "); // Serial.println(C);
      gammaR = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B));
      gammaD = gammaR * 180 / PI;
      // Serial.print("gamma: "); // Serial.print(gammaD); // Serial.print("("); // Serial.print(gammaR); // Serial.println(")");


      // beta
      A = femurLength;
      B = coxaLength;
      C = AC2;
      //// Serial.print("A: "); // Serial.print(A); // Serial.print("\nB: "); // Serial.print(B); // Serial.print("\nC: "); // Serial.println(C);
      betaR = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B));
      betaD = betaR * 180 / PI;
      // Serial.print("beta: "); // Serial.print(betaD); // Serial.print("("); // Serial.print(betaR); // Serial.println(")");

      // fix for "beta > 180"
      if (Yc < Yb) {
        // Serial.println("fix beta");
        betaD = 360 - betaD;
        // Serial.print("beta: "); // Serial.println(betaD);
      }


      //      result.alpha = alphaD;
      //      result.beta = betaD;
      //      result.gamma = gammaD;

      coxaPosExpect = round(alphaD);
      femurPosExpect = round(betaD);
      tibiaPosExpect = round(gammaD);

    }

    void moveServo (int servo, int pin, int angle) {
      int real = getRealAngleForServo(servo, angle);
      pwm.setPWM(pin, 0, angleToPulse(real));
    }


    // main method for moving one leg to XYZ
    void goToPos (int expectedX, int expectedY, int expectedZ) {

      computeExpectPos (expectedX, expectedY, expectedZ);

      legX = expectedX;
      legY = expectedY;
      legZ = expectedZ;

      float difC, difF, difT;

      difC = abs(coxaPosExpect - coxaPosNow);
      difF = abs(femurPosExpect - femurPosNow);
      difT = abs(tibiaPosExpect - tibiaPosNow);

      float maxDif = max(difC, max(difF, difT));

      speedC = (difC / maxDif);
      speedF = (difF / maxDif);
      speedT = (difT / maxDif);

    }

    void update()
    {
      if ((millis() - lastUpdate) > updateSpeed)
      {

        lastUpdate = millis();

        int difC, difF, difT;

        difC = coxaPosExpect - coxaPosNow;
        difF = femurPosExpect - femurPosNow;
        difT = tibiaPosExpect - tibiaPosNow;

        if (difC) {
          coxaPosNow = (difC > 0) ? coxaPosNow + speedC : coxaPosNow - speedC;
          moveServo(0, coxaPin, round(coxaPosNow));
        }

        if (difF) {
          femurPosNow = (difF > 0) ? femurPosNow + speedF : femurPosNow - speedF;
          moveServo(1, femurPin, round(femurPosNow));
        }

        if (difT) {
          tibiaPosNow = (difT > 0) ? tibiaPosNow + speedT : tibiaPosNow - speedT;
          moveServo(2, tibiaPin, round(tibiaPosNow));
        }

//        // check position
//        if (!difC && !difF && !difT) {
////          Serial.println("current position of leg[" + String(legNum) + "]:");
////          Serial.println(String(legX) + ", " + String(legY) + ", " + String(legZ) + ", ");
////          Serial.println("diff: " + String(difC) + " - " + String(difF) + " - " + String(difT));
//        }
        
      }
      
    }

    boolean inMove() {

      int difC, difF, difT;

      difC = coxaPosExpect - coxaPosNow;
      difF = femurPosExpect - femurPosNow;
      difT = tibiaPosExpect - tibiaPosNow;

      return (abs(difC) > 0.1 || abs(difF) > 0.1 || abs(difT) > 0.1);

    }

};
