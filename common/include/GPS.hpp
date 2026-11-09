#pragma once
#include <Arduino.h>
#include <cstdint>

#define GPS_DEFAULT_BAUD 9600
#define GPS_MAX_AGE_MS 2000 // Time before treated as no fix to satellite

struct GPS_Time {
  int hours;
  int minutes;
  int seconds;
  int milliseconds;
};

struct GPS_Data {
  double latitude; // Positive = North / Negative = South
  double longitude; // Positive = East / Negative = West
  float altitude_meters; // Above sea level
  float speed_knots; // 
  float course_degrees;
  
  int satellites_used;
  bool has_fix;

  GPS_Time time;
};


bool GPS_Init(HardwareSerial& port);
bool GPS_Update();
bool GPS_ProcessChar(char c);
bool GPS_GetLatestData(GPS_Data* out);
