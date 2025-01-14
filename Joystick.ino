float joyYDir;
float joyXDir;
float joySpeed = 64;
bool isJoyStickDown;
long whenJoyStickDown;
int longTime = 700;
int deadzone = 50;
long deltaTime = 0;
long lastTime;
long joyDownTime(){
  
}
void joy() {
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Mode");
  lcd.setCursor(2,0);
  lcd.print("Joystick");
  whenJoyStickDown = millis();
  while (true) {
    if (Serial.available() != 0) { break; }
    if (digitalRead(JOY_B)) {
      if(!isJoyStickDown){
        whenJoyStickDown = millis();
        isJoyStickDown = true;
      }
    }
    else{
      if(isJoyStickDown){
        long downTime = millis() - whenJoyStickDown;
        printToAllSerials(String(downTime));
        if(downTime < longTime){toggleZ();}
        else{break;}
      }
      isJoyStickDown = false;
    }
    joyXDir = (analogRead(JOY_X) - 512) * -1;
    joyYDir = (analogRead(JOY_Y) - 512) * -1;
    float joySize = sqrt(sq(joyXDir) + sq(joyYDir));
    if (joySize > 512) {
      joyXDir = 512 * (joyXDir / joySize);
      joyYDir = 512 * (joyYDir / joySize);
    }
    Serial.println(String(joyXDir) + " | " + String(joyYDir));
    joyXDir = (digitalRead(X_MIN_PIN) == LOW && joyXDir < 0) ? 0 : joyXDir;
    joyYDir = (digitalRead(Y_MIN_PIN) == LOW && joyYDir > 0) ? 0 : joyYDir;
    joyXDir = (startPos[0] > 35000 && joyXDir > 0) ? 0 : joyXDir;
    joyYDir = (startPos[1] > 35000 && joyYDir < 0) ? 0 : joyYDir;
    float joyXVal = 0;
    float joyYVal = 0;
    if (joyXDir > deadzone || joyXDir < -deadzone) {
      joyXVal = (joyXDir) / 512;
    }
    if (joyYDir > deadzone || joyYDir < -deadzone) {
      joyYVal = (joyYDir) / 512;
    }
    endPos[0] += joyXVal * joySpeed;
    endPos[1] -= joyYVal * joySpeed;
    //if(0<endPos[0] && endPos[0]<30000 && 0<endPos[1] && endPos[1]<30000)
    coolStepping(endPos[0], endPos[1]);
  }
}
