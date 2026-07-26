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

struct WSSensorData createWSSensorData(WSTHData thData, WSDateTimeData dateTimeData, WSRelayData relayData) {
    WSSensorData data;
    data.thData = thData;
    data.dateTimeData = dateTimeData;
    data.relayData = relayData;
    return data;
}

WSRelayData createWSRelayData(bool relay1Status, bool relay2Status)
{
    WSRelayData data;
    data.relay1Status = relay1Status;
    data.relay2Status = relay2Status;
    return data;
}

struct WSMessage createWSMessage(MessageType type, uint8_t *payload, uint32_t payloadLength) {
    WSMessage message;
    message.type = type;
    message.payloadLength = payloadLength;
#ifdef DEBUG
    Serial.printf("Payload size: %u bytes\n", payloadLength);
    for (size_t i = 0; i < payloadLength; i++) {
        Serial.printf("%02x ", payload[i]);
    }
#endif
    Serial.println();  
    message.payload = new uint8_t[message.payloadLength]; 
    memcpy(message.payload, payload, message.payloadLength);
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