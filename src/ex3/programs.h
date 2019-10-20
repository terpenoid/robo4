// #include <QueueArray.h>

struct point {
  byte x;
  byte y;
  int z;
};

struct progStep {
  point l1;
  point l2;
  point l3;
  point l4;
};

//QueueArray <progStep> queue;
//
//void initQueue(Stream &port) {
//  queue.setPrinter (port);
//}







byte newProgStepPointer = 0;
byte currentProgStepPointer = 0;
progStep queue1[256];

//void removeIndex(byte index, byte length){
//    for(byte i = index; i < (length - 1); i++){
//      queue1[i] = queue1[i + 1];
//    }
//    queue1[length-1] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
//}

void addToQueue(progStep oneStep) {
  queue1[newProgStepPointer] = oneStep;
  newProgStepPointer++;
}

//progStep tmp;
progStep popFromQueue() {
//  tmp = queue1[0];
//  removeIndex(0, 100);
//  newProgStepPointer--;
  currentProgStepPointer++;
  return queue1[currentProgStepPointer-1];
}
