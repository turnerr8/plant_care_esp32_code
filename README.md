# Micro Controller code for Plant Care app used with moisture sensors

### Description
Created this iot device to help prevent me from watering my plants. I have wanted to learn more about IOT and microcontrollers and thought I might as well create something I would use.

### Parts
- ESP-32 Microcontroller
- Capacitive Soil Moisture Sensor v1.2
- Power Bank

### Setup
1) Pull this repository and use either ArduinoIDE or PlatformIO for sending code to microchip
2) create a `secrets.h` file in `/include` containing the following code
    ```
    #pragma once

    constexpr char WIFI_SSID[] = "YOUR_WIFI_SSID";
    constexpr char WIFI_PASS[] = "YOUR_WIFI_PASSWORD";
    constexpr char API_KEY[] = "A_UNIQUE_KEY";
    ```
    The `API_KEY` is not a necessary step if this is fully hosted on a local network but one I use as an extra security step for preventing any accidental api calls from something else.