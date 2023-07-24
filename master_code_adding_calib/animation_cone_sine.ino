double c_periodFreq = 0.05;  // hz
double c_pitchSinDt = c_periodFreq * (ONE_SIN_PERIOD / 10000);

double modulate_periodFreq = 0.005;  // hz
double modulate_pitchSinDt = modulate_periodFreq * (ONE_SIN_PERIOD / 10000);

long lastTimeConeRan = 0;


void animation_cone_sine() {
  if (millis() - lastTimeConeRan > 700) {
    resetForInward();
  }
  //sin(28x+5sin(3x))
  double sinVal = sin((randomMults[0] + 5) * ((double)millis() / 10000) * 0.6 + 6 * sin(((double)millis() / 10000) * 0.2));
  // Serial.println(sinVal);
  movePitch(moduleIndex, sinVal);

  lastTimeConeRan = millis();
}


void resetForInward() {
  for (int module = 0; module < NUM_MODULES; module++) {
    movePitch(module, 1);
    moveTheta(module, 0);
    delay(1);
  }
}