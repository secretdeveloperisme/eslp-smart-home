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

// Timing variables for non-blocking operation
unsigned long lastDateTimeUpdate = 0;
unsigned long lastTHDataUpdate = 0;
unsigned long lastRelayStatusUpdate = 0;
unsigned long lastScreenUpdate = 0;
unsigned long screenUpdateInterval = 1000;
unsigned long relayStatusCollectionInterval = 2000;
bool firstRelayScreenStart = true;
uint32_t displayedRelayStatusVersion = 0;

void setup() {
  // Initialize Serial communication
  Serial.begin(SERIAL_BAUD);
  delay(2000);
  espl_config.setDateTimeCollectionInterval(1000);
  espl_config.setTHDataCollectionInterval(5000);

  Serial.println("\n\n========================================================");
  Serial.println("                      ESLP Smart Home                      ");
  Serial.println("==========================================================\n");
  Serial.println("Starting intitializing hardward");
  // Initialize hardware components
  InitializingHardwareResult hardwareInitResult = hardware_controller.begin();
  if (hardwareInitResult.getStatus() == ResultStatus::FAILURE) {
    Serial.println("Failed to initialize hardware: " + hardwareInitResult.getMessage());
    while (true) {
      // Infinite loop to halt execution if hardware initialization fails
    }
  }
  hardware_controller.getOLEDMonitor().printConnectingToWiFiScreen();
  system_service.getSystemState().setScreenState(ScreenState::WIFI_CONNECTING_SCREEN);
  Serial.println("Hardware initialized successfully!");
  if(espl_network.begin()){
    system_service.getSystemState().setScreenState(ScreenState::WIFI_CONNECTED_SCREEN);
    hardware_controller.getOLEDMonitor().printConnectedToWiFiScreen();
    delay(2000);
    hardware_controller.getOLEDMonitor().printIPAddressToDisplay(espl_network.getLocalIP());
    delay(2000);
    // Initialize Web Server
    espl_web_server.begin();
    Serial.println("Web server started successfully");
    system_service.getSystemState().setScreenState(ScreenState::WEB_SERVER_RUNNING_SCREEN);
  }

  Serial.println("ESLP Smart Home initialized successfully!\n");

  Serial.println("\n======================================");
  Serial.println("Setup complete! Starting main loop...");
  Serial.println("======================================\n");

  // Initialize timing variables
  lastDateTimeUpdate = lastTHDataUpdate = lastScreenUpdate = lastRelayStatusUpdate = millis();
  system_service.getSystemState().setScreenState(ScreenState::DASHBOARD_SCREEN);
}

String rtcDate = "YYYY-MM-DD";
String rtcTime = "HH:MM:SS";
float temperature = NAN, humidity = NAN;

void loop() {
  unsigned long currentMillis = millis();

  // Get current date and time
  if (currentMillis - lastDateTimeUpdate >= espl_config.getDateTimeCollectionInterval()) {
    rtcDate = hardware_controller.getRTCSensor().getDateStr();
    rtcTime = hardware_controller.getRTCSensor().getTimeStr();
    lastDateTimeUpdate = currentMillis;
  }

  // Get temperature and humidity data
  if (currentMillis - lastTHDataUpdate >= espl_config.getTHDataCollectionInterval()) {
    temperature = hardware_controller.getTHSensor().getTemperature();
    humidity = hardware_controller.getTHSensor().getHumidity();
    lastTHDataUpdate = currentMillis;
  }

  if(currentMillis - lastScreenUpdate >= screenUpdateInterval){
    lastScreenUpdate = currentMillis;
    if(system_service.getSystemState().getScreenState() == ScreenState::DASHBOARD_SCREEN){
      hardware_controller.getOLEDMonitor().printInfoToDisplay(rtcDate, rtcTime, temperature, humidity);
    }
  }

  if(system_service.getSystemState().getScreenState() == ScreenState::RELAY_STATUS_SCREEN) {
    uint32_t relayStatusVersion = system_service.getSystemState().getRelayStatusVersion();
    if (relayStatusVersion != displayedRelayStatusVersion) {
      displayedRelayStatusVersion = relayStatusVersion;
      lastRelayStatusUpdate = currentMillis;
      firstRelayScreenStart = true;
    }

    if (currentMillis - lastRelayStatusUpdate >= relayStatusCollectionInterval) {
      system_service.getSystemState().setScreenState(ScreenState::DASHBOARD_SCREEN);
      firstRelayScreenStart = false;
    } else if (firstRelayScreenStart) {
      system_service.displayRelayStatusToScreen();
      firstRelayScreenStart = false;
    }
  }

}

