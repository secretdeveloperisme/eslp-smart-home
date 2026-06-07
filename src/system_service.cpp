#ifndef SYSTEM_SERVICE_CPP
#define SYSTEM_SERVICE_CPP
#include "system_service.h"

SystemService::SystemService(HardwareController& hardwareController) : hardwareController(hardwareController) {
}
DateTimeData SystemService::getCurrentDateTime() {
    String date = hardwareController.getRTCSensor().getDateStr();
    String time = hardwareController.getRTCSensor().getTimeStr();
    return DateTimeData(date, time);
}

THData SystemService::getCurrentTHData() {
    float temperature = hardwareController.getTHSensor().getTemperature();
    float humidity = hardwareController.getTHSensor().getHumidity();
    float heatIndex = hardwareController.getTHSensor().calculateHeatIndex(temperature, humidity);
    return THData(temperature, humidity, heatIndex);
}

#endif // SYSTEM_SERVICE_CPP

