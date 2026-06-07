#ifndef ESPL_CONFIG_H
#define ESPL_CONFIG_H
#include <Arduino.h>  
class EsplConfig {
public:
    EsplConfig();
    String getSSID() const;
    String getPassword() const;
    uint32_t getPort() const;
    void setDateTimeCollectionInterval(uint64_t interval);
    void setTHDataCollectionInterval(uint64_t interval);
    uint64_t getDateTimeCollectionInterval() const;
    uint64_t getTHDataCollectionInterval() const;
private:
    String ssid;
    String password;
    uint32_t port;
    uint64_t dateTimeCollectionInterval = 60000; // default to 1 minute
    uint64_t thDataCollectionInterval = 60000; // default to 1 minute
};

#endif // ESPL_CONFIG_H