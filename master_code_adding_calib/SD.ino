//int servosCalibration[] = {1521, 1551, 1535, 1535, 1404, 1540, 1590, 1628, 1462, 1560, 1484, 1468, 1510, 1522, 1568, 1584, 1645, 1485, 1508, 1559, 1639, 1571, 1580, 1610, 1482, 1608, 1429, 1568, 1437, 1612, 1535, 1584, 1405, 1475, 1524, 1461, 1429, 1549, 1485, 1518, 1503, 1557, 1472, 1500, 1420, 1612, 1436, 1454, 1674, 1508, 1444, 1448, 1570, 1495, 1463, 1506, 1647, 1594, 1519, 1519, 1604, 1542, 1530, 1432, 1651, 1545, 1486, 1633, 1508, 1625, 1552, 1602, 1607, 1673, 1562, 1543, 1615, 1551, 1492, 1634, 1738, 1550, 1591, 1525, 1616, 1581, 1494, 1666, 1655, 1634, 1524, 1496, 1566, 1541, 1566, 1527, 1615, 1561, 1405, 1733, 1549, 1540, 1673, 1545, 1717, 1596, 1605, 1544, 1552, 1426, 1554, 1500, 1533, 1515, 1534, 1580, 1557, 1521, 1513, 1607, 1567, 1596, 1504, 1310, 1383, 1504, 1477, 1448, 1356, 1490, 1519, 1249, 1456, 1484, 1613, 1508, 1470, 1506, 1590, 1562, 1552, 1574, 1582, 1535, 1519, 1559, 1508, 1581, 1584, 1514, 1524, 1521, 1595, 1538, 1514, 1239, 1421, 1650, 1463, 1533, 1501, 1670, 1490, 1483, 1573, 1610, 1515, 1517, 1507, 1469, 1441, 1523, 1435, 1482, 1469, 1428, 1503, 1492, 1461, 1328, 1543, 1524, 1465, 1561, 1452, 1517, 1523, 1524, 1575, 1554, 1688, 1506};
void ReadSD() {
  File servoValuesFile;
  int index = 0;

  if (debug) Serial.print("Initializing SD card...");

  if (!SD.begin(D4)) {
    if (debug) Serial.println("SD initialization failed!");
    return;
  }
  if (debug) Serial.println("initialization done.");


  servoValuesFile = SD.open("servos.txt");
  if (servoValuesFile) {
    if (debug) Serial.println("servos.txt:");

    // read from the file until there's nothing else in it:
    while (servoValuesFile.available()) {
      if (index <= SERVO_COUNT) {
        int servoValue = servoValuesFile.readStringUntil(',').toInt();
        servosCalibration[index] = servoValue;
        index += 1;


        if (debug) Serial.printf("%d,", servoValue);
      } else {
        if (debug) Serial.println("done reading.");
        break;
      }
    }

    // close the file:
    servoValuesFile.close();
    if (debug) Serial.println("closed file.");
  } else {
    // if the file didn't open, print an error:
    if (debug) Serial.println("error opening test.txt");
  }
}


void logServoValues() {
  File servoValuesFile;

  if (debug) Serial.print("Initializing SD card...");

  if (!SD.begin(D4)) {
    if (debug) Serial.println("SD initialization failed!");
    return;
  }
  if (debug) Serial.println("initialization done.");

  if (debug) Serial.println("deleting old file!!!.");

  SD.remove("servos.txt");
  servoValuesFile = SD.open("servos.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (servoValuesFile) {
    if (debug) Serial.print("Writing to test.txt...");
    String calibString = "";
    for (int servoI = 0; servoI < SERVO_COUNT; servoI++) {
      calibString += String(servosCalibration[servoI]) + ",";
      //      calibString += "0,"; // debug fill 0s
    }
    if (debug) Serial.print(calibString);
    servoValuesFile.print(calibString);
    // close the file:
    servoValuesFile.close();
    if (debug) Serial.println("done writing.");
  } else {
    // if the file didn't open, print an error:
    if (debug) Serial.println("error opening servos.txt");
  }
}