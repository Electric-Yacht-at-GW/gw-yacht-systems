#include "IMU.hpp"



// Turns the sensor on and checks it
bool ImuSensor::init() {
  // 1. Start with I2C bus
  // 2. Wait some ms for the chip to boot (around half a second / ~500 ms)
  // 3. Read REG_CHIP_ID. If it isnt EXPECTED_CHIP_ID, retry then return false
  // 4. Write MODE_CONFIG to REG_OPR_MODE (must be in CONFIG to change settings?)
  // 5. Write POWER_NORMAL to REG_PWR_MODE
  // 6. Write UNITS_DEG_MG to REG_UNIT_SEL (degrees for angles and mg for accel)
  // 7. Reorient axis depending on how board in mounted
  // 8. Restore saved calibration
  // 9. Write MODE_NDOF to REG_OPR_MODE, wait some ms (like really small ~10-50)
  // 10. If anything above fails then return false
  
  has_new_data_ = false;
  is_initialized_ = true;
  return true;
}



// Gets the raw bytes from the sensor
bool ImuSensor::read_raw() {
  //Don't read if sensor was never started
  if (!is_initialized_) {
    return false;
  }
  
  // 1. Write REG_EULER_START as the register pointer, request 6 bytes
  // - if fewer than 6 arrive: has_new_data_ = false, return false
  // - otherwise copy into orientation_buffer_
  // 2. Write REG_LINEAR_ACCEL_START as the register pointer, request 6 bytes
  // - if fewer than 6 arrive: has_new_data_ = false, return false
  // - otherwise copy into acceleration_buffer_

  has_new_data_ = true;
  return true;
}



// Reads the calibration register and remembers it
uint8_t ImuSensor::read_calibration() {
  // 1. Read REG_CALIB_STAT (1 byte)
  // 2. Store it in calibration_status_
  // - Bits 7-6 = system
  // - Bits 5-4 = gyro
  // - Bits 3-2 = accel
  // - Bits 1-0 = mag

  return calibration_status_;
}



// Turns the raw bytes into numbers we can use
ImuData ImuSensor::process() {
  ImuData output;

  // Start with default values
  output.yaw_mdeg = 0;
  output.roll_mdeg = 0;
  output.pitch_mdeg = 0;
  output.accel_x_mg = 0;
  output.accel_y_mg = 0;
  output.accel_z_mg = 0;
  output.calib_status = 0;
  output.timestamp_ms = 0;
  output.is_valid = false;
  
  //Don't process if the sensor never started or there is no new data
  if (!is_initialized_ || !has_new_data_) {
    return output;
  }

  // Orientation: 16 LSB per degree, so milli-degrees = raw*1000/16 = raw*125/2
  // Yaw is unsigned (0 to 360), roll and pitch are signed
  // Cast to int32_t first so the multiplication can't overflow 16 bits
  uint16_t yaw_raw = combine_u16(orientation_buffer_[0], orientation_buffer_[1]);
  int16_t roll_raw = combine_s16(orientation_buffer_[2], orientation_buffer_[3]);
  int16_t pitch-raw = combine_s16(orientation_buffer_[4], orientation_buffer_[5]);

  output.yaw_mdeg = (uint32_t)yaw_raw * 125 / 2;
  output.roll_mdeg = (int32_t)roll_raw * 125 / 2;
  output.pitch_mdeg = (int32_t)pitch_raw * 125 / 2;

  // Linear acceleration: already in mg because UNIT_SEL was set
  output.accel_x_mg = combine_s16(acceleration_buffer_[0], acceleration_buffer_[1]);
  output.accel_y_mg = combine_s16(acceleration_buffer_[2], acceleration_buffer_[3]);
  output.accel_z_mg = combine_s16(acceleration_buffer_[4], acceleration_buffer_[5]);

  output.calib_status = calibration_status_;
  
  output.is_valid = true;

  return output;  
}
