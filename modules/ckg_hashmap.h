#pragma once

/*
    This hashmap uses double hashing
*/

#include "../core/ckg_types.h"
//========================== Begin Types ==========================
typedef struct HashMap HashMap;
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
    HashMap hashmap_create(size_t element_size);
    void hashmap_free(HashMap* hashmap);
    void hashmap_get(HashMap hashmap, char* key, void* value_returned);
    Boolean hashmap_has(HashMap hashmap, char* key);
    void hashmap_put(HashMap* hashmap, char* key, void* value_set, void* possible_value_returned);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++