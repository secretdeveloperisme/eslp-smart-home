#ifndef OLED_MONITOR_CPP
#define OLED_MONITOR_CPP
#include "oled_monitor.h"
#include "icons.h"

bool OLEDMonitor::begin(){
  return this->u8g2_monitor->begin();
}


void OLEDMonitor::drawCenteredStr(int y, const char *str){
  int stringWidth = this->u8g2_monitor->getStrWidth(str);
  int x = (128 - stringWidth) / 2;
  this->u8g2_monitor->drawStr(x, y, str);
}

void OLEDMonitor::printConnectingToWiFiScreen()
{
  this->u8g2_monitor->clearBuffer();
  this->u8g2_monitor->drawFrame(0, 0, 128, 64);
  this->u8g2_monitor->drawBitmap(52, 2, 3, 24, WIFI_ICON);
  this->u8g2_monitor->setFont(u8g2_font_6x10_tf);
  this->drawCenteredStr(34, "Connecting to wifi...");
  this->u8g2_monitor->sendBuffer();
}

void OLEDMonitor::printConnectedToWiFiScreen()
{
  this->u8g2_monitor->clearBuffer();
  this->u8g2_monitor->drawFrame(0, 0, 128, 64);
  this->u8g2_monitor->drawBitmap(52, 2, 3, 24, WIFI_ICON);
  this->u8g2_monitor->setFont(u8g2_font_6x10_tf);
  this->drawCenteredStr(34, "Wifi Connected!");
  this->u8g2_monitor->sendBuffer();
}

void OLEDMonitor::printIPAddressToDisplay(String ipAddress)
{
  this->u8g2_monitor->clearBuffer();
  this->u8g2_monitor->drawFrame(0, 0, 128, 64);
  this->u8g2_monitor->setFont(u8g2_font_6x10_tf);
  this->drawCenteredStr(10, "IP Address:");
  this->drawCenteredStr(30, ipAddress.c_str());
  this->u8g2_monitor->sendBuffer();
}

void OLEDMonitor::printInfoToDisplay(String now, float temperature, float humidity, float heatIndex){
  this->u8g2_monitor->clearBuffer();
  this->u8g2_monitor->drawFrame(0, 0, 128, 64);
  this->u8g2_monitor->setFont(u8g2_font_6x10_tf);
  String nowOutput = "Now: " + now;
  drawCenteredStr(10, now.c_str());
  String temperatureOutput = "Temper: " + String(temperature) + " °C";
  drawCenteredStr(10 +  this->u8g2_monitor->getMaxCharHeight() + 2, temperatureOutput.c_str());
  String humidityOutput = "Humidity: " + String(humidity) + "%";
   drawCenteredStr(10 + this->u8g2_monitor->getMaxCharHeight()*2 + 2, humidityOutput.c_str());
  String heatIndexOutput = "Heat index: " + String(heatIndex);
  drawCenteredStr(10 + this->u8g2_monitor->getMaxCharHeight()*3 + 2, heatIndexOutput.c_str());
  this->u8g2_monitor->sendBuffer();
}

void OLEDMonitor::printInfoToDisplay(String date, String time, float temperature, float humidity){
  this->u8g2_monitor->clearBuffer();
  this->u8g2_monitor->setCursor(2, 4);
  this->u8g2_monitor->drawBitmap(0, 0, 3, 24, WATCH_ICON);
  this->u8g2_monitor->setFont(u8g2_font_9x18_mn);
  drawCenteredStr(12, time.c_str());
  this->u8g2_monitor->setFont(u8g2_font_6x10_tf);
  drawCenteredStr(24, date.c_str());

  this->u8g2_monitor->drawLine(0, 32, 128, 32);
  this->u8g2_monitor->drawBitmap(0, 38, 3, 24, THERMORMETER_ICON);
  this->u8g2_monitor->drawBitmap(64, 38, 3, 24, HUMIDITY_ICON);
  this->u8g2_monitor->setCursor(24, 52);
  this->u8g2_monitor->setFont(u8g2_font_6x10_tf);
  this->u8g2_monitor->print(temperature);
  this->u8g2_monitor->setCursor(92, 52);
  this->u8g2_monitor->print(humidity);
  this->u8g2_monitor->sendBuffer();
}

void OLEDMonitor::printRelayStatusToDisplay(uint8_t relayNumber, bool relayStatus)
{
  this->u8g2_monitor->clearBuffer();
  this->u8g2_monitor->setFont(u8g2_font_9x18_tf);
  this->u8g2_monitor->setCursor(10, 10);
  this->u8g2_monitor->print("relay(" + String(relayNumber) + "): " + (relayStatus ? "on" : "off"));
  this->u8g2_monitor->setCursor(20, 56);
  this->u8g2_monitor->drawBitmap(52, 24, 3, 24, relayStatus ? SWITCH_ON_ICON : SWITCH_OFF_ICON);
  this->u8g2_monitor->drawLine(20, 22, 108, 22);
  this->u8g2_monitor->sendBuffer();
}

#endif
