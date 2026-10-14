#include <cstdint>


// putting all data into milli / No decimals
struct ImuData {
  int32_t accel_x_mg; // Acceleration along X in milli-g
  int32_t accel_y_mg; // Acceleration along Y in milli-g
  int32_t accel_z_mg; // Acceleration along Z in milli-g
  uint32_t timestamp_ms; // Time when reading was taken in millis
  bool is_valid; //Making sure the sensor is fine
}


class ImuSensor {
public:
  bool init(); // Initialize and verify the sensor is alive
  bool read_raw(); // Collects electrical bytes
  ImuData process(); // Convert bytes into clean Data from above (struct ImuData)

private: // Not sure what to put here, come back
  


}





