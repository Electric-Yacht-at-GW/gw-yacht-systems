#include "temp_sensor.hpp"

// ---------------------------------------------------------
// init() - Turns the sensor on and checks the connection
// ---------------------------------------------------------
bool TempSensor::init() {
    /*
     * PSEUDOCODE LOGIC:
     * 1. Send a "Wake Up" command over I2C to i2c_address_.
     * 2. Read the WHO_AM_I / ID register to verify it is the correct sensor.
     * 3. If the received ID does not match the datasheet, return false.
     * 4. Write configuration bytes (set to continuous read mode).
     */
    
    is_initialized_ = true;
    return true; // Success!
}

// ---------------------------------------------------------
// read_raw() - Pulls bytes over the physical wires
// ---------------------------------------------------------
bool TempSensor::read_raw() {
    // Safety check: Don't read if the sensor never initialized
    if (!is_initialized_) {
        return false; 
    }

    /*
     * PSEUDOCODE LOGIC:
     * 1. Send an I2C command asking for the first temperature data register.
     * 2. Wait for the sensor to send back 2 bytes.
     * 3. Store the first byte in raw_buffer_[0] (High Byte).
     * 4. Store the second byte in raw_buffer_[1] (Low Byte).
     * 5. If the bus times out or crashes during this, return false.
     */
    
    return true; // Successfully loaded bytes into the private buffer
}

// ---------------------------------------------------------
// process() - Converts raw bytes to scaled integer units (No Floats!)
// ---------------------------------------------------------
TempSensorData TempSensor::process() {
    TempSensorData output;

    // Default to a safe state until we know the math works out
    output.is_valid = false;
    output.temperature_mc = 0;
    output.timestamp_ms = 0; // In reality, we will call a system millis() function here

    // Safety check
    if (!is_initialized_) {
        return output; 
    }

    /*
     * PSEUDOCODE LOGIC:
     * 1. Combine raw_buffer_[0] and raw_buffer_[1] into a single 16-bit signed integer.
     *    Example: int16_t raw_counts = (raw_buffer_[0] << 8) | raw_buffer_[1];
     * 
     * 2. Scale to milli-Celsius using ONLY integer math. 
     *    (e.g., If the datasheet says 1 count = 0.0625 C, that means 1 count = 62.5 mC.
     *    Since we can't use decimals, multiply by 625 and divide by 10).
     *    Example: int32_t scaled_temp = (raw_counts * 625) / 10;
     * 
     * 3. Save the result into output.temperature_mc.
     */
    
    // Simulate successful processing
    output.is_valid = true;

    return output;
}
