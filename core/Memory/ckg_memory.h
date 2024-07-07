#pragma once

#include "../ckg_types.h"

//========================== Begin Types ==========================
typedef union CKG_MemoryContext {
    u64 i;
    double d;
    char cstr[8];
} CKG_MemoryContext;
typedef void* (CKG_MemoryAllocator)(size_t);
typedef void (CKG_MemoryFree)(void*);
typedef void (CKG_MemoryPlugin)(CKG_MemoryContext*);
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Note that the callback provided should zero out the memory allocation.
     * Failing to bind the allocation callback will result in a default allocation callback.
     */
    void ckg_bind_alloc_callback(CKG_MemoryAllocator* func_allocator);

    /**
     * @brief Failing to bind the callback will result in a default free callback.
     */
    void ckg_bind_free_callback(CKG_MemoryFree* func_allocator);

    
    /**
     * @brief Allows for arbitrary code execution before allocator callback
     * gives a small context for passing data
     * 
     * @param allocator_plugin 
     * @param context 
     */
    void ckg_bind_allocator_plugin_callback(CKG_MemoryPlugin* allocator_plugin, CKG_MemoryContext* context);
    void ckg_bind_free_plugin_callback(CKG_MemoryPlugin* free_plugin, CKG_MemoryContext* context);

    void* MACRO_ckg_alloc(size_t allocation_size);
    void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size);
    void* MACRO_ckg_free(void* data);

    /**
     * @brief Compares the bytes in the two buffers
     * 
     * @param buffer_one 
     * @param buffer_two 
     * @param b1_allocation_size 
     * @param b2_allocation_size 
     * @return Boolean 
     */
    Boolean ckg_memory_compare(const void* buffer_one, const void* buffer_two, u32 b1_allocation_size, u32 b2_allocation_size);
    void ckg_memory_copy(const void* source, void* destination, size_t source_size, size_t destination_capacity);
    void ckg_memory_move(const void* source, void* destination, size_t source_payload_size);
    void ckg_memory_zero(void* data, size_t data_size_in_bytes);

    void MACRO_ckg_memory_delete_index(void* data, u32 data_capacity, size_t element_size_in_bytes, u32 index);
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

#ifdef __cplusplus
    #define ckg_alloc(allocation_size) (decltype(data))MACRO_ckg_alloc(allocation_size)
    #define ckg_free(data) data = (decltype(data))MACRO_ckg_free(data)
    #define ckg_memory_delete_index(data, data_capacity, index) MACRO_ckg_memory_delete_index(data, data_capacity, sizeof(data[0]), index)
#else
    #define ckg_alloc(allocation_size) MACRO_ckg_alloc(allocation_size)
    #define ckg_free(data) data = MACRO_ckg_free(data)
    #define ckg_memory_delete_index(data, data_capacity, index) MACRO_ckg_memory_delete_index(data, data_capacity, sizeof(data[0]), index)
#endif