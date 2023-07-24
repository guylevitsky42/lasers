#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>
#include <SPI.h>
#include <SD.h>

// servos

#define MIN_TESET_VALUE 1000 //the minimum value will be apllied to servo at min knob value
#define MAX_TESET_VALUE 2000//the maximum value will be apllied to servo at max knob value

#define SERVO_MAX_RANGE 200

#define NUM_SERVOS_PER_PCA_BOARD 12
#define NUM_PCA_BOARDS 16
#define SERVO_COUNT 192
#define NUM_MODULES 96

Adafruit_PWMServoDriver pcaBoards[] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41),
                                       Adafruit_PWMServoDriver(0x42), Adafruit_PWMServoDriver(0x43),
                                       Adafruit_PWMServoDriver(0x44), Adafruit_PWMServoDriver(0x45),
                                       Adafruit_PWMServoDriver(0x46), Adafruit_PWMServoDriver(0x47),
                                       Adafruit_PWMServoDriver(0x48), Adafruit_PWMServoDriver(0x49),
                                       Adafruit_PWMServoDriver(0x4A), Adafruit_PWMServoDriver(0x4B),
                                       Adafruit_PWMServoDriver(0x4C), Adafruit_PWMServoDriver(0x4D),
                                       Adafruit_PWMServoDriver(0x4E), Adafruit_PWMServoDriver(0x4F)
                                      };


// lasers

#define NUM_LASER_BOARDS 32
#define LASERS_PIN D3
CRGB laserExpander[NUM_LASER_BOARDS];


// calibration board
#define BUTTON_PIN D0
#define KNOB_PIN A0
#define BUTTON_IS_PRESSED !digitalRead(BUTTON_PIN)


// math
#define ONE_SIN_PERIOD 6.28318530718



int servosCalibration[SERVO_COUNT];

void setup() {
  //  Serial.begin(115200);
  //     setup boards    //
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int boardI = 0; boardI < NUM_PCA_BOARDS; boardI++) {
    pcaBoards[boardI].begin();
    pcaBoards[boardI].setPWMFreq(50);
  }
  delay(10);

  //     setup lasers     //
  FastLED.addLeds<WS2811, LASERS_PIN, RGB>(laserExpander, NUM_LASER_BOARDS);
  FastLED.setBrightness(255);
  FastLED.clear();

  //calibration mode



  ReadSD();

  Wire.setClock(3400000);
}

int moduleIndex = 0 ;
void loop() {
  moduleIndex = moduleIndex < NUM_MODULES ? moduleIndex + 1 : 0; // handle moving trough servos

  //  float angle = ((float)analogRead(A0) / 512.0) - 1;
  //  float sinVal = sin((float)millis() / 1000.0);
  //  float cosVal = cos((float)millis() / 1000.0);
  //  //  Serial.println(angle);
  //  for (int moduleI = 0; moduleI < NUM_MODULES; moduleI++) {
  //    moveTheta(moduleI, cosVal);
  //    movePitch(moduleI, sinVal);
  //  }

  animation_outward_sine();
}
