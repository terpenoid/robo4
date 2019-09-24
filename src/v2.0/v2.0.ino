// http://robojax.com/learn/arduino/?vid=robojax-PCA6985
// https://habr.com/ru/post/156579/
// https://drive.google.com/drive/folders/1mvT-h3ZZSBYNPqT6P2pmCaelV2xFY8w2
// https://www.instructables.com/id/DIY-Spider-RobotQuad-robot-Quadruped/
// https://www.youtube.com/watch?v=fiQbOWvqVco

#include "parse_serial.h"

#include "servo.h"
#include "leg_calc.h"
#include "service.h"

void setup() {
  Serial.begin(9600);
  servosInit();
  serviceInit();
  yield();
}

void loop() {

  parsing();       // функция парсинга
  if (recievedFlag) {                           // если получены данные
    recievedFlag = false;

//    for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива
//      Serial.print(intData[i]); Serial.print(" ");
//    }


//    pwm.setPWM(servoPin[1][1], 0, angleToPulse(intData[0]));


    setExpectPoint(0, {x: intData[0], y: intData[1], z: intData[2]});

    
//    LegState p = computeAngles({intData[0], intData[1], intData[2]});
//
//    float alpha = p.alpha + 90;
//    float beta = p.beta - 90 + 10; // 10
//    float gamma = p.gamma;
//
//    moveToAngle(0, alpha);
//    moveToAngle(1, beta);
//    moveToAngle(2, gamma);

  }





  if (!inMove) {

    switch (prog) {
      case 0:
        setExpectPoint(0, {x: 50, y: 50, z: -15});
      break;
      case 1:
        setExpectPoint(0, {x: 50, y: 50, z: -40});
      break;
      case 2:
        setExpectPoint(0, {x: 50, y: 50, z: -15});
      break;
      case 3:
        setExpectPoint(0, {x: 50, y: 50, z: -40});
      break;
      case 4:
        setExpectPoint(0, {x: 50, y: 50, z: -15});
      break;
      case 5:
        setExpectPoint(0, {x: 100, y: 100, z: 40});
      break;
      case 6:
        setExpectPoint(0, {x: 100, y: 100, z: 80});
      break;
      case 7:
        setExpectPoint(0, {x: 100, y: 100, z: 40});
      break;
      case 8:
        setExpectPoint(0, {x: 100, y: 100, z: 80});
      break;
    }
    
    lastMove = false;
    prog++;
    if (prog>8) prog = 0;
    delay(1000);
  }


  

}
