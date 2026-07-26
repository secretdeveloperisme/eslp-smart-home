#include "relay_module.h"

RelayModule::RelayModule(uint8_t relayPin1, uint8_t relayPin2) : relayPin1(relayPin1), relayPin2(relayPin2), pin1RelayMode(RELAY_MODE::NC), pin2RelayMode(RELAY_MODE::NC) {}
RelayModule::RelayModule(uint8_t relayPin1, uint8_t relayPin2, RELAY_MODE pin1RelayMode, RELAY_MODE pin2RelayMode) : relayPin1(relayPin1), relayPin2(relayPin2), pin1RelayMode(pin1RelayMode), pin2RelayMode(pin2RelayMode) {}

RelayModule::~RelayModule() {}

bool RelayModule::begin() {
    pinMode(relayPin1, OUTPUT);
    pinMode(relayPin2, OUTPUT);
    relayPin1Status = pin1RelayMode == RELAY_MODE::NO ? false : true;
    relayPin2Status = pin2RelayMode == RELAY_MODE::NO ? false : true;
    return true;
}

bool RelayModule::isRelay1On() {
    return relayPin1Status;
}

bool RelayModule::isRelay2On() {
    return relayPin2Status;
}

bool RelayModule::turnOnRelay1() {
    if (pin1RelayMode == RELAY_MODE::NO) {
        digitalWrite(relayPin1, HIGH);
    } else {
        digitalWrite(relayPin1, LOW);
    }
    relayPin1Status = true;
    return true;
}

bool RelayModule::turnOffRelay1() {
    if (pin1RelayMode == RELAY_MODE::NO) {
        digitalWrite(relayPin1, LOW);
    } else {
        digitalWrite(relayPin1, HIGH);
    }
    relayPin1Status = false;
    return true;
}

bool RelayModule::turnOnRelay2() {
    if (pin2RelayMode == RELAY_MODE::NO) {
        digitalWrite(relayPin2, HIGH);
    } else {
        digitalWrite(relayPin2, LOW);
    }
    relayPin2Status = true;
    return true;
}

bool RelayModule::turnOffRelay2() {
    if (pin2RelayMode == RELAY_MODE::NO) {
        digitalWrite(relayPin2, LOW);
    } else {
        digitalWrite(relayPin2, HIGH);
    }
    relayPin2Status = false;
    return true;
}

