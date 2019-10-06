int y = 60;
int yu = 60; // for up
int s = 50; // step
int s_ = 70; // betw 2 legs
int zd = -50;
int zu = -20;



int updateInterval = 100;
unsigned long lastUpdate;


int progRun = false;
int program[50][4][3];
int progStep = 0;
int progLength = 0;




void checkUpdateInterval() {

  if (progRun && ((millis() - lastUpdate) > updateInterval) && (!leg1.inMove() && !leg2.inMove() && !leg3.inMove() && !leg4.inMove())) {
    //    if (progRun && ((millis() - lastUpdate) > updateInterval) && (!leg1.inMove() && !leg2.inMove() && !leg3.inMove() && !leg4.inMove()))

    lastUpdate = millis();

    //    Serial.println("[step: " + String(progStep) + "]>> " + String(program[progStep][0][1]));
    //
    //    progStep++;
    //    if (progStep == progLength) {
    //      progStep = 0;
    //    }



    int program[20][4][3] = {

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




      { { -1, 0, 0}, {0, 0, 0}, {0, 0, 0} , {0, 0, 0} },
    };

    leg1.goToPos(program[progStep][0][0], program[progStep][0][1], program[progStep][0][2]);
    leg2.goToPos(program[progStep][1][0], program[progStep][1][1], program[progStep][1][2]);
    leg3.goToPos(program[progStep][2][0], program[progStep][2][1], program[progStep][2][2]);
    leg4.goToPos(program[progStep][3][0], program[progStep][3][1], program[progStep][3][2]);

    progStep++;
    if (progStep > 14) progStep = 0;





  }

  leg1.update();
  leg2.update();
  leg3.update();
  leg4.update();

}








void program_step_forward() {

  int p[15][4][3] = {

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

  progLength = sizeof(p) / sizeof(int) / 12;
  Serial.println(progLength);

  //  for (int i = 0; i < progLength; i++) {
  //    for (int l = 0; l < 4; l++) {
  //      for (int s = 0; s < 3; s++) {
  //        program[i][l][s] = p[i][l][s];
  //      }
  //    }
  //  }

}
