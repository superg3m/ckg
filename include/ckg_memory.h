#pragma once
/*===========================================================
 * File: ckg_memory.h
 * Date: May 18, 2024
 * Creator: Jovanni Djonaj
===========================================================*/
#include "./ckg_types.h"

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif

    Boolean memory_byte_compare(const void* buffer_one, const void* buffer_two, u32 buffer_one_size, u32 buffer_two_size);
    void memory_copy(const void* source, void* destination, u32 source_size, u32 destination_size);
    void memory_zero(void* data, u32 data_size_in_bytes);

    u8* memory_advance_new_ptr(const void* data, u32 size_in_bytes);
    u8* memory_retreat_new_ptr(const void* data, u32 size_in_bytes);
    void* MACRO_memory_byte_advance(const void* data, u32 size_in_bytes);
    void* MACRO_memory_byte_retreat(const void* data, u32 size_in_bytes);

#ifdef __cplusplus
}
#endif
//************************** End Functions **************************
