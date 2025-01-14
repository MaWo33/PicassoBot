void linearBezier(long p0x, long p0y, long p1x, long p1y, long steps) {
  float fsteps = 1 / static_cast<float>(steps);
  for (float i = 0; i < 1; i += steps) {
    long x = (steps - i) * p0x + i * p1x;
    long y = (steps - i) * p0y + i * p1y;

    coolStepping(x, y);
  }
}
void quadraticBezier(long p0x, long p0y, long p1x, long p1y, long p2x, long p2y, long steps) {
  float fsteps = 1 / static_cast<float>(steps);
  Serial.println(p0x);
  Serial.println(p0y);
  Serial.println(p1x);
  Serial.println(p1y);
  Serial.println(p2x);
  Serial.println(p2y);
  Serial.println(fsteps);
  for (float i = 0; i <= 1; i += fsteps) {
    long l0x = (1 - i) * p0x + i * p1x;
    long l0y = (1 - i) * p0y + i * p1y;

    long l1x = (1 - i) * p1x + i * p2x;
    long l1y = (1 - i) * p1y + i * p2y;

    long x = pow((1 - i), 2) * p0x + 2 * (1 - i) * i * p1x + pow(i, 2) * p2x;
    long y = pow((1 - i), 2) * p0y + 2 * (1 - i) * i * p1y + pow(i, 2) * p2y;


    coolStepping(x, y);
  }
  Serial.println("done");
}
void cubicBezier(long p0x, long p0y, long p1x, long p1y, long p2x, long p2y, long p3x, long p3y, long steps, float scaleFactor = 1.0) {
  float fsteps = 1 / static_cast<float>(steps);
  for (float i = 0; i <= 1; i += fsteps) {
    long l0x = (1 - i) * p0x + i * p1x;
    long l0y = (1 - i) * p0y + i * p1y;

    long l1x = (1 - i) * p1x + i * p2x;
    long l1y = (1 - i) * p1y + i * p2y;

    long l2x = (1 - i) * p2x + i * p3x;
    long l2y = (1 - i) * p2y + i * p3y;

    long q0x = (1 - i) * l0x + i * l1x;
    long q0y = (1 - i) * l0y + i * l1y;

    long q1x = (1 - i) * l1x + i * l2x;
    long q1y = (1 - i) * l1y + i * l2y;

    long c0x = (1 - i) * q0x + i * q1x;
    long c0y = (1 - i) * q0y + i * q1y;

    coolStepping(c0x, c0y);
  }
  Serial.println("done");
}
