void stepX(long numOfSteps) {
  if (numOfSteps < 0) {
    digitalWrite(X_DIR_PIN, HIGH);
  } else {
    digitalWrite(X_DIR_PIN, LOW);
  }
  for (long i = 0; i < abs(numOfSteps); i++) {
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(MotorDelay);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(MotorDelay);
  }
}
