#ifndef SYSTEM_SERVICE_H
#define SYSTEM_SERVICE_H
#include "data_model.h"
#include "hardware_controller.h"
#include "system_state.h"
class SystemService {
public:
    SystemService(HardwareController& hardwareController);
    SystemState& getSystemState();
    const SystemState& getSystemState() const;
    DateTimeData getCurrentDateTime();
    THData getCurrentTHData();
    RelayStatusData getCurrentRelayStatus();
    void setRelayStatus(uint8_t relayNumber, bool relayStatus);
    void displayRelayStatusToScreen();
private:
    HardwareController& hardwareController;
    SystemState systemState;
};

#endif // SYSTEM_SERVICE_H