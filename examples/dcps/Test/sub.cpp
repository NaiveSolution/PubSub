// -- Std C/C++ Include
#include <iostream>
#include <algorithm>
#include "TempControl_DCPS.hpp"
#include "FlowControl_DCPS.hpp"
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono> 


int main(int argc, char* argv[]) {

  dds::domain::DomainParticipant dp(0);
  dds::topic::Topic<tutorial::TempSensorType> topic(dp, "TTempSensor");
  dds::sub::Subscriber sub(dp);
  dds::sub::DataReader<tutorial::TempSensorType> dr(sub, topic);

  while (true) {
    auto samples = dr.take();
    for (auto it = samples.begin(); it != samples.end(); ++it){
      const dds::sub::Sample<tutorial::TempSensorType>& s = *it;
      auto data = s.data();
      std::cout << "Reading sensor ID: " << data.id() << 
                   ", Temperature = " << data.temp() <<
                   ", Humidity = " << data.hum() << std::endl;
    }
    /* std::for_each(samples.begin(),
		  samples.end(),
		  [](const dds::sub::Sample<tutorial::TempSensorType>& s) {
		    std::cout << s.data().id() << std::endl;
		  }); */
    //std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}