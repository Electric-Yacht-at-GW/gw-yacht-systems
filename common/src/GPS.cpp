#include "GPS.h"

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
