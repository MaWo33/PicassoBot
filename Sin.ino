long sinX;
long sinY;
void SinusCool(long frequenz, long amplitude, long laenge, long theta) {
  for (long j = 0; j <= laenge; j += 10) {
    sinX = j;
    sinY = amplitude * sin(2 * M_PI / laenge * frequenz * j);
    //Serial.println(String(endPos[0]) + "  |  " + String(endPos[1]));
    long x = (sinX * cos(theta * M_PI / 180) - sinY * sin(theta * M_PI / 180));
    long y = (sinX * sin(theta * M_PI / 180) + sinY * cos(theta * M_PI / 180));
    coolStepping(x, y);
  }
}
