#pragma once
#include <Arduino.h>
#include <cstdint>

#define GPS_DEFAULT_BAUD 9600
#define GPS_MAX_AGE_MS 2000

struct GPS_Time {
  int hours;
  int minutes;
  int seconds;
  int milliseconds;
};

struct GPS_Data {
  double latitude;
  double longitude;
  float altitude_meters;
  float speed_knots;
  float course_degrees;
  
  int satellites_used;
  bool has_fix;

  GPS_Time time;
};


bool GPS_Init(HardwareSerial& port);
bool GPS_Update();
bool GPS_ProcessChar(char c);
bool GPS_GetLatestData(GPS_Data* out);
