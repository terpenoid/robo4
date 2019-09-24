// ./calc.html

struct LegState {
  float alpha;  // coxa
  float beta;   // femur
  float gamma;  // tibia
};

struct Point {
  float x;
  float y;
  float z;
};

// dimensions
float coxaZShift = 26;
float coxaLength = 27;
float femurLength = 54;
float tibiaLength = 78;



Point computeMiddlePoint(Point p1, Point p2, float Rac) {
  float Rab = sqrt(sq(p2.x-p1.x) + sq(p2.y-p1.y) + sq(p2.z-p1.z));
  float k = Rac / Rab;
  Point res;
  res.x = p1.x + (p2.x-p1.x)*k;
  res.y = p1.y + (p2.y-p1.y)*k;
  res.z = p1.z + (p2.z-p1.z)*k;
  return res;
}



LegState computeAngles(Point point) {

  // init result
  LegState result = { alpha: 90, beta: 90, gamma: 90 };

  // @TODO: fix possible errors for coords out from possible
  //  if (point.x < 0) point.x = 0;
  //  if (point.y < 0) point.y = 0;
  //  if (point.z < -50) point.z = -50;
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
  if (point.x != 0) {
    alphaR = atan(point.y / point.x);
  } else {
    alphaR = PI / 2;
  }
  alphaD = alphaR * 180 / PI;
  //Serial.print("alpha: "); Serial.print(alphaD); Serial.print("("); Serial.print(alphaR); Serial.println(")");

  // coxa B(X/Y)
  Xb = cos(alphaR) * coxaLength;
  Yb = sin(alphaR) * coxaLength;

  // AD (on grid 1)
  AD1 = sqrt(sq(point.x) + sq(point.y));
  //Serial.print("AD1: "); Serial.println(AD1);

  ////////////////////////////////
  // on Grid2:
  //----------------------

  Xb = coxaLength;
  Yb = coxaZShift;

  Xd = AD1;
  Yd = point.z;

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
  //Serial.print("D: "); Serial.println(d);

  b = (sq(r2) - sq(r1) + sq(d)) / (2 * d);
  a = d - b;
  h = sqrt(sq(r2) - sq(b));
  x = x1 + (x2 - x1) / (d / a);
  y = y1 + (y2 - y1) / (d / a);
  x3 = x - (y - y2) * h / b;
  y3 = y + (x - x2) * h / b;
  x4 = x + (y - y2) * h / b;
  y4 = y - (x - x2) * h / b;

  //Serial.print("X1: "); Serial.print(x3); Serial.print("\nY1: "); Serial.println(y3);
  //Serial.print("X2: "); Serial.print(x4); Serial.print("\nY2: "); Serial.print(y4);

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

  //Serial.print("Xc: "); Serial.print(Xc); Serial.print("\nYc: "); Serial.println(Yc);
  ///////////////


  // AC (on grid 2)
  AC2 = sqrt(sq(Xc) + sq(Yc - coxaZShift));
  //Serial.print("AC2: "); Serial.println(AC2);


  // BD (on grid 2)
  BD2 = sqrt(sq(Xd - Xb) + sq(Yd - Yb));
  //Serial.print("BD2: "); Serial.println(BD2);

  // https://www.calc.ru/raschet-treugolnika.html

  // gamma
  A = femurLength;
  B = tibiaLength;
  C = BD2;
  //Serial.print("A: "); Serial.print(A); Serial.print("\nB: "); Serial.print(B); Serial.print("\nC: "); Serial.println(C);
  gammaR = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B));
  gammaD = gammaR * 180 / PI;
  //Serial.print("gamma: "); Serial.print(gammaD); Serial.print("("); Serial.print(gammaR); Serial.println(")");


  // beta
  A = femurLength;
  B = coxaLength;
  C = AC2;
  //Serial.print("A: "); Serial.print(A); Serial.print("\nB: "); Serial.print(B); Serial.print("\nC: "); Serial.println(C);
  betaR = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B));
  betaD = betaR * 180 / PI;
  //Serial.print("beta: "); Serial.print(betaD); Serial.print("("); Serial.print(betaR); Serial.println(")");


  result.alpha = alphaD;
  result.beta = betaD;
  result.gamma = gammaD;

  return result;
}
