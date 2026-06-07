#ifndef ESPL_NETWORK_CPP
#define ESPL_NETWORK_CPP
#include "espl_network.h"
EsplNetwork::EsplNetwork(EsplConfig& config) : config(config) {}
bool EsplNetwork::begin() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(config.getSSID().c_str(), config.getPassword().c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        maximum_waiting_time -= 500;
        if (maximum_waiting_time <= 0) {
            return false;
        }
    }
    localIP = WiFi.localIP().toString();
    return true;
}
String EsplNetwork::getLocalIP() const
{
    return this->localIP;
}

uint32_t EsplNetwork::maximum_waiting_time = 10000; // 10 seconds
#endif // ESPL_NETWORK_CPP