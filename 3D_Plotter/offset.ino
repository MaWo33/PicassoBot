void setOffset(long x, long y) {
  offset[0] -= x * globalSizeMultiplier;
  offset[1] -= y * globalSizeMultiplier;
  startPos[0] -= x * globalSizeMultiplier;
  startPos[1] -= y * globalSizeMultiplier;
}
