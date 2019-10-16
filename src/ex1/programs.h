int y = 60;
int s = 50; // step
int s_ = 70; // betw 2 legs
int zd = -50;
int zu = -20;


int customParam[4] = {0, 0, 0, 0};


int updateInterval = 50;
unsigned long lastUpdate;

int currentProgNum = 0;
int nextProgNum = 0;

int progRun = false;
int progStep = 0;

int storedSpeed = 10;


int standPosition = 0; // 0=left; 1=right


void programReadyPosition();
void programRunForward(); // declaration of function who will be sendet as argument
void programTurnRight();
void programTurnLeft();
void programHandShake();

void programStepInL();
void programStepInR();
void programStepOut();
void programUpDown2();
void programRolling();
void programShift();
void programSway();



void doOneProgramStep() {

  if (progRun && ((millis() - lastUpdate) > updateInterval) && (!leg1.inMove() && !leg2.inMove() && !leg3.inMove() && !leg4.inMove())) {
    lastUpdate = millis();

    switch (currentProgNum) {
      case 1: programRunForward(); break;
      case 2: programTurnRight(); break;
      case 3: programTurnLeft(); break;
      case 4: programReadyPosition(); break;
      case 5: programHandShake(); break;

      case 6: programStepInL(); break;
      case 7: programStepInR(); break;
      case 8: programStepOut(); break;
      case 9: programUpDown2(); break; // 2 params - abs val of Z
      case 10: programRolling(); break; //
      case 11: programShift(); break; // 2 params - rel L/R 
      case 12: programSway(); break; // 2 params - rel L/R
    }

  }

  leg1.update();
  leg2.update();
  leg3.update();
  leg4.update();

}


void endOfOneProgramStep(int program[][4][3], int cnt, boolean again) {

  if (customParam[2] && (customParam[2] != storedSpeed)) {
    storedSpeed = leg1.getSpeed();
    leg1.setSpeed(customParam[2]);
    leg2.setSpeed(customParam[2]);
    leg3.setSpeed(customParam[2]);
    leg4.setSpeed(customParam[2]);
  }
  
  leg1.goToPos(program[progStep][0][0], program[progStep][0][1], program[progStep][0][2]);
  leg2.goToPos(program[progStep][1][0], program[progStep][1][1], program[progStep][1][2]);
  leg3.goToPos(program[progStep][2][0], program[progStep][2][1], program[progStep][2][2]);
  leg4.goToPos(program[progStep][3][0], program[progStep][3][1], program[progStep][3][2]);

  progStep++;
  if (progStep > (cnt - 1)) {
    progStep = 0;
    progRun = (currentProgNum != nextProgNum || again);
    currentProgNum = nextProgNum;

    if (customParam[2] && (customParam[2] != storedSpeed)) {
      leg1.setSpeed(storedSpeed);
      leg2.setSpeed(storedSpeed);
      leg3.setSpeed(storedSpeed);
      leg4.setSpeed(storedSpeed);
    }

    if (customParam[3]) {
      progRun = (customParam[3] > 0);
    }
    
  }
}

//////////////////////////////////////////////////////////////////////////


void programRunForward() {

  if (!standPosition) { // left

    int program[][4][3] = {

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, //1
      { {s * 2, y - 20, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {s * 2, y - 20, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {s, y, zd}, {0, y, zd}, {s * 2, y, zd} , {s, y, zd} },  //shift

      { {s, y, zd}, {0, y, zd}, {s * 2, y, zu} , {s, y, zd} }, //3
      { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} },
      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

    };

    endOfOneProgramStep(program, 8, true);

  } else { // right

    int program[][4][3] = {

      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

      { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} }, //2
      { {s, y, zd}, {s * 2, y - 20, zu}, {0, y, zd} , {s, y, zd} },
      { {s, y, zd}, {s * 2, y - 20, zd}, {0, y, zd} , {s, y, zd} },

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s * 2, y, zd} }, //shift

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s * 2, y, zu} }, //4
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} },
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    };

    endOfOneProgramStep(program, 8, true);

  }

  if (progStep == 0) {
    standPosition = !standPosition;
  }

}

