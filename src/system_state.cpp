#include "system_state.h"

SystemState::SystemState(): screenState(ScreenState::MAIN_SCREEN), relayStatus(0, false), relayStatusVersion(0) {
}

void SystemState::setScreenState(ScreenState newState) {
    this->screenState = newState;
}

ScreenState SystemState::getScreenState() const {
    return this->screenState;
}

