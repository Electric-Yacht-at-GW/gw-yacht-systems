#pragma once
#include <cstdint>

// ==============================================================================
// 1. THE DATA STRUCT (What this sensor hands to the rest of the boat)
// ==============================================================================
// Naming Rule: Name this <SensorType>Data (e.g., GpsData, ImuData, VoltageData).
//
// Design Rule: Since we don't have the specific hardware models selected yet, 
// design this struct based on what the boat's main telemetry system will 
// ACTUALLY need to know. Use standard engineering units.
//
// EXAMPLES TO FOLLOW:
// - GPS Struct:  float latitude, float longitude, float speed_knots, bool has_fix
// - IMU Struct:  float accel_x_g, float accel_y_g, float accel_z_g
// - Gyro Struct: float roll_rate, float pitch_rate, float yaw_rate
// - BMS Struct:  float pack_voltage, float current_draw_amps, float highest_cell_temp
// Because no floats please have all decimal data scaled to milli-units
// ==============================================================================
struct TempSensorData {
    int32_t temperature_mc;   // The core data points in mill-degrees celcius
    uint32_t timestamp_ms; // When this reading was taken
    bool is_valid;         // Did the sensor glitch, or is this data trustworthy?
};

// ==============================================================================
// 2. THE CLASS (The Driver Interface)
// ==============================================================================
// Naming Rule: Name this <SensorType>Sensor or <SensorType>Driver 
// (e.g., GpsSensor, ImuDriver, CurrentSensor).
// ==============================================================================
class TempSensor {
public:
    // ---------------------------------------------------------
    // The "Buttons" - Anyone can call these functions
    // ---------------------------------------------------------
    
    // Initialize the hardware connection and verify the sensor is alive
    bool init();

    // Fetch new electrical bytes from the physical wires
    bool read_raw();

    // Convert those raw bytes into the clean Data Struct defined above
    TempSensorData process();

private:
    // ---------------------------------------------------------
    // The "Internal Wires" - Hidden from the rest of the code
    // ---------------------------------------------------------
    
    // The bus address (I2C/SPI) or pin number for this specific sensor.
    // (Just guess a standard hex address for now if hardware isn't finalized).
    uint8_t i2c_address_ = 0x48; 
    
    // Tracks if init() was run successfully so we don't read from a dead sensor.
    bool is_initialized_ = false; 
    
    // Fixed memory array to hold the incoming hardware bytes.
    // (Size this based on how many bytes a typical sensor of this type outputs).
    uint8_t raw_buffer_[2]; 
};
