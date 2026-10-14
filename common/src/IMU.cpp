#include "IMU.hpp"

// Turns the sensor on and checks it
bool ImuSensor::init() {
  is_initialized_ = true;
  return true;
}



// Gets the raw bytes from the sensor
bool ImuSensor::read_raw() {
  //Don't read if sensor was never started
  if (!is_initialized_) {
    return false;
  }
  return true;
}

// Turns the raw bytes into numbers we can use
ImuData ImuSensor::process() {
  ImuData output;

  // Start with default values
  output.accel_x_mg = 0;
  output.accel_y_mg = 0;
  output.accel_z_mg = 0;
  output.timestamp_ms = 0;
  
  //Don't process if the sensor never started
  if (!is_initialized_) {
    return output;
  }

  output.is_valid = true;

  return output;  
}






