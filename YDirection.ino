void YDirection() {
  if (Yforward == true) {
    digitalWrite(Y_DIR_PIN, LOW);
    Serial.println("Y goes back");
  } else {
    digitalWrite(Y_DIR_PIN, HIGH);
    Serial.println("Y goes forward");
  }
  Yforward = !Yforward;
}
