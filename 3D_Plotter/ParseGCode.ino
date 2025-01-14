long globalDepthMultiplier;
void uncoolStep(long endX, long endY, bool raise) {
  if (raise == true)
    upZ();
  if (maxPos[0][0] + offset[0] <= endX && maxPos[0][1] + offset[0] >= endX)
    chaseX = endX * globalSizeMultiplier;
  if (maxPos[1][0] + offset[1] <= endY && maxPos[1][1] + offset[1] >= endY)
    chaseY = endY * globalSizeMultiplier;
  stepX(chaseX - startPos[0]);
  stepY(chaseY - startPos[1]);
  startPos[0] = endX;
  startPos[1] = endY;

  downZ();
}
void listGC(){
  File file;
  File root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("GELISTET");
}
void parseGC(String gcFile) {
  downZ();


  File file = SD.open(gcFile, FILE_READ);
  if (file) {
    while (file.available()) {
      String line = file.readStringUntil('\n');
      // Serial.println(line);
      bool raise = false;
      if (line.charAt(1) == '0') {
        raise = true;
      }
      // Serial.println("this is one line");
      // if(line.charAt(1)!='1')
      //   continue;

      float x_part = getParameterValue(line, 'X');
      int x = (x_part != 0.0f) ? x_part : startPos[0];

      float y_part = getParameterValue(line, 'Y');
      int y = (y_part != 0.0f) ? y_part : startPos[1];

      float z_part = getParameterValue(line, 'Z');
      int z = (z_part != 0.0f) ? z_part : startPos[2];

      // Serial.print("x_part:");
      // Serial.println(x_part);

      // Serial.print("Got this for x, y, z:");
      // Serial.println(x);
      // Serial.println(y);
      // Serial.println(z);

      coolStepping(x, y, raise);
    }
  }
}

float getParameterValue(String gcode, char parameter) {
  int index = gcode.indexOf(parameter);  // Find the position of the parameter
  if (index == -1) {
    return NAN;  // Return NaN if the parameter is not found
  }

  int startIndex = index + 1;                     // Start after the parameter character
  int endIndex = gcode.indexOf(' ', startIndex);  // Find the next space or end of string
  if (endIndex == -1) {
    endIndex = gcode.length();  // If no space, use the end of the string
  }

  String valueString = gcode.substring(startIndex, endIndex);  // Extract the value as a substring
  return valueString.toFloat();                                // Convert the substring to a float and return
}
void printDirectory(File dir, int numTabs) {
  int listIndex = 0;
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    gcodes[listIndex]=entry.name();
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
    listIndex++;
  }
  for(int i=0; i<sizeof(gcodes)/sizeof(gcodes[0]);i++){
    Serial.print(gcodes[i]);
  }
}
