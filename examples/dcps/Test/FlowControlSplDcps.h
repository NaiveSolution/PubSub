#ifndef FlowControlSPLDCPS_H
#define FlowControlSPLDCPS_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "FlowControl.h"


extern c_metaObject __FlowControl_tutorial2__load (c_base base);

extern const char *tutorial2_FlowSensorType_metaDescriptor[];
extern const c_ulong tutorial2_FlowSensorType_metaDescriptorArrLength;
extern const c_ulong tutorial2_FlowSensorType_metaDescriptorLength;
extern c_metaObject __tutorial2_FlowSensorType__load (c_base base);
struct _tutorial2_FlowSensorType ;
extern  v_copyin_result __tutorial2_FlowSensorType__copyIn(c_type dbType, const class tutorial2::FlowSensorType *from, struct _tutorial2_FlowSensorType *to);
extern  void __tutorial2_FlowSensorType__copyOut(const void *_from, void *_to);
struct _tutorial2_FlowSensorType {
    c_short id;
    c_float flow_rate;
    c_float pressure;
};

#undef OS_API
#endif
