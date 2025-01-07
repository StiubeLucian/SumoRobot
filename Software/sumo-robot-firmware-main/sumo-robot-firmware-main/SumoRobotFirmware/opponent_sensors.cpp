#include "opponent_sensors.h"
#include <Arduino.h>
#include "pin_config.h"

RawOpponentSensorData collectOpponentSensorData(OpponentSensorConfig opponentSensorConfig) {
  RawOpponentSensorData rawData = RawOpponentSensorData();

  // We check if we should use this sensor
  if (opponentSensorConfig.useLeft90Sensor) {
    // We read the sensor
    rawData.left90Sensor = IntSensorData();
    rawData.left90Sensor.hasData = true;
    rawData.left90Sensor.value = digitalRead(pin_opponent_left90);
  } else {
    // We put in an empty value
    rawData.left90Sensor = IntSensorData();
    rawData.left90Sensor.hasData = false;
  }

  // We check if we should use this sensor
  if (opponentSensorConfig.useLeftSensor) {
    // We read the sensor
    rawData.leftSensor = IntSensorData();
    rawData.leftSensor.hasData = true;
    rawData.leftSensor.value = digitalRead(pin_opponent_left);
  } else {
    // We put in an empty value
    rawData.leftSensor = IntSensorData();
    rawData.leftSensor.hasData = false;
  }

  // We check if we should use this sensor
  if (opponentSensorConfig.useLeftCenterSensor) {
    rawData.leftCenterSensor = IntSensorData();
    rawData.leftCenterSensor.hasData = true;
    rawData.leftCenterSensor.value = digitalRead(pin_opponent_left_center);
  } else {
    rawData.leftCenterSensor = IntSensorData();
    rawData.leftCenterSensor.hasData = false;
  }

  // We check if we should use this sensor
  if (opponentSensorConfig.useCenterSensor) {
    rawData.centerSensor = IntSensorData();
    rawData.centerSensor.hasData = true;
    rawData.centerSensor.value = digitalRead(pin_opponent_center);
  } else {
    rawData.centerSensor = IntSensorData();
    rawData.centerSensor.hasData = false;
  }

  // We check if we should use this sensor
  if (opponentSensorConfig.useRightCenterSensor) {
    rawData.rightCenterSensor = IntSensorData();
    rawData.rightCenterSensor.hasData = true;
    rawData.rightCenterSensor.value = digitalRead(pin_opponent_right_center);
  } else {
    rawData.rightCenterSensor = IntSensorData();
    rawData.rightCenterSensor.hasData = false;
  }

  // We check if we should use this sensor
  if (opponentSensorConfig.useRightSensor) {
    rawData.rightSensor = IntSensorData();
    rawData.rightSensor.hasData = true;
    rawData.rightSensor.value = digitalRead(pin_opponent_right);
  } else {
    rawData.rightSensor = IntSensorData();
    rawData.rightSensor.hasData = false;
  }

  if (opponentSensorConfig.useRight90Sensor) {
    rawData.right90Sensor = IntSensorData();
    rawData.right90Sensor.hasData = true;
    rawData.right90Sensor.value = digitalRead(pin_opponent_right90);
  } else {
    rawData.right90Sensor = IntSensorData();
    rawData.right90Sensor.hasData = false;
  }

  //  rawData.sensor2 = {true, digitalRead(stg)};
  //  rawData.sensor3 = {true, digitalRead(stg_dg)};
  //  rawData.sensor4 = {true, digitalRead(centru)};
  //  rawData.sensor5 = {true, digitalRead(dr_dg)};
  //  rawData.sensor6 = {true, digitalRead(dr)};
  //  rawData.sensor7 = {true, digitalRead(dr90)};
  return rawData;
}

OpponentPositionResult preprocessRawOpponentSensorData(RawOpponentSensorData rawData) {
  OpponentPositionResult result = OpponentPositionResult();
  result.hasData = true;
  result.wasProcessed = true;
  result.rawData = rawData;

  int suma=0, sgain=0, s[8];

  s[1] = rawData.left90Sensor.hasData ? rawData.left90Sensor.value : 0;
  s[2] = rawData.leftSensor.hasData ? rawData.leftSensor.value : 0;
  s[3] = rawData.leftCenterSensor.hasData ? rawData.leftCenterSensor.value : 0;
  s[4] = rawData.centerSensor.hasData ? rawData.centerSensor.value : 0;
  s[5] = rawData.rightCenterSensor.hasData ? rawData.rightCenterSensor.value : 0;
  s[6] = rawData.rightSensor.hasData ? rawData.rightSensor.value : 0;
  s[7] = rawData.right90Sensor.hasData ? rawData.right90Sensor.value : 0;

  for (int i = 1; i <= 7; i++) {
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

OpponentPositionResult aquireOpponentSensorData(OpponentSensorConfig opponentSensorConfig) {
  RawOpponentSensorData rawData = collectOpponentSensorData(opponentSensorConfig);
  if (opponentSensorConfig.processOpponentSensors) {
    return preprocessRawOpponentSensorData(rawData);
  } else {
    OpponentPositionResult result = OpponentPositionResult();
    result.hasData = true;
    result.wasProcessed = false;
    result.rawData = rawData;
    return result;
  }
}
