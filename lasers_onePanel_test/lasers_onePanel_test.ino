#include <LibPrintf.h>


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>

#define NUM_LASER_BOARDS 4

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver servoDrivers[] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41)};

#define THETA_MIN_PULSE 1300
#define THETA_MAX_PULSE 1600

#define PITCH_MIN_PULSE 1300
#define PITCH_MAX_PULSE 1700


CRGB laserExpander[NUM_LASER_BOARDS];
void setup() {
  Serial.begin(115200);
  Serial.println("8 channel Servo test!");

  servoDrivers[0].begin();
  servoDrivers[0].setOscillatorFrequency(27000000);
  servoDrivers[0].setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  servoDrivers[1].begin();
  servoDrivers[1].setOscillatorFrequency(27000000);
  servoDrivers[1].setPWMFreq(50);  // Analog servos run at ~50 Hz updates
  delay(10);


  FastLED.addLeds<WS2811, 5, RGB>(laserExpander, NUM_LASER_BOARDS);
  FastLED.setBrightness(255);
}

int fps = 3;
int strobeInterval = 100;
long t;
int laserOn = 0;


void loop() {
  t = millis();
  int thetaSin = ( (sin((float)t / (1000 / fps) ) / 2 + 0.5) * (THETA_MAX_PULSE - THETA_MIN_PULSE) ) + THETA_MIN_PULSE;
  int pitchSin = ( (cos((float)t / (1000 / fps) ) / 2 + 0.5) * (PITCH_MAX_PULSE - PITCH_MIN_PULSE) ) + PITCH_MIN_PULSE;
  printf("x: %d   y: %d \n", thetaSin, pitchSin);

  //  printf("%d \n", laserOn);

  //  laserOn = (millis() / 20) % 12;

  //  if (laserOn >= 12)laserOn = 0;

  for (int moduleItr = 0; moduleItr < 12; moduleItr++) {
    moveModule(moduleItr, thetaSin , pitchSin);
    laserOn = moduleItr;
    if (laserOn == moduleItr)
      setLaser(moduleItr, thetaSin-THETA_MIN_PULSE);
    else
      setLaser(moduleItr, 0);
  }
}

// moduleIndex is a polaric value in the global scope of modules (not per panel)
void moveModule(int moduleIndex, int theta, int pitch ) {

  int servoDriverIndex = moduleIndex / 6;
  int modulePin1 = ((moduleIndex % 6)) * 2;
  servoDrivers[servoDriverIndex].writeMicroseconds(modulePin1, theta);
  servoDrivers[servoDriverIndex].writeMicroseconds(modulePin1 + 1, pitch);

}


void setLaser(int index, int brigthness) {
  int expenderIndex = index / 3;
  int modulePin = (index % 3) ;

  CRGB color = laserExpander[expenderIndex];

  laserExpander[expenderIndex] = CRGB(modulePin == 0 ? brigthness : color.red, modulePin == 1 ? brigthness : color.green, modulePin == 2 ? brigthness : color.blue);

  FastLED.show();
}
