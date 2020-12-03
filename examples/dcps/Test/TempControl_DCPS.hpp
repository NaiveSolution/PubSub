#ifndef ISOCPP2_TempControl_H
#define ISOCPP2_TempControl_H

#include "dds/dds.hpp"

#include "TempControl.h"
#include "TempControlSplDcps.h"

#include "org/opensplice/topic/TopicTraits.hpp"
#include "org/opensplice/topic/DataRepresentation.hpp"

namespace org { namespace opensplice { namespace topic {
template <>
class TopicTraits<tutorial::TempSensorType>
{
public:
    static ::org::opensplice::topic::DataRepresentationId_t getDataRepresentationId()
    {
        return ::org::opensplice::topic::OSPL_REPRESENTATION;
    }

    static ::std::vector<os_uchar> getMetaData()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getTypeHash()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getExtentions()
    {
        return ::std::vector<os_uchar>();
    }

    static const char *getKeyList()
    {
        return "id";
    }

    static const char *getTypeName()
    {
        return "tutorial::TempSensorType";
    }

    static std::string getDescriptor()
    {
        const char *elements[] = {
            "<MetaData version=\"1.0.0\"><Module name=\"tutorial\"><Enum name=\"TemperatureScale\"><Element name=\"CELSIUS\" value=\"0\"/>",
"<Element name=\"FAHRENHEIT\" value=\"1\"/><Element name=\"KELVIN\" value=\"2\"/></Enum><Struct name=\"TempSensorType\">",
"<Member name=\"id\"><Short/></Member><Member name=\"temp\"><Float/></Member><Member name=\"hum\"><Float/>",
"</Member><Member name=\"scale\"><Type name=\"TemperatureScale\"/></Member></Struct></Module></MetaData>"
        };
        std::string descriptor;
        descriptor.reserve(452);
        for (int i = 0; i < 4; i++) {
            descriptor.append(elements[i]);
        }

        return descriptor;
    }

    static copyInFunction getCopyIn()
    {
        return (copyInFunction) __tutorial_TempSensorType__copyIn;
    }

    static copyOutFunction getCopyOut()
    {
        return (copyOutFunction) __tutorial_TempSensorType__copyOut;
    }
};
}}}

namespace dds { namespace topic {
template <>
struct topic_type_name<tutorial::TempSensorType>
{
    static std::string value()
    {
        return org::opensplice::topic::TopicTraits<tutorial::TempSensorType>::getTypeName();
    }
};
}}

REGISTER_TOPIC_TYPE(tutorial::TempSensorType)

#endif /* ISOCPP2_TempControl_H */
