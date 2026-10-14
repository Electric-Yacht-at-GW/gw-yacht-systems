//gps sensor
#include ...
#define GPS_DEFAULT_BAUD 9600
#define NMEA length of 82
struct GPS_Time {
int hours
int minutes
int seconds
int milliseconds
} 

struct GPS_Data {
double latitude
double longitude
float altitude_meters
float speed_?
float course_degrees

int satellites_in_view
bool has_fix

GPS_Time
}

//function prototypes
//start gps
GPS_Init
//process serial data by putting it into the parser
bool GPS_ProcessChar(char)
//get parsed data
bool GPS_GetLatestData
