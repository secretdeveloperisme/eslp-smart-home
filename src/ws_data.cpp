#ifndef WS_DATA_CPP
#define WS_DATA_CPP
#include "ws_data.h"


struct WSTHData createWSTHData(float temperature, float humidity, float heatIndex) {
    WSTHData data;
    data.temperature = temperature;
    data.humidity = humidity;
    data.heatIndex = heatIndex;
    return data;
}

struct WSDateTimeData createWSDateTimeData(const String& date, const String& time) {
    WSDateTimeData data;
    date.toCharArray(data.date, sizeof(data.date));
    time.toCharArray(data.time, sizeof(data.time));
    return data;
}

struct WSSensorData createWSSensorData(WSTHData thData, WSDateTimeData dateTimeData) {
    WSSensorData data;
    data.thData = thData;
    data.dateTimeData = dateTimeData;
    return data;
}

struct WSMessage createWSMessage(MessageType type, WSSensorData sensorData) {
    WSMessage message;
    message.type = type;
    message.payloadLength = sizeof(WSSensorData);
#ifdef DEBUG
    Serial.printf("Sensor data size: %u bytes\n", sizeof(WSSensorData));
    for (size_t i = 0; i < sizeof(WSSensorData); i++) {
        Serial.printf("%02x ", ((uint8_t*)&sensorData)[i]);
    }
#endif
    Serial.println();  
    message.payload = new uint8_t[message.payloadLength]; 
    memcpy(message.payload, &sensorData, message.payloadLength);
    return message;
}

int8_t convertWSMessageToBuffer(const WSMessage& message, uint8_t* buffer, size_t bufferSize) {
    size_t messageSize = sizeof(message.type) + sizeof(message.payloadLength) + message.payloadLength;
    if (bufferSize < messageSize) {
        return -1; // Buffer too small
    }
    memcpy(buffer, &message.type, sizeof(message.type));
    memcpy(buffer + sizeof(message.type), &message.payloadLength, sizeof(message.payloadLength));
    memcpy(buffer + sizeof(message.type) + sizeof(message.payloadLength), message.payload, message.payloadLength);
    return 0;
}

size_t calculateWSMessageSize(const WSMessage& message) {
    return sizeof(MessageType) + sizeof(uint32_t) + message.payloadLength;
}
#endif // WS_DATA_H