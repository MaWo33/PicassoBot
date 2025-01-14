void butterfly(long scale, long x, long y) {
  for (double t = 0; t <= 12 * M_E; t += 0.05) {
    long x = scale * sin(t) * (pow(M_E, cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12), 5)) + x;
    long y = scale * cos(t) * (pow(M_E, cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12), 5)) + y;
    coolStepping(x, y);
  }
}
