void fourier(long circles[][3], int size) {
  for (long j = 0; j <= 360; j++) {
    long x = 0;
    long y = 0;
    for (int i = 0; i < size; i++) {
      Serial.println(circles[i][0]);
      x += circles[i][0] * -cos(j * -M_PI / 180 * circles[i][1] + circles[i][2] * -M_PI / 180);
      y += circles[i][0] * -sin(j * -M_PI / 180 * circles[i][1] + circles[i][2] * -M_PI / 180);
    }
    coolStepping(x + 10000, y + 10000);
  }
}
