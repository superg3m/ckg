#include "../ckg_types.h"
#include "../Memory/ckg_memory.h"
#include "../Assert/ckg_assert.h"
#include "../Assert/ckg_stack_trace.h"
#include "../Math/ckg_math.h"

void* ckg_memory_default_allocator(size_t allocation_size) {
    void* ret = malloc(allocation_size);
    ckg_memory_zero(ret, allocation_size);
    return ret;
}

void ckg_memory_default_free(void* data) {
    free(data);
}

void ckg_memory_default_allocator_plugin() {
    return;
}

void ckg_memory_default_free_plugin() {
    return;
}

internal CKG_MemoryAllocator* memory_allocate_callback = &ckg_memory_default_allocator;
internal CKG_MemoryFree* memory_free_callback = &ckg_memory_default_free;
internal CKG_Plugin* ckg_memory_allocator_plugin_callback = &ckg_memory_default_allocator_plugin;
internal CKG_Plugin* ckg_memory_free_plugin_callback = &ckg_memory_default_free_plugin;

void ckg_bind_alloc_callback(CKG_MemoryAllocator* allocator) {
    memory_allocate_callback = allocator;
}

void ckg_bind_free_callback(CKG_MemoryFree* free) {
    memory_free_callback = free;
}

void ckg_bind_allocator_plugin_callback(CKG_Plugin* plugin) {
    ckg_memory_allocator_plugin_callback = plugin;
}

void ckg_bind_free_plugin_callback(CKG_Plugin* plugin) {
    ckg_memory_allocator_plugin_callback = plugin;
}

void* MACRO_ckg_alloc(size_t allocation_size) {
    ckg_memory_allocator_plugin_callback();
    return memory_allocate_callback(allocation_size);
}

void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size) {
    void* ret = MACRO_ckg_alloc(new_allocation_size);
    ckg_memory_copy(data, ret, old_allocation_size, new_allocation_size);
    ckg_free(data);
    return ret;
}

void* MACRO_ckg_free(void* data) {
    ckg_memory_allocator_plugin_callback();
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
    for (int i = 0; i < buffer_one_size; i++) {
        if (buffer_one_data[i] != buffer_two_data[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

void ckg_memory_copy(const void* source, void* destination, size_t source_size, size_t destination_capacity) {
    ckg_assert(source);
    ckg_assert(destination);
    ckg_assert((source_size <= destination_capacity));

    for (int i = 0; i < source_size; i++) {
        u8 temp = ((u8*)source)[i];
        ((u8*)destination)[i] = temp;
    }
}

void ckg_memory_move(const void* source, void* destination, size_t source_payload_size) {
    ckg_assert(source);
    ckg_assert(destination);

    if (source_payload_size == 0) {
        return;
    }

    u8* data_payload = ckg_alloc(source_payload_size);
    ckg_memory_copy(source, data_payload, source_payload_size, source_payload_size);
    for (int i = 0; i < source_payload_size; i++) {
        ((u8*)destination)[i] = data_payload[i];
    }

    ckg_free(data_payload);
}

void ckg_memory_zero(void* data, size_t data_size_in_bytes) {
    for (int i = 0; i < data_size_in_bytes; i++) {
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
    ckg_memory_move(byte_data + source_offset, byte_data + dest_offset, payload_source_size);
}