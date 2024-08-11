#pragma once

#include "ckg_types.h"

//========================== Begin Types ==========================
typedef void* (CKG_MemoryAllocator)(size_t);
typedef void (CKG_MemoryFree)(void*);
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
    void ckg_memory_copy(const void* source, void* destination, size_t source_size_in_bytes, size_t destination_size_in_bytes);
    void ckg_memory_zero(void* data, size_t data_size_in_bytes);

    void MACRO_ckg_memory_delete_index(void* data, u32 data_capacity, size_t element_size_in_bytes, u32 index);
    void MACRO_ckg_memory_insert_index(void* data, u32 data_capacity, size_t element_size_in_bytes, u32 index);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

#define ckg_memory_fill(buffer, buffer_count, fill_element) \
{														\
    for (u32 i = 0; i < buffer_count; i++) { 			\
        buffer[i] = fill_element;                       \
    }                                                  	\
}

#ifdef __cplusplus
    #define ckg_alloc(allocation_size) (decltype(data))MACRO_ckg_alloc(allocation_size)
    #define ckg_free(data) data = (decltype(data))MACRO_ckg_free(data)
    #define ckg_memory_delete_index(data, data_capacity, index) MACRO_ckg_memory_delete_index(data, data_capacity, sizeof(data[0]), index)
    #define ckg_memory_insert_index(data, data_capacity, index, element) MACRO_ckg_memory_insert_index(data, data_capacity,  element, sizeof(data[0]), index)
#else
    #define ckg_alloc(allocation_size) MACRO_ckg_alloc(allocation_size)
    #define ckg_free(data) data = MACRO_ckg_free(data)
    #define ckg_memory_delete_index(data, data_capacity, index) MACRO_ckg_memory_delete_index(data, data_capacity, sizeof(data[0]), index)
    #define ckg_memory_insert_index(data, data_capacity, element, index) MACRO_ckg_memory_insert_index(data, data_capacity, sizeof(data[0]), index); data[index] = element;
#endif


#if defined(CKG_IMPL)
    #include "ckg_types.h"
    #include "ckg_assert.h"
    #include "ckg_stack_trace.h"
    #include "ckg_math.h"

    void* ckg_memory_default_allocator(size_t allocation_size) {
        void* ret = malloc(allocation_size);
        ckg_memory_zero(ret, allocation_size);
        return ret;
    }

    void ckg_memory_default_free(void* data) {
        free(data);
    }

    internal CKG_MemoryAllocator* memory_allocate_callback = &ckg_memory_default_allocator;
    internal CKG_MemoryFree* memory_free_callback = &ckg_memory_default_free;

    void ckg_bind_alloc_callback(CKG_MemoryAllocator* allocator) {
        memory_allocate_callback = allocator;
    }

    void ckg_bind_free_callback(CKG_MemoryFree* free) {
        memory_free_callback = free;
    }

    void* MACRO_ckg_alloc(size_t allocation_size) {
        return memory_allocate_callback(allocation_size);
    }

    void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size) {
        void* ret = MACRO_ckg_alloc(new_allocation_size);
        ckg_memory_copy(data, ret, old_allocation_size, new_allocation_size);
        ckg_free(data);
        return ret;
    }

    void* MACRO_ckg_free(void* data) {
        memory_free_callback(data);
        data = NULLPTR;
        return data;
    }

    Boolean ckg_memory_compare(const void* buffer_one, const void* buffer_two, u32 buffer_one_size, u32 buffer_two_size) {
        ckg_assert(buffer_one);
        ckg_assert(buffer_two);

        if (buffer_one_size != buffer_two_size) {
            return FALSE;
        }

        u8* buffer_one_data = (u8*)buffer_one;
        u8* buffer_two_data = (u8*)buffer_two;
        for (u32 i = 0; i < buffer_one_size; i++) {
            if (buffer_one_data[i] != buffer_two_data[i]) {
                return FALSE;
            }
        }

        return TRUE;
    }

    void ckg_memory_copy(const void* source, void* destination, size_t source_size_in_bytes, size_t destination_size_in_bytes) {
        ckg_assert(source);
        ckg_assert(destination);
        ckg_assert(source_size_in_bytes <= destination_size_in_bytes);
        if (source_size_in_bytes == 0) {
            return;
        }

        u8* temp_data_copy = ckg_alloc(source_size_in_bytes);
        for (u32 i = 0; i < source_size_in_bytes; i++) {
            temp_data_copy[i] = ((u8*)source)[i];
        }

        for (u32 i = 0; i < source_size_in_bytes; i++) {
            ((u8*)destination)[i] = temp_data_copy[i];
        }

        ckg_free(temp_data_copy);
    }

    void ckg_memory_zero(void* data, size_t data_size_in_bytes) {
        for (u32 i = 0; i < data_size_in_bytes; i++) {
            ((u8*)data)[i] = 0;
        }
    }

    void MACRO_ckg_memory_delete_index(void* data, u32 data_capacity, size_t element_size_in_bytes, u32 index) {
        ckg_assert(index < data_capacity);
        ckg_assert(index >= 0);

        u8* byte_data = (u8*)data;

        size_t total_size = element_size_in_bytes * data_capacity;
        size_t source_offset = (index + 1) * element_size_in_bytes;
        size_t dest_offset =  index * element_size_in_bytes;

        size_t payload_source_size = total_size - source_offset;
        ckg_memory_copy(byte_data + source_offset, byte_data + dest_offset, payload_source_size, total_size - source_offset);
    }

    void MACRO_ckg_memory_insert_index(void* data, u32 data_capacity, size_t element_size_in_bytes, u32 index) {
        ckg_assert(index < data_capacity);
        ckg_assert(index >= 0);

        u8* byte_data = (u8*)data;

        size_t total_size = element_size_in_bytes * data_capacity;
        size_t source_offset = index * element_size_in_bytes;
        size_t dest_offset =  (index + 1) * element_size_in_bytes;

        size_t payload_source_size = total_size - source_offset;
        ckg_memory_copy(byte_data + source_offset, byte_data + dest_offset, payload_source_size, total_size - source_offset);
    }
#endif // CKG_IMPL