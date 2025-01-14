void Potenz(long exponent, long streckfaktor) {
  for (long j = 0; j <= 4000; j++) {
    long tempx = 10 * j;
    long tempy = 0.001 * streckfaktor * pow(j, exponent);

    if (tempy > 20000) {
      Serial.println("Y überschritten" + String(endPos[1]));
      break;
    }
    coolStepping(tempx, tempy);
  }
  Serial.println("fertig");
}
