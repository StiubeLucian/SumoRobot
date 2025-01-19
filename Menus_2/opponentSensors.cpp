#include "opponentSensors.h"
#include <Arduino.h>
#include "pins.h"

RawOpponentSensorData collectOpponentSensorData(OpponentSensorConfig opponentSensorConfig) {
  RawOpponentSensorData rawData = RawOpponentSensorData();

  if (opponentSensorConfig.useSensor1) {
    rawData.sensor1 = {true, digitalRead(Sensor1_in)};
  } else {
    rawData.sensor1 = {false, 0};
  }

  if (opponentSensorConfig.useSensor2) {
    rawData.sensor2 = {true, digitalRead(Sensor2_in)};
  } else {
    rawData.sensor2 = {false, 0};
  }

  if (opponentSensorConfig.useSensor3) {
    rawData.sensor3 = {true, digitalRead(Sensor3_in)};
  } else {
    rawData.sensor3 = {false, 0};
  }

  if (opponentSensorConfig.useSensor4) {
    rawData.sensor4 = {true, digitalRead(Sensor4_in)};
  } else {
    rawData.sensor4 = {false, 0};
  }

  if (opponentSensorConfig.useSensor5) {
    rawData.sensor5 = {true, digitalRead(Sensor5_in)};
  } else {
    rawData.sensor5 = {false, 0};
  }

  if (opponentSensorConfig.useSensor6) {
    rawData.sensor6 = {true, digitalRead(Sensor6_in)};
  } else {
    rawData.sensor6 = {false, 0};
  }

  if (opponentSensorConfig.useSensor7) {
    rawData.sensor7 = {true, digitalRead(Sensor7_in)};
  } else {
    rawData.sensor7 = {false, 0};
  }

  if (opponentSensorConfig.useSensor8) {
    rawData.sensor8 = {true, digitalRead(Sensor8_in)};
  } else {
    rawData.sensor8 = {false, 0};
  }

  if (opponentSensorConfig.useSensor9) {
    rawData.sensor9 = {true, digitalRead(Sensor9_in)};
  } else {
    rawData.sensor9 = {false, 0};
  }

  if (opponentSensorConfig.useSensor10) {
    rawData.sensor10 = {true, digitalRead(Sensor10_in)};
  } else {
    rawData.sensor10 = {false, 0};
  }

  if (opponentSensorConfig.useSensor11) {
    rawData.sensor11 = {true, digitalRead(Sensor11_in)};
  } else {
    rawData.sensor11 = {false, 0};
  }

  return rawData;
}

OpponentPositionResult preprocessRawOpponentSensorData(RawOpponentSensorData rawData) {
  OpponentPositionResult result = OpponentPositionResult();
  result.hasData = true;
  result.wasProcessed = true;
  result.rawData = rawData;

  int suma = 0, sgain = 0, s[12];

  s[1] = rawData.sensor1.hasData ? rawData.sensor1.value : 0;
  s[2] = rawData.sensor2.hasData ? rawData.sensor2.value : 0;
  s[3] = rawData.sensor3.hasData ? rawData.sensor3.value : 0;
  s[4] = rawData.sensor4.hasData ? rawData.sensor4.value : 0;
  s[5] = rawData.sensor5.hasData ? rawData.sensor5.value : 0;
  s[6] = rawData.sensor6.hasData ? rawData.sensor6.value : 0;
  s[7] = rawData.sensor7.hasData ? rawData.sensor7.value : 0;
  s[8] = rawData.sensor8.hasData ? rawData.sensor8.value : 0;
  s[9] = rawData.sensor9.hasData ? rawData.sensor9.value : 0;
  s[10] = rawData.sensor10.hasData ? rawData.sensor10.value : 0;
  s[11] = rawData.sensor11.hasData ? rawData.sensor11.value : 0;

  for (int i = 1; i <= 11; i++) {
    suma += s[i];
    sgain += s[i] * 10 * i;
  }

  if (suma == 0) {
    result.currentPosition = -1;
  } else {
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