void programReadyPosition() {
  int program[][4][3] = {
    { {s, y, 0}, {s, y, 0}, {s, y, 0} , {s, y, 0} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
  };
  endOfOneProgramStep(program, 2, false);
}


void programTurnRight() {

  if (!standPosition) { // left

    int program[][4][3] = {

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, //1
      { {y, 0, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {y, 0, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

//      { {s, y, zd}, {y, 0, zd}, {0, y, zd} , {s, y, zd} },//roll
//
//      { {s, y, zd}, {y, 0, zu}, {0, y, zd} , {s, y, zd} }, //2
//      { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} },
//      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

      { {y, 0, zd}, {s, y, zu}, {s, y, zd} , {0, y, zd} }, //2u
      { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} }, //roll
      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} }, //2d

    };

    endOfOneProgramStep(program, 7, true);

  } else { // right

    int program[][4][3] = {

      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

      { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} }, //3
      { {s, y, zd}, {0, y, zd}, {y, 0, zu} , {s, y, zd} },
      { {s, y, zd}, {0, y, zd}, {y, 0, zd} , {s, y, zd} },

//      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zd} }, //roll
//
//      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zu} }, //4
//      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} },
//      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {s, y, zd}, {0, y, zd}, {y, 0, zd} , {s, y, zu} }, //4u
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} }, //roll
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, //4d

    };

    endOfOneProgramStep(program, 7, true);

  }

  if (progStep == 0) {
    standPosition = !standPosition;
  }

}


void programTurnLeft() {

  if (!standPosition) { // left

    int program[][4][3] = {

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} }, //4
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zu} },
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zd} },

//      { {s, y, zd}, {0, y, zd}, {y, 0, zd} , {s, y, zd} }, //roll
//
//      { {s, y, zd}, {0, y, zd}, {y, 0, zu} , {s, y, zd} }, //3
//      { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} },
//      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

      { {0, y, zd}, {s, y, zd}, {s, y, zu} , {y, 0, zd} }, //3u
      { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} }, //roll
      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} }, //3d

    };

    endOfOneProgramStep(program, 7, true);

  } else { // right

    int program[][4][3] = {

      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

      { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} }, //2
      { {s, y, zd}, {y, 0, zu}, {0, y, zd} , {s, y, zd} },
      { {s, y, zd}, {y, 0, zd}, {0, y, zd} , {s, y, zd} },

//      { {y, 0, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, // roll
//
//      { {y, 0, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, //1
//      { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
//      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {s, y, zu}, {y, 0, zd}, {0, y, zd} , {s, y, zd} }, //1u
      { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, // roll
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    };

    endOfOneProgramStep(program, 7, true);

  }

  if (progStep == 0) {
    standPosition = !standPosition;
  }

}




void programHandShake() {

  if (!standPosition) { // left

    int program[][4][3] = {

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },//1
      { {s, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {100, y, 80}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {120, 0, 80}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {100, y, 80}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {120, 0, 80}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {100, y, 80}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {120, 0, 80}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {100, y, 80}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {s, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
      { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    };

    endOfOneProgramStep(program, 13, false);

  } else { // right

    int program[][4][3] = {

      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

      { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} },//1
      { {s, y, zd}, {s, y, zu}, {0, y, zd} , {s, y, zd} },

      { {s, y, zd}, {100, y, 80}, {0, y, zd}, {s, y, zd} },
      { {s, y, zd}, {120, 0, 80}, {0, y, zd}, {s, y, zd} },
      { {s, y, zd}, {100, y, 80}, {0, y, zd}, {s, y, zd} },
      { {s, y, zd}, {120, 0, 80}, {0, y, zd}, {s, y, zd} },
      { {s, y, zd}, {100, y, 80}, {0, y, zd}, {s, y, zd} },
      { {s, y, zd}, {120, 0, 80}, {0, y, zd}, {s, y, zd} },
      { {s, y, zd}, {100, y, 80}, {0, y, zd}, {s, y, zd} },

      { {s, y, zd}, {s, y, zu}, {0, y, zd} , {s, y, zd} },
      { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} },

      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

    };

    endOfOneProgramStep(program, 13, false);

  }

}


/////////////////////////////////////


void programStepInL() {
  int program[][4][3] = {
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },

    { {s*2, y, zd}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },
    
    { {s*2, y, zu}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },
    { {s, y, zu}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },
    { {s, y, zd}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zu} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    
  };
  endOfOneProgramStep(program, 9, false);
  standPosition = 0;
}

