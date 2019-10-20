#include <SoftwareSerial.h>
SoftwareSerial hc06(10, 11);

#include "parse_serial.h"
#include "programs.h"


#include "leg.h"
Leg leg1(0, 0, 1, 2), leg2(1, 4, 5, 6), leg3(2, 8, 9, 10), leg4(3, 12, 13, 14);



void setup() {


  
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println();



//  initQueue(Serial);


  hc06.begin(9600);

  


  
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




int updateInterval = 50; // prodram steps update
unsigned long lastUpdate;

boolean progRun = false;


progStep tmpStep;


void loop() {


//  parsing(hc06);
    parsing(Serial);
    
  if (recievedFlag) { // если получены данные
    
    
    recievedFlag = false;
    Serial.println("[data]:"); // выводим элементы массива
    for (byte i = 0; i < PARSE_AMOUNT; i++) {
      Serial.print(intData[i]); Serial.print(" ");
    }
    Serial.println();
    

    if (intData[0] == 1) {
      
//      queue.push({{60, 60, 0}, {60, 60, 0}, {60, 60, 0}, {60, 60, 0}});
//      queue.push({{60, 60, -70}, {60, 60, -70}, {60, 60, -70}, {60, 60, -70}});
//      queue.push({{60, 60, 0}, {60, 60, 0}, {60, 60, 0}, {60, 60, 0}});
//      queue.push({{60, 60, -70}, {60, 60, -70}, {60, 60, -70}, {60, 60, -70}});
//      queue.push({{60, 60, 0}, {60, 60, 0}, {60, 60, 0}, {60, 60, 0}});


      addToQueue({{60, 60, 0}, {60, 60, 0}, {60, 60, 0}, {60, 60, 0}});
      addToQueue({{60, 60, -70}, {60, 60, -70}, {60, 60, -70}, {60, 60, -70}});
      addToQueue({{60, 60, 0}, {60, 60, 0}, {60, 60, 0}, {60, 60, 0}});
      addToQueue({{60, 60, -70}, {60, 60, -70}, {60, 60, -70}, {60, 60, -70}});
      addToQueue({{60, 60, 0}, {60, 60, 0}, {60, 60, 0}, {60, 60, 0}});

      


      progRun = true;
      
    }
    
    if (intData[0] == -1) {      
      progRun = false;
    }

  }




  if (progRun && ((millis() - lastUpdate) > updateInterval) && (!leg1.inMove() && !leg2.inMove() && !leg3.inMove() && !leg4.inMove())) {
    lastUpdate = millis();

    Serial.println("end of step");

//    if(!queue.isEmpty ()) {
//      
//      tmpStep = queue.pop();
//      Serial.print("{ ");
//      Serial.print("{ " + String(tmpStep.l1.x) + ", " + String(tmpStep.l1.y) + ", " + String(tmpStep.l1.z) + " }, ");
//      Serial.print("{ " + String(tmpStep.l2.x) + ", " + String(tmpStep.l2.y) + ", " + String(tmpStep.l2.z) + " }, ");
//      Serial.print("{ " + String(tmpStep.l3.x) + ", " + String(tmpStep.l3.y) + ", " + String(tmpStep.l3.z) + " }, ");
//      Serial.print("{ " + String(tmpStep.l4.x) + ", " + String(tmpStep.l4.y) + ", " + String(tmpStep.l4.z) + " } ");
//      Serial.println("}");
//
//      leg1.goToPos(tmpStep.l1.x, tmpStep.l1.y, tmpStep.l4.z);
//      leg2.goToPos(tmpStep.l2.x, tmpStep.l2.y, tmpStep.l2.z);
//      leg3.goToPos(tmpStep.l3.x, tmpStep.l3.y, tmpStep.l3.z);
//      leg4.goToPos(tmpStep.l4.x, tmpStep.l4.y, tmpStep.l4.z);
//      
//      
//    } else {
//
//      Serial.println("queue is empty");
//      progRun = false;
//      
//    }

      if (newProgStepPointer > 0) {

        tmpStep = popFromQueue();
        Serial.print("{ ");
        Serial.print("{ " + String(tmpStep.l1.x) + ", " + String(tmpStep.l1.y) + ", " + String(tmpStep.l1.z) + " }, ");
        Serial.print("{ " + String(tmpStep.l2.x) + ", " + String(tmpStep.l2.y) + ", " + String(tmpStep.l2.z) + " }, ");
        Serial.print("{ " + String(tmpStep.l3.x) + ", " + String(tmpStep.l3.y) + ", " + String(tmpStep.l3.z) + " }, ");
        Serial.print("{ " + String(tmpStep.l4.x) + ", " + String(tmpStep.l4.y) + ", " + String(tmpStep.l4.z) + " } ");
        Serial.println("}");
  
        leg1.goToPos(tmpStep.l1.x, tmpStep.l1.y, tmpStep.l4.z);
        leg2.goToPos(tmpStep.l2.x, tmpStep.l2.y, tmpStep.l2.z);
        leg3.goToPos(tmpStep.l3.x, tmpStep.l3.y, tmpStep.l3.z);
        leg4.goToPos(tmpStep.l4.x, tmpStep.l4.y, tmpStep.l4.z);
        
      } else {
        Serial.println("queue is empty");
        progRun = false;
      }
  
   
  }
  

  leg1.update();
  leg2.update();
  leg3.update();
  leg4.update();

}
