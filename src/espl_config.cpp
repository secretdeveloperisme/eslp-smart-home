#ifndef ESPL_CONFIG_CPP
#define ESPL_CONFIG_CPP
#include "espl_config.h"
EsplConfig::EsplConfig() : ssid(WIFI_SSID), password(WIFI_PASSWORD), port(WEB_SERVER_PORT) {}
String EsplConfig::getSSID() const {
    return ssid;
}
String EsplConfig::getPassword() const {
    return password;
}
uint32_t EsplConfig::getPort() const {
    return port;
}
void EsplConfig::setDateTimeCollectionInterval(uint64_t interval) {
    if(interval % 1000 != 0){
        Serial.println("DateTime collection interval must be a multiple of 1000ms");
        return;
    }
    this->dateTimeCollectionInterval = interval;
}
void EsplConfig::setTHDataCollectionInterval(uint64_t interval) {
    if(interval % 1000 != 0){
        Serial.println("TH data collection interval must be a multiple of 1000ms");
        return;
    }
    this->thDataCollectionInterval = interval;
}   
uint64_t EsplConfig::getDateTimeCollectionInterval() const {
    return dateTimeCollectionInterval;
}

uint64_t EsplConfig::getTHDataCollectionInterval() const {
    return thDataCollectionInterval;
}
#endif // ESPL_CONFIG_CPP
