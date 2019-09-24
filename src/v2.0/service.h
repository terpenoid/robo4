#include <FlexiTimer2.h>

// int correction[4][3]   = { {0, -9, 0}, {5, -5, -15}, {10, 0, 0}, {13, 0, -10} };



int servoStateNow[4][3] = { {0, 180, 90}, {0, 180, 90}, {0, 180, 90}, {0, 180, 90} };
int posStateNow[4][3]   = { {81, 0, -52}, {81, 0, -52}, {81, 0, -52}, {81, 0, -52} };

int servoStateExpect[4][3] = { {0, 180, 90}, {0, 180, 90}, {0, 180, 90}, {0, 180, 90} };
int posStateExpect[4][3]   = { {81, 0, -52}, {81, 0, -52}, {81, 0, -52}, {81, 0, -52} };

int servoSpeed[4][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };






//int getIndexOfMaximumValue(int* array, int size) {
//  int maxIndex = 0;
//  int max = array[maxIndex];
//  for (int i = 1; i < size; i++) {
//    if (max < array[i]) {
//      max = array[i];
//      maxIndex = i;
//    }
//  }
//  return maxIndex;
//}


boolean inMove = false;
boolean lastMove = false;
int prog = 0;



void setExpectPoint(int leg, Point point) {

  posStateExpect[leg][0] = point.x;
  posStateExpect[leg][1] = point.y;
  posStateExpect[leg][2] = point.z;

  Serial.println("----------------------------");
  Serial.println("set point");
  Serial.print("x:");
  Serial.print(point.x);
  Serial.print(" | y: ");
  Serial.print(point.y);
  Serial.print(" | z: ");
  Serial.println(point.z);
  

  //  LegState res = computeAngles(point);
  //
  //  servoStateExpect[leg][0] = res.alpha;
  //  servoStateExpect[leg][1] = res.beta;
  //  servoStateExpect[leg][2] = res.gamma;

  //  Serial.println("------------------");
  //  Serial.print("alpha, beta, gamma: ");
  //  Serial.print(res.alpha);
  //  Serial.print(", ");
  //  Serial.print(res.beta);
  //  Serial.print(", ");
  //  Serial.println(res.gamma);
  //  Serial.print("x, y, z: ");
  //  Serial.print(point.x);
  //  Serial.print(", ");
  //  Serial.print(point.y);
  //  Serial.print(", ");
  //  Serial.println(point.z);
  //  Serial.println("------------------");

}




void moveLeg(int leg, LegState nextState, Point nextPoint) {

  Serial.println("move:");

  float alpha, beta, gamma;

  if (leg == 0) {
    alpha = nextState.alpha + 90;
    beta = nextState.beta - 90 + 10; // 10
    gamma = nextState.gamma + 10;
  }

  if (leg == 1) {
    alpha = 90 - nextState.alpha;
    beta = 270 - nextState.beta - 5;
    gamma = 180 - nextState.gamma - 5;
  }

  if (leg == 2) {
    alpha = nextState.alpha + 90;
    beta = nextState.beta - 90;
    gamma = nextState.gamma;
  }

  if (leg == 3) {
    alpha = 90 - nextState.alpha;
    beta = 270 - nextState.beta;
    gamma = 180 - nextState.gamma;
  }
  

  

  Serial.print("a:");
  Serial.print(nextState.alpha);
  Serial.print(" | b: ");
  Serial.print(nextState.beta);
  Serial.print(" | g: ");
  Serial.println(nextState.gamma);

  pwm.setPWM(servoPin[leg][0], 0, angleToPulse(alpha));
  pwm.setPWM(servoPin[leg][1], 0, angleToPulse(beta));
  pwm.setPWM(servoPin[leg][2], 0, angleToPulse(gamma));

  posStateNow[leg][0] = nextState.alpha;
  posStateNow[leg][1] = nextState.beta;
  posStateNow[leg][2] = nextState.gamma;

  posStateNow[leg][0] = nextPoint.x;
  posStateNow[leg][1] = nextPoint.y;
  posStateNow[leg][2] = nextPoint.z;

}






/**
   Main function - compare `now` and `expected` and make moves between they
*/
void servoService(void)
{
  sei();
//  Serial.println("-------------------------------------------------");
//  Serial.println("servoService tick");

  int leg = 0;
  int stepX = 10;

  float diff = sqrt( sq(posStateExpect[leg][0] - posStateNow[leg][0]) + sq(posStateExpect[leg][1] - posStateNow[leg][1]) + sq(posStateExpect[leg][2] - posStateNow[leg][2]) );

  if (diff > 0.5) {

    Serial.println("diff");

    Point nextPoint;
    if (diff > stepX) {
      nextPoint = computeMiddlePoint({x: posStateNow[leg][0], y: posStateNow[leg][1], z: posStateNow[leg][2]}, {x: posStateExpect[leg][0], y: posStateExpect[leg][1], z: posStateExpect[leg][2]}, stepX);
      Serial.println("computeMiddlePoint");

      lastMove = false;
      
    } else {
      nextPoint = {x: posStateExpect[leg][0], y: posStateExpect[leg][1], z: posStateExpect[leg][2]};
      Serial.println("lastPoint");

      lastMove = true;
      
    }

    LegState nextState = computeAngles(nextPoint);
    servoStateExpect[leg][0] = nextState.alpha;
    servoStateExpect[leg][1] = nextState.beta;
    servoStateExpect[leg][2] = nextState.gamma;

    if (servoStateNow[leg][0] != servoStateExpect[leg][0] ||  servoStateNow[leg][1] != servoStateExpect[leg][1] ||  servoStateNow[leg][2] != servoStateExpect[leg][2]) {
      moveLeg(leg, nextState, nextPoint);
      moveLeg(1, nextState, nextPoint);
      moveLeg(2, nextState, nextPoint);
      moveLeg(3, nextState, nextPoint);      

      inMove = true;

    }

  } else {

//    Serial.println("leg on position");
    inMove = false;
    
  }





}


/**
   Initialisation of timer-service (for `setup()` function)
*/
void serviceInit() {

  //start servo service
  FlexiTimer2::set(20, servoService);
  FlexiTimer2::start();
  Serial.println("Servo service started");

}
