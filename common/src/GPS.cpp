#include "GPS.hpp"
#include <TinyGPSPlus.h>

static TinyGPSPlus gps;
static HardwareSerial* gps_port = nullptr;

// Start the GPS
bool GPS_Init (HardwareSerial& port) {
  
}


// Feed a character to the library,  then return true when a valid sentence was parsed




// Read everything waiting on the serial port and send it to the parser




// Copy the latest values out of the library into our struct
// A fix only counts if the position is valid AND was updated recently
bool GPS_GetLatestData (GPS_Data* out) {
  if (out == nullptr) {
    return false;
  }

  bool fresh = gps.location.isValid() && gps.location.age() < GPS_MAX_AGE_MS;

  out->has_fix = fresh;
  out->latitude = gps.location.lat();
  out->longitude = gps.location.lng();
  out->altitude_meters = (float)gps.altitude.meters();
  out->speed_knots = (float)gps.speed.knots();
  out->course_degrees = (float)gps.course.deg();
  out->satellites_used = (int)gps.satellites.value();

  out->time.hours = gps.time.hour();
  out->time.minutes = gps.time.minute();
  out->time.seconds = gps.time.second();
  out->time.milliseconds = gps.time.centisecond() * 10;

  return fresh;
}











//buffer the NMEA string
//take the max length of a string and add one to keep like feeding through

//internal structure to hold the most recent data
static GPS_Data 

//internal functions
//verify NMEA (between $ and *)
static bool VerifyChecksum 
//extract the hex at end
//XOR all characters between
//compare those with hex
//return true if match

//parse the NMEA
static bool ParseNMEA{
  if checksum fails return false
  else split the string by commas
take each of those fields and return the value from them
...

//public api
GPS_Init defined

GPS_ProcessChar defined

GPS_GetLatestData defined
