#include "lineSensors.h"
#include <Arduino.h>
#include "pins.h"

RawLineSensorData collectLineSensorData(LineSensorConfig lineSensorConfig) {
  RawLineSensorData rawData = RawLineSensorData();

  if (lineSensorConfig.useFrontLeft) {
    rawData.frontLeft = {true, digitalRead(LineSensor_FrontLeft)};
  } else {
    rawData.frontLeft = {false, 0};
  }

  if (lineSensorConfig.useFrontRight) {
    rawData.frontRight = {true, digitalRead(LineSensor_FrontRight)};
  } else {
    rawData.frontRight = {false, 0};
  }

  if (lineSensorConfig.useBackLeft) {
    rawData.backLeft = {true, digitalRead(LineSensor_BackLeft)};
  } else {
    rawData.backLeft = {false, 0};
  }

  if (lineSensorConfig.useBackRight) {
    rawData.backRight = {true, digitalRead(LineSensor_BackRight)};
  } else {
    rawData.backRight = {false, 0};
  }

  return rawData;
}

LinePositionResult preprocessRawLineSensorData(RawLineSensorData rawData) {
  LinePositionResult result = LinePositionResult();
  result.hasData = true;
  result.wasProcessed = true;
  result.rawData = rawData;

  int suma = 0, sgain = 0, s[4];

  s[1] = rawData.frontLeft.hasData ? rawData.frontLeft.value : 0;
  s[2] = rawData.frontRight.hasData ? rawData.frontRight.value : 0;
  s[3] = rawData.backLeft.hasData ? rawData.backLeft.value : 0;
  s[4] = rawData.backRight.hasData ? rawData.backRight.value : 0;

  for (int i = 1; i <= 4; i++) {
    suma = suma + s[i];
    sgain = sgain + s[i] * 10 * i;
  }

  if (suma == 0) {
    result.currentPosition = -1;
  } else {
    result.currentPosition = sgain / suma;
  }

  return result;
}

LinePositionResult aquireLineSensorData(LineSensorConfig lineSensorConfig) {
  RawLineSensorData rawData = collectLineSensorData(lineSensorConfig);
  if (lineSensorConfig.processLineSensors) {
    return preprocessRawLineSensorData(rawData);
  } else {
    LinePositionResult result = LinePositionResult();
    result.hasData = true;
    result.wasProcessed = false;
    result.rawData = rawData;
    return result;
  }
}
