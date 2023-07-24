void moveServo(int servoNum, int pulselen) {
  pcaBoards[servoNum / NUM_SERVOS_PER_PCA_BOARD].writeMicroseconds(servoNum % NUM_SERVOS_PER_PCA_BOARD , pulselen);
}


void moveTheta(int moduleIndex, float value) {
  if (value < -1) value = -1;
  else if (value > 1) value = 1;
  int servoIndex = moduleIndex * 2;
  int pulselen = ((SERVO_MAX_RANGE / 2) * value) + servosCalibration[servoIndex];
  pcaBoards[servoIndex / NUM_SERVOS_PER_PCA_BOARD].writeMicroseconds(servoIndex % NUM_SERVOS_PER_PCA_BOARD , constrain(pulselen, 800, 2300));
}


void movePitch(int moduleIndex, float value) {
  if (value < -1) value = -1;
  else if (value > 1) value = 1; // constrain

  int servoIndex = ( moduleIndex * 2 ) + 1;
  int pulselen = ((float)(SERVO_MAX_RANGE / 2) * value) + servosCalibration[servoIndex];

  pcaBoards[servoIndex / NUM_SERVOS_PER_PCA_BOARD].writeMicroseconds(servoIndex % NUM_SERVOS_PER_PCA_BOARD , constrain(pulselen, 800, 2300));
}
