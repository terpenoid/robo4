int y = 60;
int yu = 60; // for up
int s = 50; // step
int s_ = 70; // betw 2 legs
int zd = -50;
int zu = -20;



int updateInterval = 100;
unsigned long lastUpdate;

int progRun = false;
int progStep = 0;




void programRunForward(); // declaration of function who will be sendet as argument
void programRunUpDown();

void doOneProgramStep(void (*)()); // function who will run another declared function




void doOneProgramStep(void (*function)()) {

  if (progRun && ((millis() - lastUpdate) > updateInterval) && (!leg1.inMove() && !leg2.inMove() && !leg3.inMove() && !leg4.inMove())) {
    lastUpdate = millis();
    (*function)();
  }

  leg1.update();
  leg2.update();
  leg3.update();
  leg4.update();

}


void programRunForward() {

  int program[15][4][3] = {

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    { {0, yu, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    { {s * 2, y - 20, zu}, {s, y, zd}, {s, y, zd} , {0, y, zd} },
    { {s * 2, y - 20, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

    { {s, y, zd}, {0, y, zd}, {s * 2, y, zd} , {s, y, zd} },

    { {s, y, zd}, {0, y, zd}, {s * 2, y, zu} , {s, y, zd} },
    { {s, y, zd}, {0, y, zd}, {0, yu, zu} , {s, y, zd} },
    { {s, y, zd}, {0, y, zd}, {0, y, zd} , {s, y, zd} },

    { {s, y, zd}, {0, yu, zu}, {0, y, zd} , {s, y, zd} },
    { {s, y, zd}, {s * 2, y - 20, zu}, {0, y, zd} , {s, y, zd} },
    { {s, y, zd}, {s * 2, y - 20, zd}, {0, y, zd} , {s, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s * 2, y, zd} },

    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {s * 2, yu, zu} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, yu, zu} },
    { {0, y, zd}, {s, y, zd}, {s, y, zd} , {0, y, zd} },

  };

  leg1.goToPos(program[progStep][0][0], program[progStep][0][1], program[progStep][0][2]);
  leg2.goToPos(program[progStep][1][0], program[progStep][1][1], program[progStep][1][2]);
  leg3.goToPos(program[progStep][2][0], program[progStep][2][1], program[progStep][2][2]);
  leg4.goToPos(program[progStep][3][0], program[progStep][3][1], program[progStep][3][2]);

  progStep++;
  if (progStep > 14) {
    progStep = 0;
  }


}

void programRunUpDown() {

  int program[2][4][3] = {

    { {20, y - 10, zd}, {20, y - 10, zd}, {20, y - 10, zd} , {20, y - 10, zd} },
    { {20, yu, zu}, {20, yu, zu}, {20, yu, zu} , {20, yu, zu} },

  };

  leg1.goToPos(program[progStep][0][0], program[progStep][0][1], program[progStep][0][2]);
  leg2.goToPos(program[progStep][1][0], program[progStep][1][1], program[progStep][1][2]);
  leg3.goToPos(program[progStep][2][0], program[progStep][2][1], program[progStep][2][2]);
  leg4.goToPos(program[progStep][3][0], program[progStep][3][1], program[progStep][3][2]);

  progStep++;
  if (progStep > 1) {
    progStep = 0;
    progRun = false;
  }


}
