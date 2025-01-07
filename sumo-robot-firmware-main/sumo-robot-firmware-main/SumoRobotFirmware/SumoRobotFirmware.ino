#include "led_worker.h"
#include "pin_config.h"
#include "structures/structures.h"
#include "data_aquisition_manager.h"
#include "state_manager.h"
//#include "motor_manager.h"

SensorConfig sensorConfig = SensorConfig();
DataHolder dataHolder = DataHolder();

void setup() {

  // First thing at boot is to create default configuration and set different configuration
  sensorConfig.opponentSensorConfig = OpponentSensorConfig();
  sensorConfig.lineSensorConfig = LineSensorConfig();

  // Second thing we configure Serial
  Serial.begin(9600);

  // Third thing we setup various pin modes
  // This should probably be done in a different CPP within a function dedicated to this
  // This should probably be done based on configuration
  pinMode(pin_opponent_left90, INPUT);
  pinMode(pin_opponent_left, INPUT);
  pinMode(pin_opponent_left_center, INPUT);
  pinMode(pin_opponent_center, INPUT);
  pinMode(pin_opponent_right_center, INPUT);
  pinMode(pin_opponent_right, INPUT);
  pinMode(pin_opponent_right90, INPUT);

  pinMode(pin_qtr_front_left, INPUT);
  pinMode(pin_qtr_front_right, INPUT);

  pinMode(start_module, INPUT);

  pinMode(dip1, INPUT);
  pinMode(dip2, INPUT);
  pinMode(dip3, INPUT);
  pinMode(dip4, INPUT);
  pinMode(dip5, INPUT);

  // We initialize motors
  //setupMotors();

  // We setup states
  setupStates();
}


// the loop function runs over and over again forever
void loop() {

  // First thing we loop the existing data
  if (dataHolder.currentSensorData.hasData) {
    dataHolder.previousSensorData = dataHolder.currentSensorData;
  }

  // Second thing within the loop, we aquire new sensor data
  dataHolder.currentSensorData = aquireAllSensorData(sensorConfig);
  printSensorDataToSerial(dataHolder.currentSensorData);

  // We pass the data to the state machine and let it process a tick
  runStateManagerTick(dataHolder);

  // return 2 values as vectors
  // int position_vector[2], j, value;

  //  OpponentPositionResult opponentPosition = aquireOpponentSensorData();
  //
  //  Serial.print(opponentPosition.currentPosition);
  //  Serial.print(opponentPosition.rawData.sensor1);
  //  Serial.print(opponentPosition.rawData.sensor2);

  // Check for shorts and disable sensor in config.

  // SensorData sensorData = aquireAllSensorData(sensorConfig);
  // printSensorDataToSerial(sensorData);

  // dataHolder.previousSensorData = dataHolder.currentSensorData;
  // dataHolder.currentSensorData = aquireAllSensorData();

  // processStateTick(dataHolder)

  //  Position pointA = {2, 3};
  //
  //  Serial.print(pointA.x);
  //  Serial.print(pointA.y);
  // position_vector[j] = opponent_fuzzy_data();
  // Serial.print(" | ");
  // Serial.println(position_vector[2]);
  // value = opponent_fuzzy_data();
  // Serial.println(value);
  delay(10);
}
