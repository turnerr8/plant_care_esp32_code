#include <Arduino.h>

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



void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.printf("Chip ID: %04X%08X\n", (uint16_t)(CHIP_ID >> 32), (uint32_t)CHIP_ID);
  Serial.println("Starting up moisture sensor...");
}

void loop() {
  float val = analogRead(MOISTURE_SENSOR);
  printf("moisture sensor value: %f%%\n", (MOISTURE_MAX - val) / (MOISTURE_MAX - MOISTURE_MIN) * 100);
  delay(1000);
}

