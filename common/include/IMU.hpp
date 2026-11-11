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

  void set_saved_calibration(const uint8_t profile[22]);
  void set_external_crystal(bool enable);

  bool read_calibration_profile(uint8_t profile[22]);

  uint8_t system_status() const { return system_status_; }
  uint8_t system_error() const { return system_error_; }


private:
  // Register addresses
  static constexpr uint8_t REG_CHIP_ID = 0x00;
  static constexpr uint8_t REG_PAGE_ID = 0x07;
  static constexpr uint8_t REG_OPR_MODE = 0x3D;
  static constexpr uint8_t REG_PWR_MODE = 0x3E;
  static constexpr uint8_t REG_UNIT_SEL = 0x3B;
  static constexpr uint8_t REG_SYS_TRIGGER = 0x3F;
  static constexpr uint8_t REG_SYS_STAT = 0x39;
  static constexpr uint8_t REG_SYS_ERR = 0x3A;
  static constexpr uint8_t REG_CALIB_STAT = 0x35;
  static constexpr uint8_t REG_AXIS_MAP_CONFIG = 0x41;
  static constexpr uint8_t REG_AXIS_MAP_SIGN = 0x42;
  static constexpr uint8_t REG_CALIB_PROFILE = 0x55;
  static constexpr uint8_t REG_EULER_START = 0x1A; // yaw, roll, pitch (2 bytes each = 6 total)
  static constexpr uint8_t REG_LINEAR_ACCEL_START = 0x28; // X, Y, Z (2 bytes each = 6 total)

  // Values written to / expected from registers
  static constexpr uint8_t EXPECTED_CHIP_ID = 0xA0;
  static constexpr uint8_t PAGE_ZERO = 0x00;
  static constexpr uint8_t MODE_CONFIG = 0x00;
  static constexpr uint8_t MODE_NDOF = 0x0C;
  static constexpr uint8_t POWER_NORMAL = 0x00;
  static constexpr uint8_t UNITS_DEG_MG = 0x01; // Angles in degrees, accel in mg
  static constexpr uint8_t AXIS_MAP_DEFAULT = 0x24;
  static constexpr uint8_t AXIS_SIGN_DEFAULT = 0x00;
  static constexpr uint8_t SYS_TRIGGER_RESET = 0x20;
  static constexpr uint8_t SYS_TRIGGER_EXT_XTAL = 0x80;
  static constexpr uint8_t STATUS_FUSION_RUNNING = 5;
  static constexpr uint8_t CALIB_PROFILE_SIZE = 22;

  static constexpr uint32_t BOOT_DELAY_MS = 500; 
  static constexpr uint32_t RESET_DELAY_MS = 700; 
  static constexpr uint32_t CHIP_ID_RETRY_DELAY_MS = 100; 
  static constexpr uint8_t  CHIP_ID_RETRIES = 5;
  static constexpr uint32_t CONFIG_SWITCH_DELAY_MS = 20; 
  static constexpr uint32_t NDOF_SWITCH_DELAY_MS = 600; 
  static constexpr uint32_t POWER_DELAY_MS = 10;

  bool write_register(uint8_t reg, uint8_t value);
  bool read_registers(uint8_t start_reg, uint8_t* dest, uint8_t length);
  bool wait_for_chip();

  static uint16_t combine_u16(uint8_t lo, uint8_t hi) {
    return (uint16_t)(lo | ((uint16_t)hi << 8));
  }
  static int16_t combine_s16(uint8_t lo, uint8_t hi) {
    return (int16_t)(lo | ((uint16_t)hi << 8));
  }

  uint8_t i2c_address = 0x28;
  bool is_initialized_ = false; 
  bool has_new_data_ = false;
  uint8_t orientation_buffer_[6] = {0}; 
  uint8_t acceleration_buffer_[6] = {0}; 
  uint8_t calibration_status_ = 0; 
  uint32_t last_read_ms_ = 0;

  bool use_external_crystal_ = false;
  bool has_saved_calibration_ = false;
  uint8_t saved_calibration_[22] = {0}; 
  uint8_t system_status_ = 0;  
  uint8_t system_error_ = 0; 
};
