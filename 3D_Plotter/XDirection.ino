void XDirection() {
  if (Xforward == true) {
    digitalWrite(X_DIR_PIN, HIGH);
    Serial.println("X goes back");
  } else {
    digitalWrite(X_DIR_PIN, LOW);
    Serial.println("X goes forward");
  }
  Xforward = !Xforward;
}
