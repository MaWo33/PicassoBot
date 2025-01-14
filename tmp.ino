void tmp() {
  long circles[2][3] = {
    { 5000, 1, 0 },
    { 1000, 10, 0 },
  };
  fourier(circles, sizeof(circles) / sizeof(circles[0]));
}
