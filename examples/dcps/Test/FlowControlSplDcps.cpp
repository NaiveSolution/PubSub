#include "FlowControl_DCPS.hpp"

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__tutorial2_FlowSensorType__copyIn(
    c_type dbType,
    const class ::tutorial2::FlowSensorType *from,
    struct _tutorial2_FlowSensorType *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) dbType;

    to->id = (c_short)from->id();
    to->flow_rate = (c_float)from->flow_rate();
    to->pressure = (c_float)from->pressure();
    return result;
}

void
__tutorial2_FlowSensorType__copyOut(
    const void *_from,
    void *_to)
{
    const struct _tutorial2_FlowSensorType *from = (const struct _tutorial2_FlowSensorType *)_from;
    class ::tutorial2::FlowSensorType *to = (class ::tutorial2::FlowSensorType *)_to;
    to->id((int16_t)from->id);
    to->flow_rate((float)from->flow_rate);
    to->pressure((float)from->pressure);
}

