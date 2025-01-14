void circleCool(long radius, long circleX, long circleY, int iterations, int circleStart) {
  int cirdir = 1;
  if (iterations < 0) {
    iterations *= -1;
    cirdir = -1;
    circleStart = 360 - circleStart;
  }
  for (long j = circleStart; j <= iterations + circleStart; j++) {
    coolStepping(radius * -cos(j * -M_PI / 180) + circleX, radius * -sin(j * -M_PI / 180) * cirdir + circleY);
  }
}
