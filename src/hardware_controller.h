#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H
#include "oled_monitor.h"
#include "rtc_sensor.h"
#include "th_sensor.h"
#include "initializing_hardware_result.h"

#define DHT_PIN 26
class HardwareController {
public:
    HardwareController();
    ~HardwareController();
    InitializingHardwareResult begin();
    OLEDMonitor& getOLEDMonitor();
    RTCSensor& getRTCSensor();
    THSensor& getTHSensor();
private:
    OLEDMonitor oled_monitor;
    RTCSensor rtc_sensor;
    THSensor th_sensor;
    const static uint8_t RETRY_COUNT;
};

#endif // HARDWARE_CONTROLLER_H