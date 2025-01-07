#include "line_sensors.h"
#include <Arduino.h>
#include "pin_config.h"

RawLineSensorData collectLineSensorData(LineSensorConfig lineSensorConfig) {
  RawLineSensorData rawData = RawLineSensorData();

  // We check if we should use this sensor
  if (lineSensorConfig.useQtrFrontRight) {
    // We read the sensor
    rawData.qtrFrontRight = IntSensorData();
    rawData.qtrFrontRight.hasData = true;
    rawData.qtrFrontRight.value = digitalRead(pin_qtr_front_left);
  } else {
    // We put in an empty value
    rawData.qtrFrontRight = IntSensorData();
    rawData.qtrFrontRight.hasData = false;
  }
  if (lineSensorConfig.useQtrFrontLeft) {
    // We read the sensor
    rawData.qtrFrontLeft = IntSensorData();
    rawData.qtrFrontLeft.hasData = true;
    rawData.qtrFrontLeft.value = digitalRead(pin_qtr_front_left);
  } else {
    // We put in an empty value
    rawData.qtrFrontLeft = IntSensorData();
    rawData.qtrFrontLeft.hasData = false;
  }

  if (lineSensorConfig.useQtrBackLeft) {
    // We read the sensor
    rawData.qtrBackLeft = IntSensorData();
    rawData.qtrBackLeft.hasData = true;
    rawData.qtrBackLeft.value = digitalRead(pin_qtr_front_left);
  } else {
    // We put in an empty value
    rawData.qtrBackLeft = IntSensorData();
    rawData.qtrBackLeft.hasData = false;
  }

  if (lineSensorConfig.useQtrBackRight) {
    // We read the sensor
    rawData.qtrBackRight = IntSensorData();
    rawData.qtrBackRight.hasData = true;
    rawData.qtrBackRight.value = digitalRead(pin_qtr_front_left);
  } else {
    // We put in an empty value
    rawData.qtrBackRight = IntSensorData();
    rawData.qtrBackRight.hasData = false;
  }

  //  rawData.sensor2 = {true, digitalRead(stg)};
  //  rawData.sensor3 = {true, digitalRead(stg_dg)};
  //  rawData.sensor4 = {true, digitalRead(centru)};
  //  rawData.sensor5 = {true, digitalRead(dr_dg)};
  //  rawData.sensor6 = {true, digitalRead(dr)};
  //  rawData.sensor7 = {true, digitalRead(dr90)};
  return rawData;
}

LinePositionResult preprocessRawLineSensorData(RawLineSensorData rawData) {
  LinePositionResult result = LinePositionResult();
  result.hasData = true;
  result.wasProcessed = true;
  result.rawData = rawData;

  int suma=0, sgain=0, s[4];

  s[1] = rawData.qtrFrontLeft.hasData ? rawData.qtrFrontLeft.value : 0;
  s[2] = rawData.qtrFrontRight.hasData ? rawData.qtrFrontRight.value : 0;
  s[3] = rawData.qtrBackLeft.hasData ? rawData.qtrBackLeft.value : 0;
  s[4] = rawData.qtrBackRight.hasData ? rawData.qtrBackRight.value : 0;
 
  for (int i = 1; i <= 4; i++) {
    suma = suma + s[i];
    sgain = sgain + s[i] * 10 * i;
  }
  if (suma == 0)
    result.currentPosition = -1;
  else {
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
