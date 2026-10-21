#pragma once
#include <cstdint>


// putting all data into milli / No decimals
struct ImuData {
  uint32_t yaw_mdeg; // Heading in milli-degrees (0 to 359999)
  int32_t roll_mdeg; // Side to side tilt (heel) in milli-degrees
  int32_t pitch_mdeg; // Bow up/down tilt in milli-degrees
  int32_t accel_x_mg; // Linear acceleration along X in milli-g (gravity removed)
  int32_t accel_y_mg; // Linear acceleration along Y in milli-g
  int32_t accel_z_mg; // Linear acceleration along Z in milli-g
  uint32_t calib_status; // Raw CALIB_STAT byte (sys, gyro, accel, mag (each 2 bytes))
  uint32_t timestamp_ms; // Time when reading was taken in millis
  bool is_valid; // Making sure the sensor is fine
};


class ImuSensor {
public:
  bool init(); // Initialize and verify the sensor is alive
  bool read_raw(); // Collects electrical bytes
  ImuData process(); // Convert bytes into clean Data from above (struct ImuData)
  uint8_t read_calibration(); // Reads register 0x35, stores and returns it

private:
  // Register addresses
  static constexpr uint8_t REG_CHIP_ID = 0x00;
  static constexpr uint8_t REG_OPR_MODE = 0x3D;
  static constexpr uint8_t REG_PWR_MODE = 0x3E;
  static constexpr uint8_t REG_UNIT_SEL = 0x3B;
  static constexpr uint8_t REG_CALIB_STAT = 0x35;
  static constexpr uint8_t REG_EULER_START = 0x1A; // yaw, roll, pitch (2 bytes each = 6 total)
  static constexpr uint8_t REG_LINEAR_ACCEL_START = 0x28; // X, Y, Z (2 bytes each = 6 total)

  // Values written to / expected from registers
  static constexpr uint8_t EXPECTED_CHIP_ID = 0xA0;
  static constexpr uint8_t MODE_CONFIG = 0x00;
  static constexpr uint8_t MODE_NDOF = 0x0C;
  static constexpr uint8_t POWER_NORMAL = 0x00;
  static constexpr uint8_t UNITS_DEG_MG = 0x01; // Angles in degrees, accel in mg

  uint8_t i2c_address = 0x28; // Sensors address
  bool is_initialized_ = false; // Will turn true after init() gets called
  bool has_new_data_ = false; // Will turn true after a successful read_raw()
  uint8_t orientation_buffer_[6] = {0}; // yaw, roll, pitch bytes (low byte first)
  uint8_t acceleration_buffer_[6] // X, Y, Z linear acceleration bytes (low byte first)
  uint8_t calibration_status_ = 0; // Stores last calibration reading
};
