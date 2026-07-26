#ifndef HARDWARE_CONTROLLER_CPP
#define HARDWARE_CONTROLLER_CPP
#include "hardware_controller.h"
const uint8_t HardwareController::RETRY_COUNT = 3;

HardwareController::HardwareController() : oled_monitor(), rtc_sensor(), th_sensor(DHT_PIN), relay_module(RELAY_PIN_1, RELAY_PIN_2) {
}
HardwareController::~HardwareController() {
}
InitializingHardwareResult HardwareController::begin(){
    uint8_t retryCount = 0;
    InitializingHardwareResult oledResult = this->oled_monitor.begin() ? InitializingHardwareResult(ResultStatus::SUCCESS, "OLED initialized successfully", HardwareType::OLED) : InitializingHardwareResult(ResultStatus::FAILURE, "Failed to initialize OLED", HardwareType::OLED);
    if (oledResult.getStatus() == ResultStatus::FAILURE) {
        while (this->oled_monitor.begin() == false && retryCount < RETRY_COUNT) {
            #ifdef DEBUG
            Serial.println("Failed to initialize SSD1306 OLED! Retrying...");
            #endif
            delay(1000);
            retryCount++;
        }
        #ifdef DEBUG
        Serial.println("Failed to initialize SSD1306 OLED!");
        #endif
        if (this->rtc_sensor.status() == false) {
            return oledResult;
        }
    }
    retryCount = 0;
    InitializingHardwareResult rtcResult = this->rtc_sensor.begin() ? InitializingHardwareResult(ResultStatus::SUCCESS, "RTC initialized successfully", HardwareType::RTC) : InitializingHardwareResult(ResultStatus::FAILURE, "Failed to initialize RTC", HardwareType::RTC);
    if (rtcResult.getStatus() == ResultStatus::FAILURE) {
        while (this->rtc_sensor.begin() == false && retryCount < RETRY_COUNT) {
            #ifdef DEBUG
            Serial.println("Failed to initialize RTC! Retrying...");
            #endif
            delay(1000);
            retryCount++;
        }
        if (this->rtc_sensor.status() == false) {
            return rtcResult;
        }
    }
    retryCount = 0;
    this->th_sensor.begin();
    InitializingHardwareResult thSensorResult = this->th_sensor.getStatus() ? InitializingHardwareResult(ResultStatus::SUCCESS, "TH Sensor initialized successfully", HardwareType::TH_SENSOR) : InitializingHardwareResult(ResultStatus::FAILURE, "Failed to initialize TH Sensor", HardwareType::TH_SENSOR);
    if (thSensorResult.getStatus() == ResultStatus::FAILURE) {
        while (this->th_sensor.getStatus() == false && retryCount < RETRY_COUNT) {
            this->th_sensor.begin();
            #ifdef DEBUG
            Serial.println("Failed to initialize DHT22 Sensor! Retrying...");
            #endif
            delay(1000);
            retryCount++;
        }
        if (this->th_sensor.getStatus() == false) {
            return thSensorResult;
        }
    }
    retryCount = 0;
    InitializingHardwareResult relayResult = this->relay_module.begin() ? InitializingHardwareResult
    (ResultStatus::SUCCESS, "Relay Module initialized successfully", HardwareType::RELAY_MODULE) : InitializingHardwareResult(ResultStatus::FAILURE, "Failed to initialize Relay Module", HardwareType::RELAY_MODULE);

    return InitializingHardwareResult(ResultStatus::SUCCESS, "All hardware initialized successfully");
}

OLEDMonitor& HardwareController::getOLEDMonitor() {
    return this->oled_monitor;
}
RTCSensor& HardwareController::getRTCSensor() {
    return this->rtc_sensor;
}
THSensor& HardwareController::getTHSensor() {
    return this->th_sensor;
}
RelayModule& HardwareController::getRelayModule() {
    return this->relay_module;
}
void HardwareController::setRelayStatus(uint8_t relayNumber, bool relayStatus) {
    if (relayNumber == 1) {
        if (relayStatus && !this->relay_module.isRelay1On()) {
            this->relay_module.turnOnRelay1();
        } else if (!relayStatus && this->relay_module.isRelay1On()) {
            this->relay_module.turnOffRelay1();
        }
    } else if (relayNumber == 2) {
        if (relayStatus && !this->relay_module.isRelay2On()) {
            this->relay_module.turnOnRelay2();
        } else if (!relayStatus && this->relay_module.isRelay2On()) {
            this->relay_module.turnOffRelay2();
        }
    }
}
#endif // HARDWARE_CONTROLLER_CPP