void programStepInR() {
  int program[][4][3] = {
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },

    { {s*2, y, zd}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },

    { {s*2, y, zd}, {s*2, y, zu}, {0, y, zd} , {0, y, zd} },
    { {s*2, y, zd}, {s, y, zu}, {0, y, zd} , {0, y, zd} },
    { {s*2, y, zd}, {s, y, zd}, {0, y, zd} , {0, y, zd} },

    { {s, y, zd}, {0, y, zd}, {s, y, zd} , {s, y, zd} },

    { {s, y, zd}, {0, y, zd}, {s, y, zu} , {s, y, zd} },
    { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} },
    { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },
    
  };
  endOfOneProgramStep(program, 9, false);
  standPosition = 1;
}


void programStepOut() {

  if (!standPosition) { // left
  
    int program[][4][3] = {
      
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} },
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zu} },
      { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },

      { {s, y, zd}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },

      { {s, y, zu}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },
      { {s*2, y, zu}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },
      { {s*2, y, zd}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },

      { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
      
    };
    
    endOfOneProgramStep(program, 9, false);

  } else { // right

    int program[][4][3] = {
      
      { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

      { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} },
      { {s, y, zd}, {0, y, zd}, {s, y, zu} , {s, y, zd} },
      { {s, y, zd}, {0, y, zd}, {s, y, zd} , {s, y, zd} },

      { {s*2, y, zd}, {s, y, zd}, {0, y, zd} , {0, y, zd} },

      { {s*2, y, zd}, {s, y, zu}, {0, y, zd} , {0, y, zd} },
      { {s*2, y, zd}, {s*2, y, zu}, {0, y, zd} , {0, y, zd} },
      { {s*2, y, zd}, {s*2, y, zd}, {0, y, zd} , {0, y, zd} },

      { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
      
    };
    
    endOfOneProgramStep(program, 9, false);
    
  }
  
}


void programUpDown2() {

  int shiftU = customParam[0] ? customParam[0] : zu;
  int shiftD = customParam[1] ? customParam[1] : zd;
  
  int program[][4][3] = {
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
    { {s, y, shiftU}, {s, y, shiftU}, {s, y, shiftU} , {s, y, shiftU} },
    { {s, y, shiftD}, {s, y, shiftD}, {s, y, shiftD} , {s, y, shiftD} },
    { {s, y, shiftU}, {s, y, shiftU}, {s, y, shiftU} , {s, y, shiftU} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
  };
  endOfOneProgramStep(program, 5, false);
}




//int calcRollingCoord(Leg l, char coord, int angle) {
//  float Ar = customParam[0] * PI / 180;
//  if (coord == 'x') {
//    return l.getX() * cos(Ar) - l.getY() * sin(Ar);
//  } else {
//    return l.getX() * sin(Ar) + l.getY() * cos(Ar);
//  }
//}
void programRolling() { 
  int program[][4][3] = {
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
    { {0, y+18, zd}, {y, 0, zd}, {0, y+18, zd} , {y, 0, zd} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
    { {y, 0, zd}, {0, y+18, zd}, {y, 0, zd} , {0, y+18, zd} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
  };
  endOfOneProgramStep(program, 5, false);
}


void programShift() {

  int shiftL = customParam[0] ? customParam[0] : y/2;
  int shiftR = customParam[1] ? customParam[1] : shiftL;
  
  int program[][4][3] = {
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
    { {s, y-shiftL, zd}, {s, y+shiftL, zd}, {s, y+shiftL, zd} , {s, y-shiftL, zd} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
    { {s, y+shiftR, zd}, {s, y-shiftR, zd}, {s, y-shiftR, zd} , {s, y+shiftR, zd} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
  };
  endOfOneProgramStep(program, 5, false);
}

void programSway() {

  int shiftL = customParam[0] ? customParam[0] : 20;
  int shiftR = customParam[1] ? customParam[1] : shiftL;
  
  int program[][4][3] = {
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
    { {s, y, zd+shiftL}, {s, y, zd-shiftR}, {s, y, zd-shiftR} , {s, y, zd+shiftL} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
    { {s, y, zd-shiftL}, {s, y, zd+shiftR}, {s, y, zd+shiftR} , {s, y, zd-shiftL} },
    { {s, y, zd}, {s, y, zd}, {s, y, zd} , {s, y, zd} },
  };
  endOfOneProgramStep(program, 5, false);
}
