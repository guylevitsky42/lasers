#include <LibPrintf.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x43);
//Adafruit_PWMServoDriver pwm[] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41), Adafruit_PWMServoDriver(0x42), Adafruit_PWMServoDriver(0x43), Adafruit_PWMServoDriver(0x44), Adafruit_PWMServoDriver(0x45)};
#define NUM_PANELS 6
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define MIN_TESET_VALUE 710 //the minimum value will be apllied to servo at min knob value
#define MAX_TESET_VALUE 2200//the maximum value will be apllied to servo at max knob value

#define NUM_SERVOS 16
#define BUTTON_PIN 4
#define KNOB_PIN A0
#define BUTTON_IS_PRESSED !digitalRead(BUTTON_PIN)
int pressCounter = 0;
int servoPin = 75;
int pulselen = 0;

int servosCalibration[NUM_SERVOS];
//{{1559, 1203}, {1701, 1353}, {1613, 1206}, {1867, 1527}, {1843, 1425}, {1717, 1160}, {1624, 1174}, {1814, 1350}, {1556, 1142}, {1451, 1015}, {1550, 1161}, {1575, 1155}, {1241, 823}, {1752, 1356}, {1862, 1862}}
void setup() {
  Serial.begin(115200);

    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
    delay(30);
//    printf("started %d pwm driver", i);
  


  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int panel = servoPin / 15;
  int pinInPanel =  servoPin % 15;
  printf("panel: %d servoPin: %d value: %d \n", panel, pinInPanel, pulselen);

  while (!BUTTON_IS_PRESSED) {
    pulselen = map(analogRead(KNOB_PIN), 0, 1023, MIN_TESET_VALUE, MAX_TESET_VALUE);
    //    printf("%d \n", pulselen);
    pwm.writeMicroseconds(pinInPanel, pulselen); //move the servo to pulselen position
    delay(10);
  }
  printf("servo calibration %d:   %d\n", servoPin, pulselen);
  servosCalibration[servoPin] = pulselen;
  while (BUTTON_IS_PRESSED)  delay(10);// wait for button release;
  servoPin++;
  delay(40);

  if (servoPin >= NUM_SERVOS) {
    servoPin = 0; //reset servo count if servoPin is at NUM_SERVOS
    printf("\n {{");
    for (int servo = 0; servo < NUM_SERVOS; servo++ ) {
      if (servo % 15 == 0) {
        printf("}, {");
      }
      printf("%d, ", servosCalibration[servo]);
    }
    printf("} \n");
  }

}
