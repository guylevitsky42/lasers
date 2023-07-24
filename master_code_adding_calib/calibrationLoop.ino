void checkForCalibrationMode() {
  //calibration mode
  while (millis() < 3000) {
    delay(10);
  }
  calibrationMode = false;
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  analogWriteResolution(10);  // 0 - 1023

  //if(debug)Serial.println("starting calibration checking");

  int pressCounter = 0;
  while (BUTTON_IS_PRESSED && pressCounter < 50) {
    // if(debug)Serial.println("button is pressed");
    calibrationMode = true;
    delay(10);
    pressCounter++;
  }

  if (calibrationMode) {
    // if(debug)Serial.println("servo reset");
    for (int moduleI = 0; moduleI < NUM_MODULES; moduleI++) {
      moveTheta(moduleI, 0);
      movePitch(moduleI, 1);
    }
  }
  while (BUTTON_IS_PRESSED) delay(1);
}

bool topIsInCalib = 1;
void calibrationLoop() {
  printf("now calibrating servo %d \n", servoIndex);
  int pulselen;
  setLaser(servoIndex / 2, 255);
  while (!BUTTON_IS_PRESSED) {
    potVal = ((float)analogRead(A0) / 1023) * 2 - 1;
    pulselen = moveServo(servoIndex, potVal);
    delay(10);
  }

  delay(10);
  servosCalibration[servoIndex] = pulselen;
  // printf("servo %d: %d \n", servoIndex, pulselen);
  while (BUTTON_IS_PRESSED) delay(10);  // wait for button release


  servoIndex += (servoIndex % 2 == 0) ? 3 : -1;

  if (servoIndex >= SERVO_COUNT) {
    servoIndex = 0;

    // if(debug)Serial.println("done calibration. now lets save to SD");
    delay(100);
    logServoValues();
  }
}