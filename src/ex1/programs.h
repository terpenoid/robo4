int y = 60;
int s = 50; // step
int s_ = 70; // betw 2 legs
int zd = -50;
int zu = -20;



int updateInterval = 100;
unsigned long lastUpdate;

int currentProgNum = 0;
int nextProgNum = 0;

int progRun = false;
int progStep = 0;




void programRunForward(); // declaration of function who will be sendet as argument
void programRunUpDown();
void programTurnLeft();
void programTurnRight();
void programHandShake();





void doOneProgramStep() {

  if (progRun && ((millis() - lastUpdate) > updateInterval) && (!leg1.inMove() && !leg2.inMove() && !leg3.inMove() && !leg4.inMove())) {
    lastUpdate = millis();
    
    switch (currentProgNum) {
      case 1: programRunForward(); break;
      case 2: programRunUpDown(); break;
      case 3: programTurnLeft(); break;
      case 4: programTurnRight(); break;
      case 5: programHandShake(); break;
    }

  }

  leg1.update();
  leg2.update();
  leg3.update();
  leg4.update();

}


void endOfOneProgramStep(int program[][4][3], int cnt, boolean again) {
  leg1.goToPos(program[progStep][0][0], program[progStep][0][1], program[progStep][0][2]);
  leg2.goToPos(program[progStep][1][0], program[progStep][1][1], program[progStep][1][2]);
  leg3.goToPos(program[progStep][2][0], program[progStep][2][1], program[progStep][2][2]);
  leg4.goToPos(program[progStep][3][0], program[progStep][3][1], program[progStep][3][2]);

  progStep++;
  if (progStep > (cnt-1)) {
    progStep = 0;
    progRun = (currentProgNum != nextProgNum || again);
    currentProgNum = nextProgNum;
  }
}


void programRunForward() {

  int program[15][4][3] = {

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    { {s * 2, y - 20, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    { {s * 2, y - 20, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    { {s, y, zd}, {0, y, zd}, {s * 2, y, zd} , {s, y, zd} },

    { {s, y, zd}, {0, y, zd}, {s * 2, y, zu} , {s, y, zd} },
    { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} },
    { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

    { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} },
    { {s, y, zd}, {s * 2, y - 20, zu}, {0, y, zd} , {s, y, zd} },
    { {s, y, zd}, {s * 2, y - 20, zd}, {0, y, zd} , {s, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s * 2, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s * 2, y, zu} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

  };
  
  endOfOneProgramStep(program, 15, true);
  
}

void programRunUpDown() {
  int program[4][4][3] = {

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    { {0, y, zu}, {s, y, zu}, {s, y, zu} , {0, y, zu} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    { {0, y, zu}, {s, y, zu}, {s, y, zu} , {0, y, zu} },

  };
  
  endOfOneProgramStep(program, 4, false);  
  
}




void programTurnLeft() {

  int program[15][4][3] = {

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    
    { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, //1
    { {y, 0, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    
    { {y, 0, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    { {s, y, zd}, {y, 0, zd}, {0, y, zd} , {s, y, zd} },//roll
    
    { {s, y, zd}, {y, 0, zu}, {0, y, zd} , {s, y, zd} }, //2
    { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} },
    
    { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} }, // 0.5 of cicle
    
    { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} }, //3
    { {s, y, zd}, {0, y, zd}, {y, 0, zu} , {s, y, zd} },
    
    { {s, y, zd}, {0, y, zd}, {y, 0, zd} , {s, y, zd} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zd} }, //roll
    
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zu} }, //4
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} },
    
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    
  };

  endOfOneProgramStep(program, 15, true);
  
}


void programTurnRight() {

  int program[15][4][3] = {

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zu} }, //4
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zu} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {y, 0, zd} },
    { {s, y, zd}, {0, y, zd}, {y, 0, zd} , {s, y, zd} }, //roll

    { {s, y, zd}, {0, y, zd}, {y, 0, zu} , {s, y, zd} }, //3
    { {s, y, zd}, {0, y, zd}, {0, y, zu} , {s, y, zd} },

    { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} }, // 0.5 of cicle

    { {s, y, zd}, {0, y, zu}, {0, y, zd} , {s, y, zd} }, //2
    { {s, y, zd}, {y, 0, zu}, {0, y, zd} , {s, y, zd} },

    { {s, y, zd}, {y, 0, zd}, {0, y, zd} , {s, y, zd} },
    { {y, 0, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, // roll

    { {y, 0, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} }, //1
    { {0, y, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    
    
  };

  endOfOneProgramStep(program, 15, true);
  
}




void programHandShake() {

  int program[13][4][3] = {

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
  
}
