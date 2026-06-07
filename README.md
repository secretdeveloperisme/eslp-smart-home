# ESLP Smart Home

**ESLP Smart Home** is a compact, custom-engineered IoT ecosystem designed for real-time environmental monitoring, local timekeeping, and intelligent appliance automation. Driven by an ESP32 microcontroller, it pairs a DHT22 climate sensor and a DS1307 Real-Time Clock (RTC) with an SSD1306 OLED display and a 2-channel relay module. It also serves a web control interface entirely over the local network.

---

## Features

* **Real-Time Climate Tracking:** Continuous monitoring of ambient temperature and humidity using the DHT22 sensor.
* **Persistent Local Timekeeping:** Integrates a DS1307 RTC module to maintain accurate date and time, even if the ESP32 loses power or internet connectivity.
* **On-Board OLED Visuals:** Features a crisp, 0.96" SSD1306 OLED display to cycle through live telemetry, current time, and relay status indicators locally.
* **Dual-Channel Appliance Control:** Independently switch two isolated electrical loads (e.g., fans, lights...) via a 2-channel relay module.
* **Embedded Web Interface:** A lightweight, async HTML/CSS/JS dashboard hosted straight from the ESP32 to monitor live data and toggle relays.
---

## Hardware Requirements

* **Microcontroller:** ESP32-WROOM-32 Development Board 
* **Sensors:** DHT22 Temperature & Humidity Sensor
* **Timekeeping:** DS1307 Real-Time Clock (RTC) Module (with CR2032 backup battery)
* **Display:** 0.96" SSD1306 OLED Display (128x64 resolution, I2C version)
* **Actuators:** 2-Channel Relay Module (5V optocoupler-isolated)
* **Misc:** Breadboard, Jumper wires, resistors.


## Software Stack

* **Firmware Framework:** PlatformIO (C++)
* **Core Libraries:**
    * `WiFi.h` & `ESPAsyncWebServer.h` (Asynchronous HTTP network handling)
    * `DHT sensor library` by Adafruit
    * `U8G2` (OLED display handling)
    * `RTClib` by Adafruit (RTC synchronization and reading)
* **Frontend Dashboard:** Vanilla JavaScript, HTML5, and CSS3.

## Demo 
### Board 
![espl_smart_home_board](/documents/espl_smart_home_board.jpg)

### Dashboard web interface 
![espl_smart_home_web_dashboard](/documents/espl_smart_home_web_dashboard.jpg)


