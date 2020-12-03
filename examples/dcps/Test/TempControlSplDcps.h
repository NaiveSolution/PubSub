#ifndef TempControlSPLDCPS_H
#define TempControlSPLDCPS_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "TempControl.h"


extern c_metaObject __TempControl_tutorial__load (c_base base);

extern c_metaObject __tutorial_TemperatureScale__load (c_base base);
enum _tutorial_TemperatureScale {
    _tutorial_CELSIUS,
    _tutorial_FAHRENHEIT,
    _tutorial_KELVIN
};

extern const char *tutorial_TempSensorType_metaDescriptor[];
extern const c_ulong tutorial_TempSensorType_metaDescriptorArrLength;
extern const c_ulong tutorial_TempSensorType_metaDescriptorLength;
extern c_metaObject __tutorial_TempSensorType__load (c_base base);
struct _tutorial_TempSensorType ;
extern  v_copyin_result __tutorial_TempSensorType__copyIn(c_type dbType, const class tutorial::TempSensorType *from, struct _tutorial_TempSensorType *to);
extern  void __tutorial_TempSensorType__copyOut(const void *_from, void *_to);
struct _tutorial_TempSensorType {
    c_short id;
    c_float temp;
    c_float hum;
    enum _tutorial_TemperatureScale scale;
};

#undef OS_API
#endif
