#ifndef MONITOR_H
#define MONITOR_H
#include <U8g2lib.h>

class OLEDMonitor{
  private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C* u8g2_monitor;
  public:
    OLEDMonitor(){
      this->u8g2_monitor = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
    };
    bool begin();
    void drawCenteredStr(int y, const char *str);
    void printInfoToDisplay(String now, float temperature, float humidity, float heatIndex);
    void printInfoToDisplay(String date, String time, float temperature, float humidity);
    ~OLEDMonitor(){
      delete u8g2_monitor;
    }
};
#endif