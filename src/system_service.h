#ifndef SYSTEM_SERVICE_H
#define SYSTEM_SERVICE_H
#include "data_model.h"
#include "hardware_controller.h"
class SystemService {
public:
    SystemService(HardwareController& hardwareController);
    DateTimeData getCurrentDateTime();
    THData getCurrentTHData();
    RelayStatusData getCurrentRelayStatus();
    void setRelayStatus(uint8_t relayNumber, bool relayStatus);
private:
    HardwareController& hardwareController;

};

#endif // SYSTEM_SERVICE_H