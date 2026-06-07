#ifndef TH_SENSOR_CPP
#define TH_SENSOR_CPP
#include "th_sensor.h"

void THSensor::begin(){
  this->dht22->begin();
}
float THSensor::getTemperature(){
  return this->dht22->readTemperature();
}
float THSensor::getHumidity(){
  return this->dht22->readHumidity();
}
bool THSensor::getStatus()
{
  return !isnan(this->getTemperature()) && !isnan(this->getHumidity());
}
float THSensor::calculateHeatIndex(float temperature, float humidity)
{
    return this->dht22->computeHeatIndex(temperature, humidity, false);
}

#endif