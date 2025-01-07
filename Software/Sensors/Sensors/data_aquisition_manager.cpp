#include "data_aquisition_manager.h"
#include "lineSensors.h"
#include "opponentSensors.h"

SensorData aquireAllSensorData(SensorConfig sensorConfig) {
  // We create a new SensorData instance
  SensorData dataResult = SensorData();

  // We check config if line sensors should be used
  if (sensorConfig.lineSensorConfig.useLineSensors) {
    // We aquire line data
    dataResult.linePositionResult = aquireLineSensorData(sensorConfig.lineSensorConfig);
  } else {
    // We set an empty oponent position data and set hasData to false
    dataResult.linePositionResult = LinePositionResult();
    dataResult.linePositionResult.hasData = false;
  }

  // We check config if oponent sensors should be used
  if (sensorConfig.opponentSensorConfig.useOpponentSensors) {
    // We aquire oponnet data
    dataResult.opponentPositionResult = aquireOpponentSensorData(sensorConfig.opponentSensorConfig);
  } else {
    // We set an empty oponent position data and set hasData to false
    dataResult.opponentPositionResult = OpponentPositionResult();
    dataResult.opponentPositionResult.hasData = false;
  }

  dataResult.hasData = true;
  return dataResult;
}

void printSensorDataToSerial(SensorData sensorData) {


  if (sensorData.opponentPositionResult.hasData) {
    if (sensorData.opponentPositionResult.rawData.sensor1.hasData) {
      Serial.print("Sensor 1: ");
      Serial.println(sensorData.opponentPositionResult.rawData.sensor1.value);
    }
    if (sensorData.opponentPositionResult.rawData.sensor2.hasData) {
      Serial.print("Sensor 2: ");
      Serial.println(sensorData.opponentPositionResult.rawData.sensor2.value);
    }
    // Repeat for other sensors (sensor3 to sensor11)
  }

  if (sensorData.linePositionResult.hasData) {
    if (sensorData.linePositionResult.rawData.frontLeft.hasData) {
      Serial.print("Front Left: ");
      Serial.println(sensorData.linePositionResult.rawData.frontLeft.value);
    }
    if (sensorData.linePositionResult.rawData.frontRight.hasData) {
      Serial.print("Front Right: ");
      Serial.println(sensorData.linePositionResult.rawData.frontRight.value);
    }
    // Repeat for backLeft and backRight
  }


  if (sensorData.opponentPositionResult.hasData) {
    Serial.print("Opponent Position: ");
    Serial.print(sensorData.opponentPositionResult.currentPosition);
    Serial.print("\t");
  } else {
    Serial.print("Opponent Position: No Data\t");
  }

  if (sensorData.linePositionResult.hasData) {
    Serial.print("Line Position: ");
    Serial.print(sensorData.linePositionResult.currentPosition);
    Serial.print("\t");
  } else {
    Serial.print("Line Position: No Data\t");
  }

  Serial.println();
}
