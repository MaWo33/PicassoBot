#include <Rotary.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38
#define X_MIN_PIN 3

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Y_MIN_PIN 14

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62
#define Z_MIN_PIN 18

#define JOY_B A5
#define JOY_X A3
#define JOY_Y A4

#define STATE_PIN 49
#define ENABLE_PIN 53

#define SD_CS 42
#define SD_SCK 52
#define SD_MOSI 51
#define SD_MISO 50

#define ROT_A 2
#define ROT_B 19
#define ROT_BUT 44

#include <math.h>


int CurrentStepsX = 10000;
int GoalStepsX = 0;
int MotorDelay = 50;
int AbsoluteDelay = 50;

bool MotorAn = false;
bool Xforward = true;
bool Yforward = true;
String input;

long startPos[] = { 0, 0, 0 };
long endPos[] = { 0, 0, 0 };
long altePos[] = { 0, 0 };
long neuePos[] = { 0, 0 };
long maxPos[2][2] = { { 0, 35000 }, { 0, 34000 } };
int zRange = 5000;
long numOfSteps;
long chaseX;
long chaseY;

long offset[2] = { 0, 0 };

long Exponent = 2;
float Streckfaktor = 1;

String serialOut;
bool Zdown = true;

long sqPosX[] = { 0 };
long sqPosY[] = { 0 };

//for bluetooth
const int MAX_STRING_LENGTH = 100;  // Adjust this value based on your needs
char receivedString[MAX_STRING_LENGTH];
int stringIndex = 0;

float globalSizeMultiplier = 1;

String gcodes[16] ={};

Rotary rot = Rotary(ROT_A, ROT_B);

void coolStepping(long, long = 0, bool = false);
void uncoolStep(long, long, long, bool = false);
void SinusCool(long, long = 1000, long = 5000, long = 69);
void circleCool(long, long = 0, long = 0, int = 360, int = 0);
void Potenz(long, long = 1);
void linearBezier(long, long = 0, long = 4000, long = 4000, long = 32);
void quadraticBezier(long, long = 0, long = 3000, long = 3000, long = 5000, long = 0, long = 32);
void cubicBezier(long, long = 0, long = 2000, long = 2000, long = 5000, long = 5000, long = 7000, long = 0, long = 32, float = 1.0f);
void butterfly(long, long = 1000, long = 1000);

