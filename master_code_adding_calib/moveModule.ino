int moveServo(int servoIndex, float value) {
  if (value < -1) value = -1;
  else if (value > 1) value = 1;

  int pulselen = constrain(((value + 1) * 500) + 1000, 1000, 2000);
  //  if(debug)Serial.printf("moving %dth servo \n", servoIndex);

  pcaBoards[servoIndex / NUM_SERVOS_PER_PCA_BOARD].writeMicroseconds(servoIndex % NUM_SERVOS_PER_PCA_BOARD, pulselen);
  return pulselen;
}


int moveTheta(int moduleIndex, float value) {
  if (value < -1) value = -1;
  else if (value > 1) value = 1;
  int servoIndex = moduleIndex * 2;
  int pulselen = constrain(((float)(SERVO_MAX_RANGE / 2) * value) + servosCalibration[servoIndex], 800, 2300);
  pcaBoards[servoIndex / NUM_SERVOS_PER_PCA_BOARD].writeMicroseconds(servoIndex % NUM_SERVOS_PER_PCA_BOARD, pulselen);
  return pulselen;
}


int movePitch(int moduleIndex, float value) {
  if (value < -1) value = -1;
  else if (value > 1) value = 1;  // constrain

  int servoIndex = (moduleIndex * 2) + 1;
  int pulselen = constrain(servosCalibration[servoIndex] - SERVO_MAX_RANGE + (float)SERVO_MAX_RANGE * (value / 2 + 1), 800, 2300);

  pcaBoards[servoIndex / NUM_SERVOS_PER_PCA_BOARD].writeMicroseconds(servoIndex % NUM_SERVOS_PER_PCA_BOARD, pulselen);
  return pulselen;
}