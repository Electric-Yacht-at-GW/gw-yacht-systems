#pragma once
#include <cstdint>


// putting all data into milli / No decimals
struct ImuData {
  // yaw_mdeg
  // roll_mdeg
  // pitch_mdeg
  int32_t accel_x_mg; // Acceleration along X in milli-g
  int32_t accel_y_mg; // Acceleration along Y in milli-g
  int32_t accel_z_mg; // Acceleration along Z in milli-g
  // calibration_status
  uint32_t timestamp_ms; // Time when reading was taken in millis
  bool is_valid; // Making sure the sensor is fine
};


class ImuSensor {
public:
  bool init(); // Initialize and verify the sensor is alive
  bool read_raw(); // Collects electrical bytes
  ImuData process(); // Convert bytes into clean Data from above (struct ImuData)
  // read_calibration

private:
  uint8_t i2c_address = 0x28; // Sensors address
  bool is_initialized_ = false; // Will turn true after init() gets called
  // has_new_data_ = false // Will turn true after a successful read_raw()
  // orientation_buffer_[6] // yaw, roll, pitch bytes
  // acceleration_buffer_[6] // X, Y, Z linear acceleration bytes
  // calibration_status_ // Stores last calibration reading
};
