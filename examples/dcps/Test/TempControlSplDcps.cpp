#include "TempControl_DCPS.hpp"

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__tutorial_TempSensorType__copyIn(
    c_type dbType,
    const class ::tutorial::TempSensorType *from,
    struct _tutorial_TempSensorType *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) dbType;

    to->id = (c_short)from->id();
    to->temp = (c_float)from->temp();
    to->hum = (c_float)from->hum();
    if((((c_long)from->scale()) >= 0) && (((c_long)from->scale()) < 3) ){
        to->scale = (enum _tutorial_TemperatureScale)from->scale();
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'tutorial::TempSensorType.scale' of type 'TemperatureScale' is out of range.");
        result = V_COPYIN_RESULT_INVALID;
    }
    return result;
}

void
__tutorial_TempSensorType__copyOut(
    const void *_from,
    void *_to)
{
    const struct _tutorial_TempSensorType *from = (const struct _tutorial_TempSensorType *)_from;
    class ::tutorial::TempSensorType *to = (class ::tutorial::TempSensorType *)_to;
    to->id((int16_t)from->id);
    to->temp((float)from->temp);
    to->hum((float)from->hum);
    to->scale((tutorial::TemperatureScale)from->scale);
}

