#ifndef RTC_SENSOR_CPP
#define RTC_SENSOR_CPP
#include "WString.h"
#include "rtc_sensor.h"

bool RTCSensor::begin(){
  bool rtcStatus =  this->rtc->begin();
  if(!rtcStatus){
    #ifdef DEBUG
    Serial.println("RTC Sensor initialization failed!");
    #endif
    return false;
  }
  rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
  return true;
}

bool RTCSensor::status() {
  return this->rtc->isrunning();
}

String RTCSensor::getDateStr(){
  DateTime now = this->rtc->now();
  String dateOutput;
  dateOutput += now.year();
  dateOutput += '-';
  if (now.month() < 10) 
  {
    dateOutput += '0';
  }
  dateOutput += now.month();
  dateOutput += '-';
  if (now.day() < 10) 
  {
    dateOutput += '0';
  }
  dateOutput += now.day();
  return dateOutput;
}

String RTCSensor::getTimeStr(){
  DateTime now = this->rtc->now();
  String timeOutput;

  if (now.hour() < 10) {
    timeOutput += '0';
  }
  timeOutput += now.hour();
  timeOutput += ':';
  if (now.minute() < 10){
    timeOutput += '0';
  }
  timeOutput += now.minute();
  timeOutput += ':';
  if (now.second() < 10){
    timeOutput += '0';
  }
  timeOutput += now.second();
  return timeOutput;
}

String RTCSensor::getDateTimeStr(){
  DateTime now = this->rtc->now();
  String dateTimeOutput = getDateStr() + " " + getTimeStr();
  return dateTimeOutput;
}

String RTCSensor::getUTCDateTimeStr()
{
  DateTime dt = this->rtc->now();
  String iso8601DateTime = "";
  iso8601DateTime += dt.year();
  iso8601DateTime += '-';
  if (dt.month() < 10) iso8601DateTime += '0';
  iso8601DateTime += dt.month();
  iso8601DateTime += '-';
  if (dt.day() < 10) iso8601DateTime += '0';
  iso8601DateTime += dt.day();
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

String RTCSensor::getDayOfWeek(uint8_t day) {
  const char* daysOfWeek[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"
  };
  return String(daysOfWeek[day - 1]);
}


#endif