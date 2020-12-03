#ifndef ISOCPP2_FlowControl_H
#define ISOCPP2_FlowControl_H

#include "dds/dds.hpp"

#include "FlowControl.h"
#include "FlowControlSplDcps.h"

#include "org/opensplice/topic/TopicTraits.hpp"
#include "org/opensplice/topic/DataRepresentation.hpp"

namespace org { namespace opensplice { namespace topic {
template <>
class TopicTraits<tutorial2::FlowSensorType>
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
        return "tutorial2::FlowSensorType";
    }

    static std::string getDescriptor()
    {
        const char *elements[] = {
            "<MetaData version=\"1.0.0\"><Module name=\"tutorial2\"><Struct name=\"FlowSensorType\"><Member name=\"id\">",
"<Short/></Member><Member name=\"flow_rate\"><Float/></Member><Member name=\"pressure\"><Float/></Member>",
"</Struct></Module></MetaData>"
        };
        std::string descriptor;
        descriptor.reserve(240);
        for (int i = 0; i < 3; i++) {
            descriptor.append(elements[i]);
        }

        return descriptor;
    }

    static copyInFunction getCopyIn()
    {
        return (copyInFunction) __tutorial2_FlowSensorType__copyIn;
    }

    static copyOutFunction getCopyOut()
    {
        return (copyOutFunction) __tutorial2_FlowSensorType__copyOut;
    }
};
}}}

namespace dds { namespace topic {
template <>
struct topic_type_name<tutorial2::FlowSensorType>
{
    static std::string value()
    {
        return org::opensplice::topic::TopicTraits<tutorial2::FlowSensorType>::getTypeName();
    }
};
}}

REGISTER_TOPIC_TYPE(tutorial2::FlowSensorType)

#endif /* ISOCPP2_FlowControl_H */
