void sequence() {
  Serial.println("What Seqeunce?");
  while (Serial.available() == 0 & Serial2.available() == 0) {}
  delay(200);
  String sqInput;
  if (Serial.available() > 0)
    sqInput = Serial.readString();
  else
    sqInput = Serial2.readString();
  sqInput.trim();
  delay(100);
  Serial.println("drawing:" + sqInput);

  if (sqInput == "triforce") {
    sq_triforce();
  } else if (sqInput == "square") {
    sq_square();
  } else if (sqInput == "cock") {
    sq_cock();
  } else if (sqInput == "cock2") {
    sq_cock2();
  } else if (sqInput == "cock3") {
    sq_cock3();
  } else if (sqInput == "wdg") {
    sq_wdg();
  } else if (sqInput == "xxxlFunction") {
    sq_xxlFunc();
  } else if (sqInput == "coolTris") {
    sq_coolTris();
  } else if (sqInput == "heart") {
    sq_heart();
  } else if (sqInput == "heart2") {
    sq_heart2();
  } else if (sqInput == "3d") {
    sq_threeD();
  } else if (sqInput == "pokeball") {
    sq_pokeball();
  } else if (sqInput == "1up") {
    sq_oneUp();
  } else Serial.println("Error404");
}
void sq_triforce() {
  long posesX[] = { 0, 5000, 10000, 0, 2500, 5000, 7500, 2500, 0 };
  long posesY[] = { 0, 9000, 0, 0, 4500, 0, 4500, 4500, 0 };
  for (int i = 0; i < 9; i++) {
    coolStepping(posesX[i], posesY[i]);
  }
}
void sq_square() {
  long posesX[] = { 8000, 8000, 0, 0 };
  long posesY[] = { 0, 8000, 8000, 0 };
  for (int i = 0; i < 4; i++) {
    coolStepping(posesX[i], posesY[i]);
  }
}
void sq_cock() {
  long posesX[] = { 4000, 8000, 4000, 0, 4000, 8000, 8000, 11000, 11000, 8000, 14000, 11000, 14000, 14000, 18000, 22000, 18000, 14000 };
  long posesY[] = { 0, 4000, 8000, 4000, 0, 4000, 20000, 23000, 20000, 20000, 20000, 23000, 20000, 4000, 0, 4000, 8000, 4000 };
  for (int i = 0; i < 18; i++) {
    coolStepping(posesX[i], posesY[i]);
  }
}
void sq_cock2() {
  circleCool(4000, 4000, 4000, 540, 0);
  circleCool(3000, 11000, 20000, 180, 0);
  long posesX[] = { 8000, 11000, 11000, 11000, 14000, 14000 };
  long posesY[] = { 20000, 20000, 23000, 20000, 20000, 4000 };
  for (int i = 0; i < 6; i++) {
    coolStepping(posesX[i], posesY[i]);
  }
  circleCool(4000, 18000, 4000, 360, 0);
  coolStepping(8000, 4000);
}
void sq_cock3() {
  circleCool(4000, 4000, 4000, 450, 0);
  circleCool(4000, 8000, 30000, 90, 0);
  coolStepping(8000, 32000);
  circleCool(4000, 8000, 30000, 90, 90);
  coolStepping(4000, 30000);
  coolStepping(12000, 30000);
  circleCool(4000, 12000, 4000, 360, 90);
}
void sq_wdg() {
  upZ();
  coolStepping(0,5000);
  downZ();
  circleCool(5000, 5000, 5000, 360, 0);
  circleCool(5000, 5000, 5000, 0, 300);
  coolStepping(5000, 2000);
  circleCool(5000, 5000, 5000, 0, 240);
  circleCool(5000, 5000, 5000, 0, 180);
  coolStepping(7000, 3500);
  circleCool(5000, 5000, 5000, 0, 90);
  coolStepping(3000, 3500);
  circleCool(5000, 5000, 5000, 0, 0);
}
void sq_heart() {
  float sqSize = 10;
  coolStepping(500 * sqSize, 0 * sqSize);
  circleCool(250 * sqSize, 250 * sqSize, 750 * sqSize, 220, 320);
  circleCool(250 * sqSize, 750 * sqSize, 750 * sqSize, 220, 0);
  long posesX[] = { 500, 600, 400, 500 };
  long posesY[] = { 0, 250, 500, 750 };
  for (int i = 0; i < 4; i++) {
    coolStepping(posesX[i] * sqSize, posesY[i] * sqSize);
  }
}
void sq_heart2() {
  coolStepping(5000, 0, true);
  cubicBezier(5000, 0, -2000, 5000, 3000, 10000, 5000, 5000, 32);
  cubicBezier(5000, 5000, 7000, 10000, 12000, 5000, 5000, 0, 32);
}
void sq_threeD() {
  coolStepping(5000, 0);
  coolStepping(5000, 5000);
  coolStepping(0, 5000);
  coolStepping(0, 0);
  coolStepping(5000, 0);
  coolStepping(7500, 2500);
  coolStepping(7500, 7500);
  coolStepping(5000, 5000);
  coolStepping(0, 5000);
  coolStepping(2500, 7500);
  coolStepping(7500, 7500);
}
void sq_pokeball() {
  circleCool(5000, 5000, 5500, 180, 0);
  coolStepping(9750, 5500);
  coolStepping(9750, 5000);
  circleCool(1500, 5000, 5250, 160, 190);
  coolStepping(0, 5000);
  coolStepping(250, 5000);
  coolStepping(250, 5500);
  coolStepping(0, 5500);
  circleCool(1500, 5000, 5250, 160, 10);
  coolStepping(9750, 5500);
  coolStepping(9750, 5000);
  circleCool(5000, 5000, 5000, 180, 180);
}
void sq_oneUp() {
  cubicBezier(5000, 5000, 5000, 2000, 5000, 0, 10000, 0, 32);
  cubicBezier(10000, 0, 15000, 0, 15000, 2000, 15000, 5000, 32);
  cubicBezier(15000, 5000, 13000, 7000, 7000, 7000, 5000, 5000, 32);
  cubicBezier(5000, 5000, 0, 8000, 4000, 15000, 10000, 15000, 32);
  cubicBezier(10000, 15000, 16000, 15000, 20000, 8000, 15000, 5000, 32);

  //cubicBezier(15000,5000,20000,8000,16000,15000,10000,15000,32);
  //cubicBezier(10000,15000,4000,15000,0,8000,5000,5000,32);
}
void sq_xxlFunc() {
  circleCool(5000, 5000, 5000, 360, 0);
  for (int a = 0; a <= 360; a += 10) {
    for (double i = 0; i <= 360; i += 360 / 3) {
      circleCool(5000, 5000, 5000, a, i);
    }
  }
}
void sq_coolTris() {
  circleCool(5000, 5000, 5000, 360, 0);
  for (int a = 0; a <= 120; a += 10) {
    for (double i = 0; i <= 360; i += 120) {
      circleCool(5000, 5000, 5000, 0, i + a);
    }
  }
}
void sq_demo() {
  for (int i = 0; i < 4; i++) {
    sq_heart2();
    setOffset(8000, 0);
  }
  setOffset(-32000, 0);
  upZ();
  coolStepping(0, 0);
  downZ();
  setOffset(0, 9000);
  for (int i = 0; i < 3; i++) {
    coolStepping(0, 0);
    sq_wdg();
    coolStepping(0, 0);
    setOffset(10000, 0);
  }
  setOffset(-40000, 0);
  coolStepping(0, 0);
  setOffset(0, 9000);
  for (int i = 0; i < 3; i++) {
    sq_triforce();
    setOffset(10000, 0);
  }
  setOffset(-40000, 0);
  coolStepping(0, 0);
  setOffset(0, 9000);
  for (int i = 0; i < 3; i++) {
    coolStepping(0, 0);
    sq_coolTris();
    coolStepping(0, 0);
    setOffset(10000, 0);
  }
}