void setup() {

  //set interrupt time bits
  //Setup timer interrupt
  // Reset Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  // Set Timer1 to CTC mode
  TCCR1B |= (1 << WGM12);
  
  // Set prescaler to 256
  TCCR1B |= (1 << CS12);
  
  // Set compare match value for 1 second interrupt
  OCR1A = 62;
  
  // Enable Timer1 compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // Enable global interrupts
  sei();

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(Z_MIN_PIN, INPUT);

  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);

  digitalWrite(X_DIR_PIN, LOW);
  digitalWrite(Y_DIR_PIN, HIGH);
  digitalWrite(Z_DIR_PIN, HIGH);

  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);

  pinMode(STATE_PIN, INPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, HIGH);

  pinMode(ROT_BUT, INPUT);

  Serial.begin(9600);
  Serial2.begin(9600);

  if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    //return;
  }

  if (digitalRead(STATE_PIN) == HIGH) {
    printToAllSerials("Bluetooth Connected");
  } else {
    printToAllSerials("Bluetooth Disconnected");
  }


  cycleMotor();
  calibrate();
  cycleMotor();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DAS IST ROBOTIK");
  lcd.setCursor(0, 1);
  lcd.print(":D");


}
void loop() {
  joySelect();
  if (Serial2.available() > 0)
    delay(500);
  while (Serial2.available() > 0) {
    char data = Serial2.read();
    receivedString[stringIndex] = data;
    stringIndex++;
  }

  receivedString[stringIndex] = '\0';
  stringIndex = 0;

  if (Serial.available() > 0 | receivedString[0] != '\0') {
    cycleMotor();
    if (receivedString[0] == '\0')
      input = Serial.readString();
    else
      input = String(receivedString);
    input.trim();
    printToAllSerials(input);
    if (input == "cycle" || input == "c") {
      cycleMotor();
    } else if (input == "coolStep" || input == "cs") {
      printToAllSerials("x,y");
      long* arr = getParams(3);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          coolStepping(arr[1]);
          break;
        case 2:
          coolStepping(arr[1], arr[2]);
          break;
      }
    } else if (input == "circle") {
      printToAllSerials("radius,circleX,circle>,its,startpoint");
      long* arr = getParams(6);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          circleCool(arr[1]);
          break;
        case 2:
          circleCool(arr[1], arr[2]);
          break;
        case 3:
          circleCool(arr[1], arr[2], arr[3]);
          break;
        case 4:
          circleCool(arr[1], arr[2], arr[3], arr[4]);
          break;
        case 5:
          circleCool(arr[1], arr[2], arr[3], arr[4], arr[5]);
          break;
      }

    } else if (input == "Pot") {
      printToAllSerials("exponent,streckfaktor");
      long* arr = getParams(6);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          Potenz(arr[1]);
          break;
        case 2:
          Potenz(arr[1], arr[2]);
          break;
      }
    } else if (input == "r") {
      startPos[0] = 0;
      startPos[1] = 0;
      endPos[0] = 0;
      endPos[1] = 0;
      printToAllSerials("reset");
    } else if (input == "wo") {
      whereUat();
    } else if (input == "sq") {
      sequence();
    } else if (input == "linbezier") {
      printToAllSerials("p0x,p0y,p1x,p1y,steps");
      long* arr = getParams(6);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          linearBezier(arr[1]);
          break;
        case 2:
          linearBezier(arr[1], arr[2]);
          break;
        case 3:
          linearBezier(arr[1], arr[2], arr[3]);
          break;
        case 4:
          linearBezier(arr[1], arr[2], arr[3], arr[4]);
          break;
        case 5:
          linearBezier(arr[1], arr[2], arr[3], arr[4], arr[5]);
          break;
      }
    } else if (input == "quadbezier") {
      printToAllSerials("p0x,p0y,p1x,p1y,p2x,p2y,steps");
      long* arr = getParams(8);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          quadraticBezier(arr[1]);
          break;
        case 2:
          quadraticBezier(arr[1], arr[2]);
          break;
        case 3:
          quadraticBezier(arr[1], arr[2], arr[3]);
          break;
        case 4:
          quadraticBezier(arr[1], arr[2], arr[3], arr[4]);
          break;
        case 5:
          quadraticBezier(arr[1], arr[2], arr[3], arr[4], arr[5]);
          break;
        case 6:
          quadraticBezier(arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
          break;
        case 7:
          quadraticBezier(arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]);
          break;
      }
    } else if (input == "cubicBezier") {
      printToAllSerials("p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,steps");
      long* arr = getParams(10);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          cubicBezier(arr[1]);
          break;
        case 2:
          cubicBezier(arr[1], arr[2]);
          break;
        case 3:
          cubicBezier(arr[1], arr[2], arr[3]);
          break;
        case 4:
          cubicBezier(arr[1], arr[2], arr[3], arr[4]);
          break;
        case 5:
          cubicBezier(arr[1], arr[2], arr[3], arr[4], arr[5]);
          break;
        case 6:
          cubicBezier(arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
          break;
        case 7:
          cubicBezier(arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]);
          break;
        case 8:
          cubicBezier(arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);
          break;
        case 9:
          cubicBezier(arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
          break;
      }
    } else if (input == "bezier3d") {
      cubicBezier(0, 0, 5000, 5000, 5000, -5000, 10000, 0, 16);
    } else if (input == "butterfly") {
      printToAllSerials("scale,x,y");
      long* arr = getParams(10);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          butterfly(arr[1]);
          break;
        case 2:
          butterfly(arr[1], arr[2]);
          break;
        case 3:
          butterfly(arr[1], arr[2], arr[3]);
          break;
      }
    } else if (input == "Joy") {
      joy();
      delay(100);
    } else if (input == "txt") {
      printToAllSerials("What do you want to write?");
      while (Serial.available() == 0 & Serial2.available() == 0) {}
      writeText();
      delay(100);
    } else if (input == "Sin") {
      printToAllSerials("Frequenz,Amplitude,Länge,Winkel");
      long* arr = getParams(6);
      int arrLength = arr[0] - 1;
      switch (arrLength) {
        case 1:
          SinusCool(arr[1]);
          break;
        case 2:
          SinusCool(arr[1], arr[2]);
          break;
        case 3:
          SinusCool(arr[1], arr[2], arr[3]);
          break;
        case 4:
          SinusCool(arr[1], arr[2], arr[3], arr[4]);
          break;
      }
    } else if (input == "tmp") {
      tmp();

    } else if (input == "offset") {
      printToAllSerials("x, y");
      long* arr = getParams(6);
      int arrLength = arr[0] - 1;
      setOffset(arr[1], arr[2]);
    } else if (input == "demo") {
      sq_demo();
    } else if (input == "Z") {
      toggleZ();
      if (!Zdown) printToAllSerials("Z is up");
      if (Zdown) printToAllSerials("Z is down");
    } else if (input == "cal") {
      calibrate();
    } else if (input == "upZ") {
      upZ();
      printToAllSerials("Z is up!");
    } else if (input == "downZ") {
      downZ();
      printToAllSerials("Z is down!");
    } else if (input == "fZ") {
      forceZ();
      printToAllSerials("Z is down bad!");
    } else if (input == "find bounds") {
      long tmp = 0;
      while (true) {
        tmp++;
        coolStepping(tmp, tmp);
        printToAllSerials(String(tmp));
      }

    } else if (input == "heartship") {
      printToAllSerials("schreibe so: K+M");
      while (Serial.available() == 0 & Serial2.available() == 0) {}
      delay(500);
      downZ();
      globalSizeMultiplier = 2;
      sq_heart2();
      globalSizeMultiplier = 1;
      coolStepping(6500, 5500, true);
      writeText();
      upZ();
    }
    else if(input == "gs"){
      printToAllSerials("Scale (was " + String(globalSizeMultiplier) + ") input *1000");
      long* arr = getParams(2);
      globalSizeMultiplier = float(arr[1])/1000;
      printToAllSerials("New scale set to " + String(globalSizeMultiplier));
    }
    else if(input == "parsegcode"){
      parseGC("WOLF~1.gco");
    }
    else if(input == "listgcode"){
      listGC();
    }
    cycleMotor();
    receivedString[0] = '\0';
  }
  input = "";
}
