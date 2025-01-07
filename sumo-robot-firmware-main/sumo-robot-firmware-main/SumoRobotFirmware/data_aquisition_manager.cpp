#include "data_aquisition_manager.h"
#include "opponent_sensors.h"
#include "line_sensors.h"

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
  /* Serial.println("Hello world");

  if (sensorData.opponentPositionResult.hasData) {
    if (sensorData.opponentPositionResult.rawData.leftSensor.hasData) {
      Serial.print(sensorData.opponentPositionResult.rawData.leftSensor.value);
    }
  }

  if (sensorData.linePositionResult.hasData) {
    if (sensorData.linePositionResult.rawData.qtrFrontLeft.hasData) {
      Serial.print(sensorData.linePositionResult.rawData.qtrFrontLeft.value);
    }
  }
  */
  if (sensorData.opponentPositionResult.hasData) {
    Serial.print(sensorData.opponentPositionResult.currentPosition);
    Serial.print("\t");
  }

  if (sensorData.linePositionResult.hasData) {
    Serial.print(sensorData.linePositionResult.currentPosition);
    Serial.print("\t");
  }
  Serial.println("\t");
}
