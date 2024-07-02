#include "../ckg_types.h"
#include "../ckg_memory.h"
#include "../ckg_assert.h"
#include "../ckg_error.h"

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

void ckg_memory_bind_allocator_callback(CKG_MemoryAllocator* allocator) {
    memory_allocate_callback = allocator;
}

void ckg_memory_bind_free_callback(CKG_MemoryFree* free) {
    memory_free_callback = free;
}

void* MACRO_ckg_memory_allocate(size_t allocation_size) {
    return memory_allocate_callback(allocation_size);
}

void* ckg_memory_reallocate(void* data, size_t old_allocation_size, size_t new_allocation_size) {
    void* ret = MACRO_ckg_memory_allocate(new_allocation_size);
    ckg_errorable(ckg_memory_copy(data, ret, old_allocation_size, new_allocation_size));
    ckg_memory_free(data);
    return ret;
}

void* MACRO_ckg_memory_free(void* data) {
    memory_free_callback(data);
    data = NULLPTR;
    return data;
}

Boolean ckg_memory_compare(const void* buffer_one, const void* buffer_two, u32 buffer_one_size, u32 buffer_two_size) {
    ckg_assert(buffer_one, "ckg_memory_compare buffer_one IS NULL\n");
    ckg_assert(buffer_two, "ckg_memory_compare buffer_two IS NULL\n");

    if (buffer_one_size != buffer_two_size) {
        return FALSE;
    }

    u8* buffer_one_data = (u8*)buffer_one;
    u8* buffer_two_data = (u8*)buffer_two;
    for (int i = 0; i < buffer_one_size; i++) {
        if (buffer_one_data[i] != buffer_two_data[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

void ckg_memory_copy(const void* source, void* destination, size_t source_size, size_t destination_size) {
    ckg_assert(source, "MEMORY COPY SOURCE IS NULL\n");
    ckg_assert(destination, "MEMORY COPY SOURCE IS NULL\n");
    ckg_assert((source_size <= destination_size), "MEMORY COPY SOURCE IS TOO BIG FOR DESTINATION\n");

    for (int i = 0; i < source_size; i++) {
        u8 temp = ((u8*)source)[i];
        ((u8*)destination)[i] = temp;
    }
}

void ckg_memory_move(void* buffer, size_t buffer_capacity, size_t offset_into_buffer, size_t data_patload_size) {
    ckg_assert(buffer, "MEMORY MOVE buffer IS NULL\n");
    ckg_assert((data_patload_size + offset_into_buffer <= buffer_capacity), "MEMORY MOVE OFFSET IS TOO BIG FOR DESTINATION\n");
    if (data_patload_size == 0) {
        return;
    }

    // Date: June 30, 2024
    // TODO(Jovanni): If the offset is greater than data_payload_size then its not overlapping
    // if its not overlapping you don't have to copy
    // also I think its possible not not ckg_memory_copy the whole array i should be able to get by with just a constant time temp variable
    // to store the next byte value

    u8* data_payload = ckg_memory_allocate(data_patload_size);
    ckg_errorable(ckg_memory_copy(buffer, data_payload, data_patload_size, data_patload_size));
    u8* dest_ptr = ckg_memory_advance_new_ptr(buffer, offset_into_buffer);

    for (int i = 0; i < data_patload_size; i++) {
        ((u8*)dest_ptr)[i] = data_payload[i];
    }
    ckg_memory_free(data_payload);
}

void ckg_memory_zero(void* data, size_t data_size_in_bytes) {
    for (int i = 0; i < data_size_in_bytes; i++) {
        ((u8*)data)[i] = 0;
    }
}

void ckg_memory_set(u8* data, size_t data_size_in_bytes, u8 element) {
    for (int i = 0; i < data_size_in_bytes; i++) {
        ((u8*)data)[i] = element;
    }
}

/**
 * @brief O(n)
 * 
 * @param data 
 * @param size_in_bytes 
 * @param buffer_count 
 * @param index 
 */
void ckg_memory_buffer_delete_index(const void* data, size_t size_in_bytes, u32 buffer_count, u32 index) {
    u32 size_of_element = size_in_bytes / buffer_count;

    u8* source_ptr = ckg_memory_advance_new_ptr(data, (index + 1) * size_of_element);
    u8* dest_ptr = ckg_memory_advance_new_ptr(data, index * size_of_element);

    u32 source_ptr_size = (buffer_count - (index + 1)) * size_of_element;
    u32 dest_ptr_size = (buffer_count - (index)) * size_of_element;
    ckg_memory_copy(source_ptr, dest_ptr, source_ptr_size, dest_ptr_size);
}

u8* ckg_memory_advance_new_ptr(const void* data, size_t size_in_bytes) {
    return ((u8*)data) + size_in_bytes;
}

u8* ckg_memory_retreat_new_ptr(const void* data, size_t size_in_bytes) {
    return ((u8*)data) - size_in_bytes;
}

void* MACRO_memory_advance(const void* data, size_t size_in_bytes) {
    return ((u8*)data) + size_in_bytes;
}

void* MACRO_memory_retreat(const void* data, size_t size_in_bytes) {
    return ((u8*)data) - size_in_bytes;
}