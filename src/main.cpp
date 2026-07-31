#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

#ifndef MOISTURE_SENSOR
#define MOISTURE_SENSOR 34
#endif
#ifndef MOISTURE_MAX
#define MOISTURE_MAX 3500
#endif
#ifndef MOISTURE_MIN
#define MOISTURE_MIN 1700
#endif
#ifndef CHIP_ID
#define CHIP_ID ESP.getEfuseMac()
#endif

#define WIFI_SSID "I'm So Happy"


#define WIFI_PASS "1 L0ve Kp0p"

//ssid and wifi pass are stored as local variables WIFI_SSID and WIFI_PASS

//ntp pool vars
const char* ntpServer = "pool.ntp.org";
const long gmtOffsetSec = -25200;
const int daylightOffsetSec = 3600;

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("could not get time info.");
    return;
  }
  //time info gotten
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


void readSensor() {
  float val = analogRead(MOISTURE_SENSOR);
  printf("moisture sensor value: %f%%\n", (MOISTURE_MAX - val) / (MOISTURE_MAX - MOISTURE_MIN) * 100);
}



void setup() {
  Serial.begin(115200);
  //set up wifi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("CONNECTED");

  delay(1000);
  Serial.printf("Chip ID: %04X%08X\n", (uint16_t)(CHIP_ID >> 32), (uint32_t)CHIP_ID);
  Serial.println("Starting up moisture sensor...");
}

void loop() {
  printLocalTime();
  delay(3000);
}

