int joySelectOption;
int oldJoySelectOption = 8;
int joySelectPage;
bool confirmed;
bool JSPress;
String JSType = "default";

void joySelect() {
  while (true) {
    if (Serial.available() != 0 || Serial2.available() != 0) { break; } //breaks for Text Input
    float joyXDir = (analogRead(JOY_X) - 512) * -1;                     //JoyStickInput
    float joyYDir = (analogRead(JOY_Y) - 512) * -1;
    float joySize = sqrt(sq(joyXDir) + sq(joyYDir));
    if (joySize > 512) {
      joyXDir = 512 * (joyXDir / joySize);
      joyYDir = 512 * (joyYDir / joySize);
    }

    if (joySelectPage < 0) joySelectPage = 2; //Pages
    if (joySelectPage > 2) joySelectPage = 0;
    
    if (abs(joyXDir) > 100 || abs(joyYDir) > 100) {
      float JoyAngle = atan2(-joyYDir, -joyXDir) / 3.14159 * 180 + 180;
      if (JoyAngle > 22.5 + 45 * 0 && JoyAngle <= 67.5 + 45 * 0) joySelectOption = 2;       //RadialOption
      else if (JoyAngle > 22.5 + 45 * 1 && JoyAngle <= 67.5 + 45 * 1) joySelectOption = -1;
      else if (JoyAngle > 22.5 + 45 * 2 && JoyAngle <= 67.5 + 45 * 2) joySelectOption = 3;
      else if (JoyAngle > 22.5 + 45 * 3 && JoyAngle <= 67.5 + 45 * 3) joySelectOption = 4;
      else if (JoyAngle > 22.5 + 45 * 4 && JoyAngle <= 67.5 + 45 * 4) joySelectOption = 5;
      else if (JoyAngle > 22.5 + 45 * 5 && JoyAngle <= 67.5 + 45 * 5) joySelectOption = -3;
      else if (JoyAngle > 22.5 + 45 * 6 && JoyAngle <= 67.5 + 45 * 6) joySelectOption = 6;
      else joySelectOption = 1;
    } 
    else joySelectOption = 0;
    
    if (oldJoySelectOption != joySelectOption || JSPress == true) {
      if(JSPress) cycleMotor();
      oldJoySelectOption = joySelectOption;
      lcd.clear();
      if(JSType=="default"){
          lcd.setCursor(1, 0);
          lcd.print("Schnellauswahl");
      }
      else if(JSType=="drawShape"){
          lcd.setCursor(3, 0);
          lcd.print("Formen");
      }
      else if(JSType=="gcode"){
          lcd.setCursor(4, 0);
          lcd.print("gCode");
      }
      
      lcd.setCursor(0, 1);
      if(joySelectOption > 0) joySelectOption += joySelectPage *6;
      else if(joySelectOption < 0)
        switch (joySelectOption){
          case -1:
            lcd.print("Naechste Seite >");
            if(JSPress)joySelectPage += 1;
            break;
          case -3:
            lcd.print("< Naechste Seite");
            if(JSPress)joySelectPage -= 1;
            break;
          default:
            lcd.print("Unknown Error");
        }
      if(JSType == "default"){
        switch (joySelectOption) {
          case 0:
            lcd.print("Seite " + String(joySelectPage + 1));
            break;
          case 1:
            lcd.print("GCode");
            if(JSPress) JSType = "gcode";
            break;
          case 2:
            lcd.print("Form Zeichnen");
            if(JSPress) JSType = "drawShape";
            break;
          case 3:
            lcd.print("Size reset");
            if(JSPress) globalSizeMultiplier = 1;
            break;
          case 4:
            lcd.print("Calibrate");
            if(JSPress) calibrate();
            break;
          case 5:
            lcd.print("Toggle Z");
            if(JSPress) toggleZ();
            break;
          case 6:
            lcd.print("JoyStick");
            if(JSPress) joy();
            break;
          default:
            lcd.print("-Unbelegt-");
            break;
        }
      }
      else if(JSType == "drawShape"){
        if(JSPress)downZ();
        switch (joySelectOption) {
          case 0:
            lcd.print("Seite " + String(joySelectPage + 1));
            if(JSPress) JSType = "default";
            break;
          case 1:
            lcd.print("WDG");
            if(JSPress)sq_wdg();
            break;
          case 2:
            lcd.print("Cube");
            if(JSPress)sq_threeD();
            break;
          case 3:
            lcd.print("Pokéball");
            if(JSPress)sq_pokeball();
            break;
          default:
            lcd.print("-Unbelegt-");
            break;
        }
        if(JSPress){
          upZ();
          JSType = "default";
        }
      }
      else if(JSType=="gcode"){
        if(joySelectOption == 0){
          lcd.print("Seite " + String(joySelectPage + 1));
          if(JSPress) JSType = "default";
        }
        else if(joySelectOption == 1){
          lcd.print("Get gcodes");
          if(JSPress) listGC();
        }
        else if(joySelectOption > 1 && joySelectOption <= 1000){
          lcd.print(gcodes[joySelectOption -2]);
          if(JSPress) parseGC(gcodes[joySelectOption -2]);
        }
      }
    }
    if(JSPress) cycleMotor();
    JSPress = false;
    if (digitalRead(JOY_B) && confirmed != true) { //Press
      confirmed = true;
    }
    else if (!digitalRead(JOY_B) && confirmed == true){
      confirmed = false;
      JSPress = true;
    }
  }
}