void stepZ(long numOfSteps) {
  if (numOfSteps < 0) {
    digitalWrite(Z_DIR_PIN, LOW);
  } else {
    digitalWrite(Z_DIR_PIN, HIGH);
  }
  for (long i = 0; i < abs(numOfSteps); i++) {
    digitalWrite(Z_STEP_PIN, HIGH);
    delayMicroseconds(MotorDelay);
    digitalWrite(Z_STEP_PIN, LOW);
    delayMicroseconds(MotorDelay);

    if(digitalRead(Z_MIN_PIN)==LOW){
      digitalWrite(Z_DIR_PIN, HIGH);
      digitalWrite(Z_STEP_PIN, HIGH);
      delayMicroseconds(MotorDelay);
      digitalWrite(Z_STEP_PIN, LOW);
      delayMicroseconds(MotorDelay);
    }
  }
}
