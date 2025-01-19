#ifndef STRUCTURES_SENSOR_CONFIG_H
#define STRUCTURES_SENSOR_CONFIG_H

struct OpponentSensorConfig
{
    bool useOpponentSensors = true;
    bool processOpponentSensors = true;
    bool useLeft90Sensor = true;
    bool useLeftSensor = true;
    bool useLeftCenterSensor = true;
    bool useCenterSensor = true;
    bool useRightCenterSensor = true;
    bool useRightSensor = true;
    bool useRight90Sensor = true;
};

struct LineSensorConfig
{
    bool useLineSensors = true;
    bool processLineSensors = true;
    bool useQtrFrontLeft = true;
    bool useQtrFrontRight = true;
    bool useQtrBackLeft = false;
    bool useQtrBackRight = false;
};

struct SensorConfig
{
    OpponentSensorConfig opponentSensorConfig;
    LineSensorConfig lineSensorConfig;
};

struct IntSensorData
{
    bool hasData = false;
    int value;
};

struct DoubleSensorData
{
    bool hasData = false;
    double value;
};

struct RawOpponentSensorData
{
    IntSensorData leftSensor;
    IntSensorData left90Sensor;
    IntSensorData leftCenterSensor;
    IntSensorData centerSensor;
    IntSensorData rightSensor;
    IntSensorData right90Sensor;
    IntSensorData rightCenterSensor;
};

struct RawLineSensorData
{
    IntSensorData qtrFrontLeft;
    IntSensorData qtrFrontRight;
    IntSensorData qtrBackLeft;
    IntSensorData qtrBackRight;
};

// Is opponent position just an int?
struct OpponentPositionResult
{
    bool hasData = false;
    bool wasProcessed = false;
    RawOpponentSensorData rawData;
    int currentPosition;
};

struct LinePositionResult
{
    bool hasData = false;
    bool wasProcessed = false;
    RawLineSensorData rawData;
    int currentPosition;
};

// Holds all sensor data
struct SensorData
{
    bool hasData = false;
    OpponentPositionResult opponentPositionResult;
    LinePositionResult linePositionResult;
};

// Holds current and previous sensor data
struct DataHolder
{
    SensorData currentSensorData;
    SensorData previousSensorData;
};

#endif