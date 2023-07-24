

//module Addition part

int nextModuleToBeAdded = 0;
// this sine represnts which module should be added next. so move from zero up to NUM_MODULES.
// the moduleAdditionSinePeriod just here to tell the radians from zero to the hill peak of sine-wave (its half-pi)
float moduleAdditionSinePeriod = 1.57079632679;
float moduleAdditionFreq = 0.9;
float moduleAdditionSinDt = (moduleAdditionFreq / NUM_MODULES) * (moduleAdditionSinePeriod / 1000);
float moduleAdditionSinVal;

//module moving part

float periodFreq =  0.2; // hz
float pitchSinDt = periodFreq * (ONE_SIN_PERIOD / 1000);

float phaseOffset = PI / 30;

float pitchSinVal;
float moduleSineOffset;


void animation_outward_sine_init() {
  servosOutward();
}

void animation_outward_sine() {
  //module Addition part
  moduleAdditionSinVal = abs(sin(millis() * moduleAdditionSinDt)); // we cant add negative modules    ?? !!
  nextModuleToBeAdded = moduleAdditionSinVal * NUM_MODULES;
  //  Serial.printf("next module to be added: %d \n", nextModuleToBeAdded);


  //module moving part
  if (moduleIndex <= nextModuleToBeAdded) {
    setLaser(nextModuleToBeAdded, 255);
    moduleSineOffset = phaseOffset * moduleIndex;
    pitchSinVal = sin(millis() * pitchSinDt + moduleSineOffset);

    movePitch(moduleIndex, pitchSinVal);
  }
  else {
    setLaser(nextModuleToBeAdded, 0);
  }

}
