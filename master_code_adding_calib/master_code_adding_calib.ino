#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>
#include <SPI.h>
#include <SD.h>

// servos
//
//#define MIN_TESET_VALUE 1000 //the minimum value will be apllied to servo at min knob value
//#define MAX_TESET_VALUE 2000//the maximum value will be apllied to servo at max knob value

#define SERVO_MAX_RANGE 500
#define SERVO_CALIBRATION_MAX_RANGE 1500

#define NUM_SERVOS_PER_PCA_BOARD 12
#define NUM_PCA_BOARDS 16
#define SERVO_COUNT 192
#define NUM_MODULES 96
int timeBetweenAnimations = 1000;

Adafruit_PWMServoDriver pcaBoards[] = { Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41),
                                        Adafruit_PWMServoDriver(0x42), Adafruit_PWMServoDriver(0x43),
                                        Adafruit_PWMServoDriver(0x44), Adafruit_PWMServoDriver(0x45),
                                        Adafruit_PWMServoDriver(0x46), Adafruit_PWMServoDriver(0x47),
                                        Adafruit_PWMServoDriver(0x48), Adafruit_PWMServoDriver(0x49),
                                        Adafruit_PWMServoDriver(0x4A), Adafruit_PWMServoDriver(0x4B),
                                        Adafruit_PWMServoDriver(0x4C), Adafruit_PWMServoDriver(0x4D),
                                        Adafruit_PWMServoDriver(0x4E), Adafruit_PWMServoDriver(0x4F) };


// lasers
#define NUM_LASER_BOARDS 32
#define LASERS_PIN D0
CRGB laserExpander[NUM_LASER_BOARDS];


// calibration board
#define BUTTON_PIN D3
#define KNOB_PIN A0
#define BUTTON_IS_PRESSED !digitalRead(BUTTON_PIN)


// math
#define ONE_SIN_PERIOD 6.28318530718


bool calibrationMode = false;
int servosCalibration[SERVO_COUNT];

int moduleIndex = 0;
int servoIndex = 1;
float potVal;
bool calibratingPitch = 1;
int iterateIndex = 0;
int debug = 0;

void setup() {
  // Serial.begin(115200);
  // if (debug) Serial.println("starting");
  //     setup boards    //

  for (int boardI = 0; boardI < NUM_PCA_BOARDS; boardI++) {
    pcaBoards[boardI].begin();
    pcaBoards[boardI].setPWMFreq(50);
  }
  delay(10);

  //     setup lasers     //
  FastLED.addLeds<WS2811, LASERS_PIN, BGR>(laserExpander, NUM_LASER_BOARDS);
  FastLED.setBrightness(255);
  fill_solid(laserExpander, NUM_LASER_BOARDS, CRGB(255, 255, 255));
  FastLED.show();

  ReadSD();
  Wire.setClock(3400000);
  checkForCalibrationMode();

  if (calibrationMode)
    // if (debug) Serial.println("setup ended in calib mode");
    // else if (debug) Serial.println("setup ended in animation mode");

    resetForInward();
  randomSeed(millis());
}

const int NUM_ANIMATIONS = 4;
typedef void (*animationList[])();
animationList animationsList = { animation_outward_sine, animation_cone_sine, animation_inward_circular, animation_random };
int currentAnimationINdex = 0;
int animationIndex = 0;
long timeToChangeAnimation;

long sameAnimationDuration = 0;
long animationChangeTime = 0;

float randomMults[] = { 0.0, 0.0, 0.0 };
void loop() {
  if (calibrationMode) {
    calibrationLoop();
  } else {
    moduleIndex++;  // handle moving trough servos
    if (moduleIndex >= NUM_MODULES) moduleIndex = 0;

    if (animationChangeTime < millis()) {
      randomMults[0] = randomMultGenerate();
      randomMults[1] = randomMultGenerate();
      randomMults[2] = randomMultGenerate();

      sameAnimationDuration = random(45000, 60000 * 3);
      animationChangeTime = millis() + sameAnimationDuration;
      animationIndex++;
      if (animationIndex >= NUM_ANIMATIONS) {
        animationIndex = 0;
        resetForInward();
      }

      delay(random(2000, 8000));
    }

    animationsList[animationIndex]();
  }
}

float randomMultGenerate() {
  return (float)random(60, 100) / 100.0;
}