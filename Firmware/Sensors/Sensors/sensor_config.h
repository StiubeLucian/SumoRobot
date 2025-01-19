#ifndef STRUCTURES_SENSOR_CONFIG_H
#define STRUCTURES_SENSOR_CONFIG_H

struct OpponentSensorConfig {
  bool useOpponentSensors = true;
  bool processOpponentSensors = true;
  bool useSensor1 = true;
  bool useSensor2 = false;
  bool useSensor3 = false;
  bool useSensor4 = false;
  bool useSensor5 = false;
  bool useSensor6 = false;
  bool useSensor7 = false;
  bool useSensor8 = false;
  bool useSensor9 = false;
  bool useSensor10 = false;
  bool useSensor11 = false;
};

struct LineSensorConfig {
  bool useLineSensors = true;
  bool processLineSensors = true;
  bool useFrontLeft = true;
  bool useFrontRight = true;
  bool useBackLeft = true;
  bool useBackRight = true;
};

struct SensorConfig {
  OpponentSensorConfig opponentSensorConfig;
  LineSensorConfig lineSensorConfig;
};

struct IntSensorData {
  bool hasData = false;
  int value;
};

struct RawOpponentSensorData {
  IntSensorData sensor1;
  IntSensorData sensor2;
  IntSensorData sensor3;
  IntSensorData sensor4;
  IntSensorData sensor5;
  IntSensorData sensor6;
  IntSensorData sensor7;
  IntSensorData sensor8;
  IntSensorData sensor9;
  IntSensorData sensor10;
  IntSensorData sensor11;
};

struct RawLineSensorData {
  IntSensorData frontLeft;
  IntSensorData frontRight;
  IntSensorData backLeft;
  IntSensorData backRight;
};

struct OpponentPositionResult {
  bool hasData = false;
  bool wasProcessed = false;
  RawOpponentSensorData rawData;
  int currentPosition;
};

struct LinePositionResult {
  bool hasData = false;
  bool wasProcessed = false;
  RawLineSensorData rawData;
  int currentPosition;
};

struct SensorData {
  bool hasData = false;
  OpponentPositionResult opponentPositionResult;
  LinePositionResult linePositionResult;
};

#endif
