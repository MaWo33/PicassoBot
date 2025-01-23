#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Potentio           A3

int MotorDelay = 30;

bool motorDir = true;
#include "pitches.h" 
int melody[] = {
  0,//AUFTAKT
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//REP
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//
  0,NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_GS4,//Lower
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//REP
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//(Cut)
  NOTE_GS4, NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_GS4,//Lower
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//REP
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//
  0,NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_GS4,//Lower
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//REP
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//
  0,NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5,//(Cut)
  NOTE_GS4, NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_FS4,//Lower
  
  NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_AS5, 0, NOTE_DS6, NOTE_CS6,//09
  NOTE_AS5, 0, NOTE_DS5, 0, NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_F5,//10
  NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_AS5, 0, NOTE_GS5, NOTE_FS5,//11
  NOTE_F5, NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_D5, NOTE_F5,//12
  NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_AS5, 0, NOTE_DS6, NOTE_CS6,//13
  NOTE_AS5, 0, NOTE_DS5, 0, NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_F5,//14
  NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_AS5, 0, NOTE_GS5, NOTE_FS5,//15
  NOTE_F5, 0, NOTE_FS5, 0, NOTE_GS5, 0, NOTE_AS5, 0,//16
  NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_AS5, 0, NOTE_DS6, NOTE_CS6,//17
  NOTE_AS5, 0, NOTE_DS5, 0, NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_F5,//18
  NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_AS5, 0, NOTE_GS5, NOTE_FS5,//19
  NOTE_F5, NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_D5, NOTE_F5,//20
  NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_AS5, 0, NOTE_DS6, NOTE_CS6//21
};

int durations[] = {
  2, //Auftakt
  1, 2, 1, 1, 3,//REP
  1, 2, 1, 1, 3,//
  1, 2, 1, 1, 3,//
  1, 1, 2, 1, 3,//Lower
  1, 2, 1, 1, 3,//REP
  1, 2, 1, 1, 3,//
  1, 2, 1, 1, 1,//(Cut)
  2, 1, 1, 2, 1, 3, //Lower
  1, 2, 1, 1, 3,//REP
  1, 2, 1, 1, 3,//
  1, 2, 1, 1, 3,//
  1, 1, 2, 1, 3,//Lower
  1, 2, 1, 1, 3,//REP
  1, 2, 1, 1, 3,//
  1, 2, 1, 1, 1,//(Cut)
  2, 1, 1, 3, 1,//Lower (Cut)
  
  2, 2, 2, 2, 3, 1, 2, 2,//09
  3, 1, 3, 1, 2, 2, 2, 2,//10
  2, 2, 2, 2, 3, 1, 2, 2,//11
  2, 2, 2, 2, 2, 2, 2, 2,//12
  2, 2, 2, 2, 3, 1, 2, 2,//13
  3, 1, 3, 1, 2, 2, 2, 2,//14
  2, 2, 2, 2, 3, 1, 2, 2,//15
  3, 1, 3, 1, 3, 1, 3, 1,//16
  2, 2, 2, 2, 3, 1, 2, 2,//17
  3, 1, 3, 1, 2, 2, 2, 2,//18
  2, 2, 2, 2, 3, 1, 2, 2,//19
  2, 2, 2, 2, 2, 2, 2, 2,//20
  2, 2, 2, 2, 3, 1, 2, 2//21
};


void setup() {
  // put your setup code here, to run once:
  pinMode(X_STEP_PIN ,OUTPUT);
  pinMode(X_ENABLE_PIN ,OUTPUT);
  
  digitalWrite(X_ENABLE_PIN, LOW);
  Serial.begin(115200);
}

void loop() {
  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    Serial.println((float)analogRead(Potentio)/500);
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 100 * durations[note];
    tone(X_STEP_PIN, melody[note]*6, duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.3f;
    delay(pauseBetweenNotes);

    motorDir = !motorDir;
    digitalWrite(X_DIR_PIN, int(motorDir));
    
    
    //stop the tone playing:
    noTone(X_STEP_PIN);
  }
  motorDir = !motorDir;
  digitalWrite(X_DIR_PIN, int(motorDir));

}
