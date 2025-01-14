void writeText() {
  setOffset(startPos[0], startPos[1]);
  delay(1000);
  recvWithEndMarker();
  downZ();
  for (int i = 0; i < sizeof(receivedChars) / sizeof(receivedChars[0]); i++) {
    if (receivedChars[i] == (char)NULL) {
      break;
    }
    printToAllSerials(String(receivedChars[i]));
    writeLetter(receivedChars[i]);
  }
  printToAllSerials(receivedChars);
  printToAllSerials("gex");
  receivedChars[0] = '\0';
  newData = false;
  upZ();
}
int font_size = 12;
int font_scale = font_size * 1200;
void writeLetter(char Letter) {
  switch (Letter) {
    case ' ':
      break;
    case 'A':
      coolStepping(0, 0, true);
      coolStepping(1000, 4000);
      coolStepping(1500, 2000);
      coolStepping(500, 2000);
      coolStepping(1500, 2000);
      coolStepping(2000, 0);
      break;
    case 'B':
      coolStepping(0, 0, true);
      circleCool(1000, 1000, 1000, -180, 270);
      coolStepping(0, 2000);
      circleCool(1000, 750, 3000, -180, 270);
      coolStepping(0, 4000);
      coolStepping(0, 0);
      break;
    case 'C':
      coolStepping(2000, 1000, true);
      circleCool(1000, 1000, 1000, 180, 180);
      circleCool(1000, 1000, 3000, 180, 0);
      break;
    case 'D':
      coolStepping(0, 0, true);
      circleCool(1000, 1000, 1000, -90, 270);
      circleCool(1000, 1000, 3000, -90, 180);
      coolStepping(0, 4000);
      coolStepping(0, 0);
      break;
    case 'E':
      coolStepping(2000, 0, true);
      coolStepping(0, 0);
      coolStepping(0, 2000);
      coolStepping(2000, 2000);
      coolStepping(0, 2000);
      coolStepping(0, 4000);
      coolStepping(2000, 4000);
      break;
    case 'F':
      coolStepping(0, 0, true);
      coolStepping(0, 2000);
      coolStepping(2000, 2000);
      coolStepping(0, 2000);
      coolStepping(0, 4000);
      coolStepping(2000, 4000);
      break;
    case 'G':
      coolStepping(1000, 2000, true);
      coolStepping(1000, 2000);
      coolStepping(2000, 2000);
      circleCool(1000, 1000, 1000, 180, 180);
      circleCool(1000, 1000, 3000, 180, 0);
      break;
    case 'H':
      coolStepping(0, 0, true);
      coolStepping(0, 4000);
      coolStepping(0, 2000);
      coolStepping(2000, 2000);
      coolStepping(2000, 4000);
      coolStepping(2000, 0);
      break;
    case 'I':
      coolStepping(500, 0, true);
      coolStepping(500, 4000);
      setOffset(-1000, 0);
      break;
    case 'J':
      coolStepping(0, 1000, true);
      circleCool(1000, 1000, 1000, -180, 0);
      coolStepping(2000, 4000);
      coolStepping(0, 4000);
      break;
    case 'K':
      coolStepping(0, 0, true);
      coolStepping(0, 4000);
      coolStepping(0, 2000);
      coolStepping(2000, 4000);
      coolStepping(0, 2000);
      coolStepping(2000, 0);
      break;
    case 'L':
      coolStepping(0, 4000, true);
      coolStepping(0, 0);
      coolStepping(2000, 0);
      break;
    case 'M':
      coolStepping(0, 0, true);
      coolStepping(0, 4000);
      coolStepping(1000, 2000);
      coolStepping(2000, 4000);
      coolStepping(2000, 0);
      break;
    case 'N':
      coolStepping(0, 0, true);
      coolStepping(0, 4000);
      coolStepping(2000, 0);
      coolStepping(2000, 4000);
      break;
    case 'O':
      coolStepping(0, 1000, true);
      circleCool(1000, 1000, 3000, 180, 0);
      circleCool(1000, 1000, 1000, 180, 180);
      break;
    case 'P':
      coolStepping(0, 0, true);
      coolStepping(0, 4000);
      circleCool(1000, 1000, 3000, 180, 90);
      coolStepping(0, 2000);
      break;
    case 'Q':
      coolStepping(1000, 0, true);
      circleCool(1000, 1000, 1000, 90, 270);
      circleCool(1000, 1000, 3000, 180, 0);
      circleCool(1000, 1000, 1000, 45, 180);
      coolStepping(1000, 1000);
      coolStepping(2000, 0);
      circleCool(1000, 1000, 1000, 45, 225);
      break;
    case 'R':
      coolStepping(0, 0, true);
      coolStepping(0, 4000);
      circleCool(1000, 1000, 3000, 180, 90);
      coolStepping(0, 2000);
      coolStepping(2000, 0);
      break;
    case 'S':
      coolStepping(0, 0, true);
      circleCool(1000, 1000, 1000, -180, 270);
      circleCool(1000, 1000, 3000, 180, 270);
      coolStepping(2000, 4000);
      break;
    case 'T':
      coolStepping(1000, 0, true);
      coolStepping(1000, 4000);
      coolStepping(0, 4000);
      coolStepping(2000, 4000);
      break;
    case 'U':
      coolStepping(0, 4000, true);
      circleCool(1000, 1000, 1000, -180, 0);
      coolStepping(2000, 4000);
      break;
    case 'V':
      coolStepping(0, 4000, true);
      coolStepping(1000, 0);
      coolStepping(2000, 4000);
      break;
    case 'W':
      coolStepping(0, 4000, true);
      coolStepping(400, 0);
      coolStepping(1000, 2000);
      coolStepping(1600, 0);
      coolStepping(2000, 4000);
      break;
    case 'X':
      coolStepping(0, 0, true);
      coolStepping(2000, 4000);
      coolStepping(1000, 2000);
      coolStepping(0, 4000);
      coolStepping(2000, 0);
      break;
    case 'Y':
      coolStepping(1000, 0, true);
      coolStepping(1000, 2500);
      coolStepping(0, 4000);
      coolStepping(1000, 2500);
      coolStepping(2000, 4000);
      break;
    case 'Z':
      coolStepping(0, 4000, true);
      coolStepping(2000, 4000);
      coolStepping(0, 0);
      coolStepping(2000, 0);
      break;
    case '.':
      coolStepping(0, 200, true);
      circleCool(200, 200, 200, 360, 0);
      setOffset(-1600, 0);
      break;
     case ',':
      coolStepping(0, 0, true);
      coolStepping(300,300);
      setOffset(-1700, 0);
      break;
    case '!':
      coolStepping(0, 200, true);
      circleCool(200, 200, 200, 360, 0);
      coolStepping(0, 750, true);
      coolStepping(0, 4000);
      coolStepping(400, 4000);
      coolStepping(400, 750);
      coolStepping(0, 750);
      setOffset(0, -1600);
      break;
    case '?':
      coolStepping(0, 200, true);
      circleCool(200, 200, 200, 360, 0);
      coolStepping(0, 750, true);
      circleCool(750, 500, 3250, -180, 270);
      setOffset(-1250, 0);
      break;
    case '+':
      coolStepping(0, 2000, true);
      coolStepping(2000, 2000);
      coolStepping(1000, 3000, true);
      coolStepping(1000, 1000);
      break;
    default:  //Missing Symbol
      coolStepping(0, 0, true);
      coolStepping(0, 4000);
      coolStepping(2000, 4000);
      coolStepping(2000, 0);
      coolStepping(0, 0);
      break;
  }
  upZ();
  setOffset(2500, 0);
}
