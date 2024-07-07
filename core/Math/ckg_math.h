#pragma once

#include "../ckg_types.h"
//========================== Begin Types ==========================
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
    float ckg_f32_abs(float val);
    double ckg_f64_abs(double val);

    s32 ckg_s32_abs(s32 val);
    s64 ckg_s64_abs(s64 val);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++
