#include <Arduino.h>
#include <Wire.h>
#include "hardware_controller.h"
#include "espl_network.h"
#include "espl_web_server.h"
#include "system_service.h"

#define SERIAL_BAUD 115200

HardwareController hardware_controller;
EsplConfig espl_config;
EsplNetwork espl_network(espl_config);
SystemService system_service(hardware_controller);
EsplWebServer espl_web_server(espl_config, espl_network, system_service);

uint64_t dateTimeIntervalTimer = 0;
uint64_t thDataIntervalTimer = 0;

void setup() {
  // Initialize Serial communication
  Serial.begin(SERIAL_BAUD);
  delay(2000);
  espl_config.setDateTimeCollectionInterval(1000);
  espl_config.setTHDataCollectionInterval(5000); 
  
  Serial.println("\n\n========================================================");
  Serial.println("                      ESLP Smart Home                      ");
  Serial.println("==========================================================\n");

  // Initialize hardware components
  InitializingHardwareResult hardwareInitResult = hardware_controller.begin();
  if (hardwareInitResult.getStatus() == ResultStatus::FAILURE) {
    Serial.println("Failed to initialize hardware: " + hardwareInitResult.getMessage());
    while (true) {
      // Infinite loop to halt execution if hardware initialization fails
    }
  }
  hardware_controller.getOLEDMonitor().printConnectingToWiFiScreen();
  Serial.println("Hardware initialized successfully!");
  if(espl_network.begin()){
    hardware_controller.getOLEDMonitor().printConnectedToWiFiScreen();
    delay(2000);
    hardware_controller.getOLEDMonitor().printIPAddressToDisplay(espl_network.getLocalIP());
    delay(2000);

    // Initialize Web Server
    espl_web_server.begin();
    Serial.println("Web server started successfully");
  }

  Serial.println("ESLP Smart Home initialized successfully!\n");
  
  Serial.println("\n======================================");
  Serial.println("Setup complete! Starting main loop...");
  Serial.println("======================================\n");
}

String rtcDate = "YYYY-MM-DD";
String rtcTime = "HH:MM:SS";
float temperature = NAN, humidity = NAN;

void loop() {
  // Get current date and time
  if(dateTimeIntervalTimer == espl_config.getDateTimeCollectionInterval() || dateTimeIntervalTimer == 0){
    rtcDate = hardware_controller.getRTCSensor().getDateStr();
    rtcTime = hardware_controller.getRTCSensor().getTimeStr();
    dateTimeIntervalTimer = 0;
  }

  if(thDataIntervalTimer == espl_config.getTHDataCollectionInterval() || thDataIntervalTimer == 0){
    temperature = hardware_controller.getTHSensor().getTemperature();
    humidity = hardware_controller.getTHSensor().getHumidity();
    thDataIntervalTimer = 0;
  }
  hardware_controller.getOLEDMonitor().printInfoToDisplay(rtcDate, rtcTime, temperature, humidity);

  dateTimeIntervalTimer += 1000;
  thDataIntervalTimer += 1000;
  delay(1000);
}

