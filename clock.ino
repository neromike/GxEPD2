#include <GFX.h>  // uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX, to use less code and ram

#include <GxEPD2_BW.h> // including both doesn't use more code or ram
//#include <GxEPD2_3C.h> // including both doesn't use more code or ram

#include "GxEPD2_display_selection_new_style.h" // select the display class and display driver class in the following file (new style):

#define SET_RTC false

#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include "formatting.h"

#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define SUN_X display.width() / 2
#define SUN_Y 70
#define SUN_SIZE 10
#define EARTH_ORBIT 45
#define EARTH_SIZE 5
#define MOON_ORBIT 22
#define MOON_SIZE 3
#define BUFFER 5

#define ARC_HEIGHT 80
#define ARC_AXIS 220

#include "calc_times.h"
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;

uint16_t curr_year;
uint8_t curr_month, curr_day, curr_hour_24, curr_min;
uint8_t portion_hour_24, portion_min;
int UTC_offset;
long longitude, latitude;
float new_moon_phase, sunrise_time, sunset_time;

short earth_x, earth_y, moon_x, moon_y;
bool write_moon = true;

char this_time[9] = "";

void update_page() {
  int16_t tb;
  uint16_t tbw;

  display.firstPage();
  do {
    // Blank the screen
    display.fillScreen(GxEPD_WHITE);

    // draw the sun
    display.fillCircle(SUN_X, SUN_Y, SUN_SIZE, GxEPD_BLACK);

    // draw the earth orbit
    display.drawCircle(SUN_X, SUN_Y, EARTH_ORBIT, GxEPD_BLACK);

    // draw the earth
    display.fillCircle(earth_x, earth_y, EARTH_SIZE, GxEPD_BLACK);

    // draw the moon orbit
    display.drawCircle(earth_x, earth_y, MOON_ORBIT, GxEPD_BLACK);

    // draw the moon
    display.fillCircle(moon_x, moon_y, MOON_SIZE, GxEPD_BLACK);

    // draw the sun arc lines
    display.drawLine(0, ARC_AXIS, display.width(), ARC_AXIS, GxEPD_BLACK);
    display.drawLine(45, ARC_AXIS, 20, 200, GxEPD_BLACK);
    display.drawLine(display.width() - 45, ARC_AXIS, display.width() - 20, 200, GxEPD_BLACK);

    // draw the sun arc
    bool done = false;
    for (uint8_t x = 0; x <= display.width(); x++) {
      display.drawPixel(x, display.height() - BUFFER - ARC_HEIGHT * (0.5 - 0.5 * cos(6.28 * x / display.width())), GxEPD_BLACK);
      if ((not done) && ( (100 * x / display.width()) > (100 * (curr_hour_24 + (curr_min / 60)) / 24) )) {
        display.fillCircle(x, display.height() - BUFFER - ARC_HEIGHT * (0.5 - 0.5 * cos(6.28 * x / display.width())), MOON_SIZE, GxEPD_BLACK);
        done = true;
      }
    }

    display.setFont(NULL);

    // draw the 'sun' text
    display.getTextBounds("sun", 0, 0, &tb, &tb, &tbw, &tb);
    display.setCursor((display.width() - tbw) / 2, SUN_Y + SUN_SIZE + 1);
    display.print("sun");

    // draw the 'earth' text
    display.getTextBounds("earth", 0, 0, &tb, &tb, &tbw, &tb);
    display.setCursor(earth_x - (tbw / 2), earth_y + EARTH_SIZE + 1);
    display.print("earth");

    // draw the 'moon' text
    if (write_moon) {
      display.getTextBounds("moon", 0, 0, &tb, &tb, &tbw, &tb);
      display.setCursor(moon_x - (tbw / 2), moon_y + MOON_SIZE + 1);
      display.print("moon");
    }
    
    // draw the sunrise time label: 'sunrise'
    display.getTextBounds("sunrise", 0, 0, &tb, &tb, &tbw, &tb);
    display.setCursor(BUFFER, 190);
    display.print("sunrise");

    // draw the sunset time label: 'sunset'
    display.getTextBounds("sunset", 0, 0, &tb, &tb, &tbw, &tb);
    format_time(curr_hour_24, curr_min);
    display.setCursor(display.width() - tbw - BUFFER, 190);
    display.print("sunset");

    //display.setFont(&FreeSerif9pt7b);
    
    // draw the actual sunrise time
    convert_time(sunrise_time);
    format_time(portion_hour_24, portion_min);
    display.setCursor(BUFFER, 180);
    display.print(this_time);
    
    // draw the actual sunset time
    convert_time(sunset_time);
    format_time(portion_hour_24, portion_min);
    display.getTextBounds(this_time, 0, 0, &tb, &tb, &tbw, &tb);
    display.setCursor(display.width() - tbw - BUFFER, 180);
    display.print(this_time);
    
    //display.setFont(&FreeMonoBold18pt7b);
    display.setFont(&FreeSans18pt7b);
    
    // write out the time
    format_time(curr_hour_24, curr_min);
    display.getTextBounds(this_time, 0, 0, &tb, &tb, &tbw, &tb);
    display.setCursor((display.width() - tbw) / 2, 162);
    display.print(this_time);
    
  } while ( display.nextPage() );
}

void setup()
{
  Serial.begin(9600);
  display.init();
  display.setTextColor(GxEPD_BLACK);

  Wire.begin();
  if (! rtc.begin()) {
    //Serial.println("RTC is NOT running!");
    //Serial.flush();
    abort();
  }
  #if SET_RTC
    rtc.adjust(DateTime(__DATE__, __TIME__));
  #endif

  // current location
  latitude = 39.044449;
  longitude = -77.376572;

  // current time
  DateTime now = rtc.now();
  curr_year = now.year();
  curr_month = now.month();
  curr_day = now.day();
  curr_hour_24 = now.hour();
  curr_min = now.minute();
  UTC_offset = -4;

  curr_day = 10;
  curr_month = 9;

  // calculate the sunrise and sunset times
  calc_times();

  // calculate the celestial body positions
  short earth_angle = 360 * (30.4 * curr_month + curr_day) / 365;
  earth_x = SUN_X + EARTH_ORBIT * cos(earth_angle * DEG_TO_RAD);
  earth_y = SUN_Y + EARTH_ORBIT * sin(earth_angle * DEG_TO_RAD);
  short moon_angle = earth_angle + 360 * (new_moon_phase - 0.5);
  moon_x = earth_x + MOON_ORBIT * cos(moon_angle * DEG_TO_RAD);
  moon_y = earth_y + MOON_ORBIT * sin(moon_angle * DEG_TO_RAD);

  // determine if the 'moon' string should be displayed
  if (earth_angle > 45 && earth_angle < 90 && moon_angle > 45 && moon_angle < 270) {
    write_moon = false;
  }
  if (earth_angle > 90 && earth_angle < 135 && (moon_angle < 135 || moon_angle > 270)) {
    write_moon = false;
  }
  if ((moon_angle < 225 && moon_angle > 155) || moon_angle > 335 || moon_angle < 25) {
    write_moon = false;
  }

  // show the page
  update_page();
}

void loop() {};