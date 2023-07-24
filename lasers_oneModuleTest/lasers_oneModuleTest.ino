#include <LibPrintf.h>


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>

#define NUM_LASER_BOARDS 2

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define THETA_MIN_PULSE 1300
#define THETA_MAX_PULSE 1600

#define PITCH_MIN_PULSE 1300
#define PITCH_MAX_PULSE 1700


CRGB lasers[NUM_LASER_BOARDS];
void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  delay(10);


  FastLED.addLeds<WS2811, 5, RGB>(lasers, NUM_LASER_BOARDS);
  FastLED.setBrightness(255);
}

int fps = 7;
int strobeInterval = 100;
long t;
void loop() {
  t = millis();
  int thetaSin = ( (cos((float)t / (1000 / fps) ) / 2 + 0.5) * (THETA_MAX_PULSE - THETA_MIN_PULSE) ) + THETA_MIN_PULSE;
  int pitchSin = ( (cos((float)t / (1000 / fps) ) / 2 + 0.5) * (PITCH_MAX_PULSE - PITCH_MIN_PULSE) ) + PITCH_MIN_PULSE;
  printf("x: %d   y: %d \n", thetaSin, pitchSin);
  pwm.writeMicroseconds(1, thetaSin);
  pwm.writeMicroseconds(2, pitchSin);


  lasersShow();
}

void lasersShow() {
  int laserVel1 = (sin((float)t / (1000 / 2)) / 2 + 0.5) * 255;
  int laserVel2 = (sin((float)t / (1000 / 20)) / 2 + 0.5) * 255;
  int laserVel3 = (sin((float)t / (1000 / 4)) / 2 + 0.5) * 255;

  lasers[0] = CRGB(laserVel1, laserVel2, laserVel3);
  lasers[1] = CRGB(laserVel2, laserVel1, laserVel3);
  FastLED.show();
}
