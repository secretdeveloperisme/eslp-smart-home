#ifndef WS_DATA_H
#define WS_DATA_H
#include <Arduino.h>
#include <stdint.h>

struct __attribute__((packed)) WSTHData{
    float temperature;
    float humidity;
    float heatIndex;
};


struct __attribute__((packed)) WSDateTimeData{
    char date[11]; // Format: YYYY-MM-DD
    char time[9];  // Format: HH:MM:SS
};


struct __attribute__((packed)) WSRelayData {
    bool relay1Status;
    bool relay2Status;
};

struct WSTHData createWSTHData(float temperature, float humidity, float heatIndex);
struct WSDateTimeData createWSDateTimeData(const String& date, const String& time);
struct WSRelayData createWSRelayData(bool relay1Status, bool relay2Status);

struct __attribute__((packed)) WSSensorData {
    WSTHData thData;
    WSDateTimeData dateTimeData;
    WSRelayData relayData;
};

struct WSSensorData createWSSensorData(WSTHData thData, WSDateTimeData dateTimeData, WSRelayData relayData);

enum MessageType : uint8_t{
    GET_SENSOR_DATA = 0x01,
    SENSOR_DATA_RESPONSE = 0x02,
    SET_RELAY_STATUS = 0x03,
    SET_RELAY_STATUS_RESPONSE = 0x04,
};

struct __attribute__((packed)) WSMessage {
    MessageType type;
    uint32_t payloadLength;
    uint8_t *payload;
};

struct WSMessage createWSMessage(MessageType type, uint8_t *payload, uint32_t payloadLength);
int8_t convertWSMessageToBuffer(const WSMessage& message, uint8_t* buffer, size_t bufferSize);
size_t calculateWSMessageSize(const WSMessage& message);
#endif // WS_DATA_H