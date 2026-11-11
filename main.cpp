// initialize sensors
// read data every 10 hz (preferably raw)
// do the math to get raw into usable data
// send data to the gauges and LCDs
// send said data over radio and/or log it to SD card

#include gps.hpp
#include <Arduino.h>

GPS_Data current_gps_data;

void setup() {
//idk yet
}

Void GpsLoop() {
  GPS_Update();

  if (GPS_GetLatestData) {
    if (current_gps_data.has_fix) {
    print string "Sats: "
    print current_gps_data.satellites_used
    print string " | Lat: "
    print current_gps_data.latitude
    print string " | Lon: "
    print current_gps_data.longitude
    print string " | Speed (kts): "
    print current_gps_data.speed_knots
    } else {
    print string "Waiting for satellite fix..."
  }
}
