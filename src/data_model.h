#ifndef DATA_MODEL_H
#define DATA_MODEL_H
#include <Arduino.h>
#include <ws_data.h>

class THData {
public:
    THData(float temperature, float humidity, float heatIndex) : temperature(temperature), humidity(humidity), heatIndex(heatIndex) {}
    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getHeatIndex() const { return heatIndex; }
    struct WSTHData toWsTHData() const{
        return createWSTHData(temperature, humidity, heatIndex);
    };
private:
    float temperature;
    float humidity;
    float heatIndex;
};

class DateTimeData {
public:
    DateTimeData(const String& date, const String& time) : date(date), time(time) {}
    String getDate() const { return date; }
    String getTime() const { return time; }
    struct WSDateTimeData toWsDateTimeData() const{
        return createWSDateTimeData(date, time);
    };
private:
    String date;
    String time;
};

#endif // DATA_MODEL_H