#ifndef RTC_SENSOR_CPP
#define RTC_SENSOR_CPP
#include "WString.h"
#include "rtc_sensor.h"

bool RTCSensor::begin(){
  return this->rtc->begin();
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

String RTCSensor::getDayOfWeek(uint8_t day) {
  const char* daysOfWeek[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"
  };
  return String(daysOfWeek[day - 1]);
}


#endif