#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>

#define NUM_LASER_BOARDS 4
CRGB laserExpander[NUM_LASER_BOARDS];


Adafruit_PWMServoDriver pcaBoards[] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41)};
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define MIN_TESET_VALUE 1200 //the minimum value will be apllied to servo at min knob value
#define MAX_TESET_VALUE 1800//the maximum value will be apllied to servo at max knob value


#define NUM_SERVOS_PER_PCA_BOARD 12
#define NUM_PCA_BOARD 2
#define SERVO_COUNT 24
#define BUTTON_PIN D3
#define KNOB_PIN A0
#define BUTTON_IS_PRESSED !digitalRead(BUTTON_PIN)

int pressCounter = 0;
int servoPin = 0;
int pulselen = 0;

int servosCalibration[SERVO_COUNT];
//{{1559, 1203}, {1701, 1353}, {1613, 1206}, {1867, 1527}, {1843, 1425}, {1717, 1160}, {1624, 1174}, {1814, 1350}, {1556, 1142}, {1451, 1015}, {1550, 1161}, {1575, 1155}, {1241, 823}, {1752, 1356}, {1862, 1862}}
void setup() {
  Serial.begin(115200);
  pcaBoards[0].begin();
  pcaBoards[1].begin();
  //pwm 4096 - 12 bits of resolution
  //  pwm.setOscillatorFrequency(27000000);
  pcaBoards[0].setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  pcaBoards[1].setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  FastLED.addLeds<WS2811, D6, RGB>(laserExpander, NUM_LASER_BOARDS);
  FastLED.setBrightness(255);

  for (int laser = 0; laser < 12; laser++) {
    setLaser(laser, 255);
//    delay(1000);
  }
//  delay(7000);
//  for (int laser = 0; laser < 12; laser++) {
//    setLaser(laser, 0);
//    delay(200);
//  }

}

void loop() {
  //  if (servoPin > NUM_SERVOS_PER_PCA_BOARD) {
  //    int pcaBoardIndex = (servoPin > NUM_SERVOS_PER_PCA_BOARD)
  //  }

  while (!BUTTON_IS_PRESSED) {
    pulselen = map(analogRead(KNOB_PIN), 0, 1023, MIN_TESET_VALUE, MAX_TESET_VALUE);
    //    printf("%d \n", pulselen);
    moveServo(servoPin, pulselen); //move the servo to pulselen position
    delay(10);
  }

  delay(10);
  printf("servo %d: %d \n", servoPin, pulselen);
  servosCalibration[servoPin] = pulselen;
  while (BUTTON_IS_PRESSED) delay(10); // wait for button release;


  servoPin += 1;
  if (servoPin >= SERVO_COUNT) {
    servoPin = 0; //reset servo count if servoPin is at NUM_SERVOS
    printf("{");
    for (int servo = 0; servo < SERVO_COUNT; servo++ ) {
      Serial.print(servosCalibration[servo]);
      Serial.print(", ");
      delay(1);
    }
    printf("}");
  }


}


void setLaser(int index, int brigthness) {
  int expenderIndex = index / 3;
  int modulePin = (index % 3) ;

  CRGB color = laserExpander[expenderIndex];

  laserExpander[expenderIndex] = CRGB(modulePin == 0 ? brigthness : color.red, modulePin == 1 ? brigthness : color.green, modulePin == 2 ? brigthness : color.blue);

  FastLED.show();
}

void moveServo(int servoNum, int pose) {
  pcaBoards[servoNum / NUM_SERVOS_PER_PCA_BOARD].writeMicroseconds(servoNum % NUM_SERVOS_PER_PCA_BOARD , pulselen);
}
