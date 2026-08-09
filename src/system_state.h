#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H
#include <stdint.h>
enum class ScreenState {
    MAIN_SCREEN,
    WIFI_CONNECTING_SCREEN,
    WIFI_CONNECTED_SCREEN,
    WEB_SERVER_RUNNING_SCREEN,
    DASHBOARD_SCREEN,
    RELAY_STATUS_SCREEN
};

class RelayStatus{
    private:
        uint8_t relayNumber;
        bool relayStatus;
    public:
        RelayStatus(uint8_t relayNumber, bool relayStatus) : relayNumber(relayNumber), relayStatus(relayStatus) {}
        uint8_t getRelayNumber() const { return relayNumber; }
        bool getRelayStatus() const { return relayStatus; } 
};

class SystemState {
    public:
        SystemState();
        void setScreenState(ScreenState newState);
        ScreenState getScreenState() const;
        void setRelayStatus(uint8_t relayNumber, bool status) {
            relayStatus = RelayStatus(relayNumber, status);
            relayStatusVersion++;
        }
        RelayStatus getRelayStatus() const { return relayStatus; }
        uint32_t getRelayStatusVersion() const { return relayStatusVersion; }
    private:
        ScreenState screenState;
        RelayStatus relayStatus;
        uint32_t relayStatusVersion;
};
#endif