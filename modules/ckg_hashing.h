#pragma once

#include "../core/ckg_types.h"
//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
    u64 ckg_hash(unsigned char *str);
    void test_collisions();
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++



