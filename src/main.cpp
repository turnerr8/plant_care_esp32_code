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

//struct that will hold all reading information
struct SensorReading {
  uint64_t chipId;
  float moistureReading;
  String timeStamp;
};

SensorReading reading;

//get mac id for this esp32 chip to use as unique identifier
uint64_t CHIP_ID = ESP.getEfuseMac();

//ntp pool vars
const char* ntpServer = "pool.ntp.org";

//functions

//print all readings
void printReadings(const SensorReading& reading){
  Serial.printf("Chip ID: %04X%08X\n",
                  (uint16_t)(reading.chipId >> 32),
                  (uint32_t)reading.chipId);
  Serial.printf("Moisture level: %.2f%%\n", reading.moistureReading);
  Serial.printf("Timestamp: %s\n", reading.timeStamp.c_str());

}

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
void getLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to get time info.");
    return;
  }

  char timestamp[30];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", &timeinfo);
  reading.timeStamp = timestamp;
  //Serial.println(timestamp);
}

//reads analog input from moisture sensor and normalizes it from 1-100 based on readings that i got
//sometimes goes over 100 but only rarely when submerged
void readSensor() {
  float val = analogRead(MOISTURE_SENSOR);
  val = (MOISTURE_MAX - val) / (MOISTURE_MAX - MOISTURE_MIN) * 100;
  reading.moistureReading = val;
  //printf("moisture sensor value: %f%%\n", val);
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

  reading.chipId = CHIP_ID;
  // Serial.printf("Chip ID: %04X%08X\n", (uint16_t)(CHIP_ID >> 32), (uint32_t)CHIP_ID);
  Serial.println("Starting up moisture sensor...");
}

void loop() {
  getLocalTime();
  readSensor();
  printReadings(reading);

  delay(3000);
}

