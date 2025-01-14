void toggleZ() {
  Zdown = !Zdown;
  if (Zdown) stepZ(-zRange);
  if (!Zdown) stepZ(zRange);
}
void upZ() {
  if (Zdown) {
    stepZ(zRange);
    Zdown = false;
  }
}
void downZ() {
  if (!Zdown) {
    stepZ(-zRange);
    Zdown = true;
  }
}
void forceZ() {
  stepZ(-zRange);
}
