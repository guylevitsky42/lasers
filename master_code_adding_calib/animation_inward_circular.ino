int pitchStart = 1;
bool firstRun = 1;
long lastTimeInwardCircularRan;


int nextModuleToBeAdded = 0;
// this sine represnts which module should be added next. so move from zero up to NUM_MODULES.
// the moduleAdditionSinePeriod just here to tell the radians from zero to the hill peak of sine-wave (its half-pi)
float moduleAdditionSinePeriod = 1.57079632679 / 2;
float moduleAdditionFreq = 40;
float moduleAdditionSinDt = (moduleAdditionFreq / NUM_MODULES) * (moduleAdditionSinePeriod / 1000);
float moduleAdditionSinVal;

float thetaGoal = 1;

void animation_inward_circular() {
  if (millis() - lastTimeInwardCircularRan > 700) {
    resetForInward();
  }

  moduleAdditionFreq = 40;
  //module Addition part
  moduleAdditionSinVal = (sin(millis() * moduleAdditionSinDt) + 1) / 2;  // we cant add negative modules    ?? !!
  nextModuleToBeAdded = moduleAdditionSinVal * NUM_MODULES;
  //  if(debug)Serial.printf("next module to be added: %d \n", nextModuleToBeAdded);


  float cosVal = cos((float)millis() / 10000.0);
  if (moduleIndex == nextModuleToBeAdded) {
    moveTheta(moduleIndex, thetaGoal);
  }
  if (nextModuleToBeAdded == NUM_MODULES || nextModuleToBeAdded == 0) {
    thetaGoal = (float)random(-100, 101) / 100;
  }

  lastTimeInwardCircularRan = millis();
}