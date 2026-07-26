#ifndef RELAY_MODULE_H
#define RELAY_MODULE_H
#include <Arduino.h>
enum class RELAY_MODE{
    NC,
    NO
};

class RelayModule{
    private:
        uint8_t relayPin1;
        uint8_t relayPin2;
        RELAY_MODE pin1RelayMode;
        RELAY_MODE pin2RelayMode;
        bool relayPin1Status = false;
        bool relayPin2Status = false;
    public:
        bool begin();
        bool turnOnRelay1();
        bool turnOffRelay1();
        bool turnOnRelay2();
        bool turnOffRelay2();
        bool isRelay1On();
        bool isRelay2On();
        RelayModule(uint8_t relayPin1, uint8_t relayPin2);
        RelayModule(uint8_t relayPin1, uint8_t relayPin2, RELAY_MODE pin1RelayMode, RELAY_MODE pin2RelayMode);
        ~RelayModule();
};


#endif // RELAY_MODULE_H