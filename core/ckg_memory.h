#pragma once

#include "./ckg_types.h"

//========================== Begin Types ==========================
typedef void* (CKG_MemoryAllocator)(size_t);
typedef void (CKG_MemoryFree)(void*);
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief If you don't bind these callbacks a default callback will be used
     * 
     */
    void ckg_bind_allocator_callback(CKG_MemoryAllocator* func_allocator);
    void ckg_bind_free_callback(CKG_MemoryFree* func_allocator);

    void* MACRO_ckg_alloc(size_t allocation_size);
    void* ckg_reallocate(void* data, size_t old_allocation_size, size_t new_allocation_size);
    void* MACRO_ckg_free(void* data);

    Boolean ckg_memory_compare(const void* buffer_one, const void* buffer_two, u32 b1_allocation_size, u32 b2_allocation_size);
    void ckg_memory_copy(const void* source, void* destination, size_t source_size, size_t destination_size);
    void ckg_memory_move(const void* source, void* destination, size_t data_payload_source_size);
    void ckg_memory_zero(void* data, size_t data_size_in_bytes);
    void ckg_memory_set(u8* data, size_t data_size_in_bytes, u8 element);

    void ckg_memory_buffer_delete_index(const void* data, size_t size_in_bytes, u32 buffer_count, u32 index);

    u8* ckg_memory_advance_new_ptr(const void* data, size_t size_in_bytes);
    u8* ckg_memory_retreat_new_ptr(const void* data, size_t size_in_bytes);
    void* MACRO_memory_advance(const void* data, size_t size_in_bytes);
    void* MACRO_memory_retreat(const void* data, size_t size_in_bytes);

#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

#define ckg_memory_fill(buffer, buffer_count, fill_element) \
{														\
    for (int i = 0; i < buffer_count; i++) { 			\
        buffer[i] = fill_element;                       \
    }                                                  	\
}

/**
 * @brief Modifies the data pointer, if you just want a new pointer consider using 
 * ckg_memory_advance_new_ptr()
 * 
 */
#ifdef __cplusplus
    #define ckg_alloc(allocation_size) (decltype(data))MACRO_ckg_alloc(allocation_size)
    #define ckg_free(data) data = (decltype(data))MACRO_ckg_free(data)

    #define ckg_memory_advance(data, size_in_bytes) data = (decltype(data))MACRO_memory_advance(data, size_in_bytes)
    #define ckg_memory_retreat(data, size_in_bytes) data = (decltype(data))MACRO_memory_retreat(data, size_in_bytes)
    
#else
    #define ckg_alloc(allocation_size) MACRO_ckg_alloc(allocation_size)
    #define ckg_free(data) data = MACRO_ckg_free(data)

    #define ckg_memory_advance(data, size_in_bytes) data = MACRO_memory_advance(data, size_in_bytes)
    #define ckg_memory_retreat(data, size_in_bytes) data = MACRO_memory_retreat(data, size_in_bytes)
#endif