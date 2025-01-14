void calibrate() {
  stepZ(zRange);
  Serial.println("calibrating x");
  while (digitalRead(X_MIN_PIN) == HIGH) {
    stepX(-1);
  }
  Serial.println("calibrating y");
  while (digitalRead(Y_MIN_PIN) == HIGH) {
    stepY(-1);
  }
  Serial.println("calibrating z");
  while (digitalRead(Z_MIN_PIN) == HIGH) {
    stepZ(-1);
  }
  stepZ(zRange);
  Zdown = false;
  Serial.println("Calibration Done!");
  startPos[0] = 0;
  startPos[1] = 0;
  endPos[0] = 0;
  endPos[1] = 0;
  offset[0] = 0;
  offset[1] = 0;
  delay(1000);
}
