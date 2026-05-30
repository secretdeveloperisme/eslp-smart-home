#ifndef TH_SENSOR_H
#define TH_SENSOR_H
#include <DHT.h>

class THSensor{
  private:
    DHT *dht22;
  public:
    THSensor(unsigned int pinIn){
      dht22 = new DHT(pinIn, DHT22);
    }
    void begin();
    float getTemperature();
    float getHumidity();
    float calculateHeatIndex(float temperature, float humidity);
    ~THSensor(){
      delete dht22;
    }

};


#endif