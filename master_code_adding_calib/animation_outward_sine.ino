//module Addition part
int i_nextModuleToBeAdded = 0;
// this sine represnts which module should be added next. so move from zero up to NUM_MODULES.
// the moduleAdditionSinePeriod just here to tell the radians from zero to the hill peak of sine-wave (its half-pi)
float i_moduleAdditionSinePeriod = 1.57079632679;
float i_moduleAdditionFreq = 0.9;
float i_moduleAdditionSinDt = (moduleAdditionFreq / NUM_MODULES) * (moduleAdditionSinePeriod / 1000);
float i_moduleAdditionSinVal;

//module moving part
float i_periodFreq = 0.2 ;  // hz
float i_pitchSinDt = i_periodFreq * (ONE_SIN_PERIOD / 1000);

float i_phaseOffset = PI / 60;

float i_pitchSinVal;
float i_moduleSineOffset;

void animation_outward_sine() {
  i_moduleAdditionFreq = 0.8 * randomMults[0];
  i_periodFreq = 0.2 * randomMults[1];
  i_phaseOffset = PI / (25 * randomMults[2]);
    //module Addition part
    i_moduleAdditionSinVal = abs(sin(millis() * i_moduleAdditionSinDt));  // we cant add negative modules    ?? !!
  i_nextModuleToBeAdded = i_moduleAdditionSinVal * NUM_MODULES;
  //  if(debug)Serial.printf("next module to be added: %d \n", nextModuleToBeAdded);


  //module moving part
  if (moduleIndex <= i_nextModuleToBeAdded) {
    setLaser(i_nextModuleToBeAdded, 255);
    i_moduleSineOffset = i_phaseOffset * moduleIndex;
    i_pitchSinVal = sin(millis() * i_pitchSinDt + i_moduleSineOffset);

    movePitch(moduleIndex, i_pitchSinVal);
  } else {
    setLaser(i_nextModuleToBeAdded, 0);
  }
}