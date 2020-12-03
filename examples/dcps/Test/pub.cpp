#include <iostream>
#include "TempControl_DCPS.hpp"
#include "FlowControl_DCPS.hpp"
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>

void temp_pub(int);
void flow_pub(int);

int main(int argc, char* argv[]){
    if (argc < 2) {
    std::cout << "USAGE:\n\t tspub <sensor-id>" << std::endl;
    return -1;
  }
  int sid = atoi(argv[1]);
  const int N = 100;

  temp_pub(sid);
  flow_pub(sid);
}

void flow_pub(int sid){

  std::system("OSPL_URI=file://$OSPL_HOME/etc/config/ospl1.xml");
  const dds::domain::qos::DomainParticipantQos qos;
  dds::domain::DomainParticipant dp(org::opensplice::domain::default_id(), &qos, );
  dds::topic::Topic<tutorial::TempSensorType> topic(dp, "TTempSensor");
  dds::pub::Publisher pub(dp);
  dds::pub::DataWriter<tutorial::TempSensorType> dw(pub, topic);
    
  const float avgT = 25;
  const float avgH = 0.6;
  const float deltaT = 5;
  const float deltaH = 0.15;
  // Initialize random number generation with a seed
  srandom(clock());
    
  // Write some temperature randomly changing around a set point
  float temp = avgT + ((random()*deltaT)/RAND_MAX);
  float hum  = avgH + ((random()*deltaH)/RAND_MAX);

  tutorial::TempSensorType sensor( sid, temp, hum, tutorial::TemperatureScale::CELSIUS );

  for (unsigned int i = 0; i < N; ++i) {
    dw.write(sensor);
    std::cout << "Sensor ID: " << sid << ", Temp = " << temp << ", Humidity = " << hum << std::endl; 
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 10 + 1));
    temp = avgT + ((random()*deltaT)/RAND_MAX);
    sensor.temp(temp); 
    hum = avgH + ((random()*deltaH)/RAND_MAX);
    sensor.hum(hum);
  }
  return 0;
}

void temp_pub(int sid){
  
  dds::domain::DomainParticipant dp(0);
  dds::topic::Topic<tutorial::TempSensorType> topic(dp, "TTempSensor");
  dds::pub::Publisher pub(dp);
  dds::pub::DataWriter<tutorial::TempSensorType> dw(pub, topic);
    
  const float avgT = 25;
  const float avgH = 0.6;
  const float deltaT = 5;
  const float deltaH = 0.15;
  // Initialize random number generation with a seed
  srandom(clock());
    
  // Write some temperature randomly changing around a set point
  float temp = avgT + ((random()*deltaT)/RAND_MAX);
  float hum  = avgH + ((random()*deltaH)/RAND_MAX);

  tutorial::TempSensorType sensor( sid, temp, hum, tutorial::TemperatureScale::CELSIUS );

  for (unsigned int i = 0; i < N; ++i) {
    dw.write(sensor);
    std::cout << "Sensor ID: " << sid << ", Temp = " << temp << ", Humidity = " << hum << std::endl; 
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 10 + 1));
    temp = avgT + ((random()*deltaT)/RAND_MAX);
    sensor.temp(temp); 
    hum = avgH + ((random()*deltaH)/RAND_MAX);
    sensor.hum(hum);
  }
  return 0;
}