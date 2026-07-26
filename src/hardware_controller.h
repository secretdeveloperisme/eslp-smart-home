#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H
#include "oled_monitor.h"
#include "rtc_sensor.h"
#include "th_sensor.h"
#include "relay_module.h"
#include "initializing_hardware_result.h"

// Define the pin numbers for the sensors and modules
#define DHT_PIN 26
#define RELAY_PIN_1 12
#define RELAY_PIN_2 13

class HardwareController {
public:
    HardwareController();
    ~HardwareController();
    InitializingHardwareResult begin();
    OLEDMonitor& getOLEDMonitor();
    RTCSensor& getRTCSensor();
    THSensor& getTHSensor();
    RelayModule& getRelayModule();
    void setRelayStatus(uint8_t relayNumber, bool relayStatus);
private:
    OLEDMonitor oled_monitor;
    RTCSensor rtc_sensor;
    THSensor th_sensor;
    RelayModule relay_module;
    const static uint8_t RETRY_COUNT;
};

#endif // HARDWARE_CONTROLLER_H