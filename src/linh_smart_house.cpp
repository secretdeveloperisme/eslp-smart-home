#include <Arduino.h>
#include <Wire.h>
#include "rtc_sensor.h"
#include "oled_monitor.h"
#include "th_sensor.h"

#define SERIAL_BAUD 115200
#define DHT_PIN 26

OLEDMonitor oled_monitor;
RTCSensor rtc_sensor;
THSensor th_sensor(DHT_PIN);

/**
 * Print DateTime in ISO 8601 format
 */
String createDateTimeISO8601Str(const DateTime &dt) {
  String iso8601DateTime = "";
  iso8601DateTime += dt.year();
  iso8601DateTime += 'T';
  if (dt.hour() < 10) iso8601DateTime += '0';
  iso8601DateTime += dt.hour();
  iso8601DateTime += ':';
  if (dt.minute() < 10) iso8601DateTime += '0';
  iso8601DateTime += dt.minute();
  iso8601DateTime += ':';
  if (dt.second() < 10) iso8601DateTime += '0';
  iso8601DateTime += dt.second();
  iso8601DateTime += 'Z';
  return iso8601DateTime;
}


void setup() {
  // Initialize Serial communication
  Serial.begin(SERIAL_BAUD);
  delay(2000);
  
  Serial.println("\n\n========================================================");
  Serial.println("                      Linh Smart House                      ");
  Serial.println("==========================================================\n");

  // Initialize OLED SSD1306
  if (!oled_monitor.begin()) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      delay(1000);
  }

  Serial.println("Initalized OLED SSD1306 successfully");
  
  // Initialize RTC DS1307
  if (!rtc_sensor.begin()) {
    Serial.println("ERROR: RTC not found!");
    Serial.println("Please check your connections:");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("Initalized RTC DS1307 successfully");
  // Initalize DHT22
  th_sensor.begin();

  Serial.println("Initalized DHT22 successfully");
  
  Serial.println("ESP32 Smart House initialized successfully!\n");
  
  Serial.println("\n======================================");
  Serial.println("Setup complete! Starting main loop...");
  Serial.println("======================================\n");
}

void loop() {
  // Get current date and time

  String dateTimeStr = rtc_sensor.getDateTimeStr();
  String date = rtc_sensor.getDateStr();
  String time = rtc_sensor.getTimeStr();
  float temperature = th_sensor.getTemperature();
  float humidity = th_sensor.getHumidity();
  float heatIndex = th_sensor.calculateHeatIndex(temperature, humidity);

  oled_monitor.printInfoToDisplay(date, time, temperature, humidity);
  delay(1000);
}

