/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

#define SERVO_COUNT 192
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  logServoValues();

  ReadSD();


}

void loop() {
  // nothing happens after setup
}
