#ifndef INITIALIZING_HARDWARE_RESULT_H
#define INITIALIZING_HARDWARE_RESULT_H
#include <Arduino.h>

enum class ResultStatus {
    SUCCESS,
    FAILURE
};

enum class HardwareType {
    OLED,
    RTC,
    TH_SENSOR
};

class InitializingHardwareResult {
public:
    InitializingHardwareResult(ResultStatus status, const String& message, HardwareType type) : status(status), message(message), hardwareType(type) {}
    InitializingHardwareResult(ResultStatus status, const String& message) : status(status), message(message){};
    ResultStatus getStatus() const { return status; }
    String getMessage() const { return message; }
    HardwareType getHardwareType() const { return hardwareType; }
private:
    ResultStatus status;
    String message;
    HardwareType hardwareType;
};
#endif // INITIALIZING_HARDWARE_RESULT_H