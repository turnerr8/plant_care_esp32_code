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



void setup() {
  Serial.begin(115200);

  delay(1000);
  Serial.println("Starting up moisture sensor...");
}

void loop() {
  float val = analogRead(MOISTURE_SENSOR);
  Serial.print("Moisture sensor value: ");
  Serial.print((MOISTURE_MAX - val) / (MOISTURE_MAX - MOISTURE_MIN) * 100);
  Serial.println("%");
  delay(1000);
}

