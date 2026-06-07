#include <stdint.h>
#ifndef RTC_SENSOR_H
#define RTC_SENSOR_H

#include <RTClib.h>
class RTCSensor{
  private:
    RTC_DS1307* rtc;

  public:
    RTCSensor(){
      this->rtc = new RTC_DS1307();
    }
    bool begin();
    bool status();
    String getDayOfWeek(uint8_t day);
    String getDateStr();
    String getTimeStr();
    String getDateTimeStr();
    String getUTCDateTimeStr();
    ~RTCSensor(){
      delete rtc;
    }
};

#endif