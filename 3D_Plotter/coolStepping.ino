void coolStepping(long endX, long endY, bool flying_move) {
  if (flying_move)
    upZ();
  if (maxPos[0][0] + offset[0] <= endX && maxPos[0][1] + offset[0] >= endX)
    chaseX = endX * globalSizeMultiplier;
  if (maxPos[1][0] + offset[1] <= endY && maxPos[1][1] + offset[1] >= endY)
    chaseY = endY * globalSizeMultiplier;
  long double l = sqrt(sq(chaseX - startPos[0]) + sq(chaseY - startPos[1]));
  altePos[0] = startPos[0];
  altePos[1] = startPos[1];
  long x_steps;
  long y_steps;
  for (double i = 0; i < 1; i = i + double(1 / l)) {
    neuePos[0] = round(startPos[0] + i * (chaseX - startPos[0]));
    neuePos[1] = round(startPos[1] + i * (chaseY - startPos[1]));
    x_steps = neuePos[0] - altePos[0];
    y_steps = neuePos[1] - altePos[1];

    stepX(x_steps);
    stepY(y_steps);

    altePos[0] = neuePos[0];
    altePos[1] = neuePos[1];
  }
  startPos[0] = chaseX;
  startPos[1] = chaseY;
  if (flying_move)
    downZ();
}
