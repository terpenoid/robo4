#include <QueueArray.h> // https://playground.arduino.cc/Code/QueueArray/

typedef struct progStep { int coords[4][3]; } progStep;
QueueArray <progStep> queue;



int y = 60;
int s = 50; // step
int s_ = 70; // betw 2 legs
int zd = -50;
int zu = -20;


int updateInterval = 50; // prodram steps update
unsigned long lastUpdate;



boolean progRun = true;



void doOneProgramStep() {

  if (progRun && ((millis() - lastUpdate) > updateInterval) && (!leg1.inMove() && !leg2.inMove() && !leg3.inMove() && !leg4.inMove())) {
    lastUpdate = millis();

    
  
  }

  leg1.update();
  leg2.update();
  leg3.update();
  leg4.update();

}
