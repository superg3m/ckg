#include "../include/ckg_memory.h"
#include "../include/ckg_assert.h"

Boolean memory_byte_compare(const void* buffer_one, const void* buffer_two, u32 buffer_one_size, u32 buffer_two_size) {
  	ckg_assert_in_function(buffer_one, "memory_byte_compare buffer_one IS NULL\n");
  	ckg_assert_in_function(buffer_two, "memory_byte_compare buffer_two IS NULL\n");

	if (buffer_one_size != buffer_one_size) {
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

void memory_copy(const void* source, void* destination, u32 source_size, u32 destination_size) {
  	ckg_assert_in_function(source, "MEMORY COPY SOURCE IS NULL\n");
  	ckg_assert_in_function(destination, "MEMORY COPY SOURCE IS NULL\n");
  	ckg_assert_in_function((source_size <= destination_size), "MEMORY COPY SOURCE IS TOO BIG FOR DESTINATION\n");

  	for (int i = 0; i < source_size; i++) {
  	    ((u8*)destination)[i] = ((u8*)source)[i];
  	}
}

void memory_zero(void* data, u32 data_size_in_bytes) {
  	for (int i = 0; i < data_size_in_bytes; i++) {
  	    ((u8*)data)[i] = 0;
  	}
}

void memory_set(u8* data, u32 data_size_in_bytes, u8 element) {
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
void memory_buffer_delete_index(const void* data, u32 size_in_bytes, u32 buffer_count, u32 index) {
	u32 size_of_element = size_in_bytes / buffer_count;

	u8* source_ptr = memory_advance_new_ptr(data, (index + 1) * size_of_element);
	u8* dest_ptr = memory_advance_new_ptr(data, index * size_of_element);

	u32 source_ptr_size = (buffer_count - (index + 1)) * size_of_element;
	u32 dest_ptr_size = (buffer_count - (index)) * size_of_element;
	memory_copy(source_ptr, dest_ptr, source_ptr_size, dest_ptr_size);
}

u8* memory_advance_new_ptr(const void* data, u32 size_in_bytes) {
  	u8* base_address = (u8*)data;
  	base_address += size_in_bytes;
  	return base_address;
}

u8* memory_retreat_new_ptr(const void* data, u32 size_in_bytes) {
    u8* base_address = (u8*)data;
    base_address -= size_in_bytes;
    return base_address;
}

void* MACRO_memory_byte_advance(const void* data, u32 size_in_bytes) {
	u8* base_address = (u8*)data;
  	base_address += size_in_bytes;
  	return base_address;
}

void* MACRO_memory_byte_retreat(const void* data, u32 size_in_bytes) {
	u8* base_address = (u8*)data;
  	base_address -= size_in_bytes;
  	return base_address;
}