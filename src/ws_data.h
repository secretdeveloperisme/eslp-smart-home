#ifndef WS_DATA_H
#define WS_DATA_H
#include <Arduino.h>
#include <stdint.h>

struct __attribute__((packed)) WSTHData{
    float temperature;
    float humidity;
    float heatIndex;
};

struct WSTHData createWSTHData(float temperature, float humidity, float heatIndex);

struct __attribute__((packed)) WSDateTimeData{
    char date[11]; // Format: YYYY-MM-DD
    char time[9];  // Format: HH:MM:SS
};

struct WSDateTimeData createWSDateTimeData(const String& date, const String& time);

struct __attribute__((packed)) WSSensorData {
    WSTHData thData;
    WSDateTimeData dateTimeData;
};

struct WSSensorData createWSSensorData(WSTHData thData, WSDateTimeData dateTimeData);

enum MessageType : uint8_t{
    GET_SENSOR_DATA = 0x01,
    SENSOR_DATA_RESPONSE = 0x02
};

struct __attribute__((packed)) WSMessage {
    MessageType type;
    uint32_t payloadLength;
    uint8_t *payload;
};

struct WSMessage createWSMessage(MessageType type, WSSensorData sensorData);
int8_t convertWSMessageToBuffer(const WSMessage& message, uint8_t* buffer, size_t bufferSize);
size_t calculateWSMessageSize(const WSMessage& message);
#endif // WS_DATA_H