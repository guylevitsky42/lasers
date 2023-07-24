int sameModuleDuration = 1000;

long moduleChangeTime = 0;
int randomIndex;
void animation_random() {
  if (moduleChangeTime < millis()) {
    if (millis() % 10000 < 2000)
      sameModuleDuration = random(50);
    else
      sameModuleDuration = random(1500);
    moduleChangeTime = millis() + sameModuleDuration;

    randomIndex = random(0, NUM_MODULES);
    // Serial.printf("again in %d now to %f", sameModuleDuration, randomValue());
    movePitch(randomIndex, randomValue());
    moveTheta(randomIndex, randomValue());
  }
}

float randomValue() {
  float value = ((float)random(200.0) / 100.0) - 1;
  return value;
}