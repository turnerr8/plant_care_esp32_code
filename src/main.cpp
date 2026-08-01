#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "secrets.h"

//globals

//sensor pins
int MOISTURE_SENSOR = 34;

//moisture max and min for normalizing readings
int MOISTURE_MAX = 3500;
int MOISTURE_MIN = 1700;

//get mac id for this esp32 chip to use as unique identifier
uint64_t CHIP_ID = ESP.getEfuseMac();

//ntp pool vars
const char* ntpServer = "pool.ntp.org";

//connects to wifi network using ssid and wifi password defined in secrets.h
void setupWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("CONNECTED");
  return;
}

//DEV: used to print local time for timeinfo structure testing
void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to get time info.");
    return;
  }

  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
  
  
}

//reads analog input from moisture sensor and normalizes it from 1-100 based on readings that i got
//sometimes goes over 100 but only rarely when submerged
void readSensor() {
  float val = analogRead(MOISTURE_SENSOR);
  printf("moisture sensor value: %f%%\n", (MOISTURE_MAX - val) / (MOISTURE_MAX - MOISTURE_MIN) * 100);
}


// SETUP
void setup() {
  //set serial output, connect to wifi, then set delay to let them boot up
  Serial.begin(115200);
  setupWifi();
  delay(1000);

  //set day and time
  configTime(0, 0, ntpServer);
  setenv("TZ", "PST8PDT,M3.2.0,M11.1.0", 1);
  tzset();

  Serial.printf("Chip ID: %04X%08X\n", (uint16_t)(CHIP_ID >> 32), (uint32_t)CHIP_ID);
  Serial.println("Starting up moisture sensor...");
}

void loop() {
  printLocalTime();
  delay(3000);
}

