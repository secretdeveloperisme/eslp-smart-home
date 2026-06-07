#ifndef ESPL_NETWORK_H
#define ESPL_NETWORK_H
#include <WiFi.h>
#include "espl_config.h"
class EsplNetwork {
public:
    EsplNetwork(EsplConfig& config);
    bool begin();
    String getLocalIP() const;
private:
    static uint32_t maximum_waiting_time;
    EsplConfig& config;
    String localIP;
};
#endif // ESPL_NETWORK_H