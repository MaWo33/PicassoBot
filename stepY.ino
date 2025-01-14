void stepY(long numOfSteps) {
  if (numOfSteps < 0) {
    digitalWrite(Y_DIR_PIN, LOW);
  } else {
    digitalWrite(Y_DIR_PIN, HIGH);
  }
  for (long i = 0; i < abs(numOfSteps); i++) {
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(MotorDelay);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(MotorDelay);
  }
}
