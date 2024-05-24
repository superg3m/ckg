#include "../include/ckg.h"

#pragma region MEMORY
	internal ckg_MemoryAllocator_func* memory_allocator_callback = NULLPTR;
	internal ckg_MemoryFree_func* memory_free_callback = NULLPTR;

	void* ckg_memory_default_allocator(u32 allocation_size) {
		void* ret = malloc(allocation_size);
		memory_zero(ret, sizeof(allocation_size));
		return ret;
	}

	void* ckg_memory_default_free(void* data) {
		free(data);
		data = NULLPTR;
		return data;
	}

	void ckg_memory_bind_allocator_callback(ckg_MemoryAllocator_func* func_allocator) {
		memory_allocator_callback = func_allocator;
	}

	void ckg_memory_bind_free_callback(ckg_MemoryFree_func* func_free) {
		memory_free_callback = func_free;
	}

	void* MACRO_ckg_memory_allocate(u32 allocation_size) {
		if (memory_allocator_callback) {
			return memory_allocator_callback(allocation_size);
		} else {
			return ckg_memory_default_allocator(allocation_size);
		}
	}

	void* MACRO_ckg_memory_reallocate(void* data, u32 old_allocation_size, u32 new_allocation_size) {
		void* ret = MACRO_ckg_memory_allocate(new_allocation_size);
		memory_copy(data, ret, old_allocation_size, new_allocation_size);
		ckg_memory_free(data);
		return ret;
	}

	void* MACRO_ckg_memory_free(void* data) {
		if (memory_free_callback) {
			data = memory_free_callback(data);
			return data;
		} else {
			ckg_memory_default_free(data);
			data = NULLPTR;
			return data;
		}
	}

	Boolean memory_byte_compare(const void* buffer_one, const void* buffer_two, u32 buffer_one_size, u32 buffer_two_size) {
		ckg_assert_in_function(buffer_one, "memory_byte_compare buffer_one IS NULL\n");
		ckg_assert_in_function(buffer_two, "memory_byte_compare buffer_two IS NULL\n");

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
#pragma endregion

#pragma region STRING
	//************************* Begin Functions *************************
	u32 ckg_cstring_length(const char* cstring) {
		u32 length = 0;
		char* cursor = (char*)cstring;
		while(*cursor++ != '\0') {
			length++;
		}
		return length;
	}

	Boolean ckg_string_compare(const char* s1, const char* s2) {
		ckg_assert_in_function(s1, "string_compare: first argument is not valid | null\n");
		ckg_assert_in_function(s2, "string_compare: second argument is not valid | null\n");

		u32 s1_length = ckg_cstring_length(s1);
		u32 s2_length = ckg_cstring_length(s2);

		return memory_byte_compare(s1, s2, s1_length, s2_length);
	}

	void ckg_string_insert(char* string_buffer, u32 string_buffer_size, const u32 index, const char* source) {
		ckg_assert_in_function(string_buffer, "string_insert: string_buffer is not valid | null\n");
		ckg_assert_in_function(source, "string_insert: source is not valid | null\n");

		u32 string_buffer_length = ckg_cstring_length(string_buffer);
		u32 source_length = ckg_cstring_length(source);

		ckg_assert_in_function(index >= 0 && index <= string_buffer_length, "Index out of bounds");
		ckg_assert_in_function(string_buffer_length + source_length < string_buffer_size, "string_insert: string_buffer_size is %d but new valid cstring length is %d + %d = %d\n", string_buffer_size, string_buffer_length, source_length + 1, string_buffer_length + source_length + 1);

		// Date: May 18, 2024
		// TODO(Jovanni): Test this
		for (int i = string_buffer_length; i > index; i--) {
			string_buffer[(i - 1) + source_length] = string_buffer[i - 1];
			string_buffer[i - 1] = 'x';
		}
		
		u8* dest_ptr = memory_advance_new_ptr(string_buffer, index);
		// Date: May 18, 2024
		// NOTE(Jovanni): We don't want source_length + 1 because we don't want to copy the null terminator
		memory_copy(source, dest_ptr, source_length, string_buffer_size);
	}

	void ckg_string_insert_char(char* string_buffer, u32 string_buffer_size, const u32 index, const char source) {
		ckg_assert_in_function(string_buffer, "string_insert_char string_buffer is not valid | null\n");
		ckg_assert_in_function(source, "string_insert_char source is not valid | null\n");

		u32 string_buffer_length = ckg_cstring_length(string_buffer);
		u32 source_length = 1;

		ckg_assert_in_function(index >= 0 && string_buffer_length + source_length < string_buffer_size, "string_compare second argument is not valid | null\n");

		// Date: May 18, 2024
		// TODO(Jovanni): Test this
		for (int i = string_buffer_length; i > index; i--) {
			string_buffer[(i - 1) + source_length] = string_buffer[(i - 1)];
		}

		string_buffer[index] = source;
	}

	void ckg_string_append(char* string_buffer, u32 string_buffer_size, const char* source) {
		u32 string_buffer_length = ckg_cstring_length(string_buffer);
		ckg_string_insert(string_buffer, string_buffer_size, string_buffer_length, source);
	}

	void ckg_string_append_char(char* string_buffer, u32 string_buffer_size, const char source) {
		u32 string_buffer_length = ckg_cstring_length(string_buffer);
		ckg_string_insert_char(string_buffer, string_buffer_size, string_buffer_length, source);
	}

	void ckg_string_clear(char* string_buffer, u32 string_buffer_size) {
		ckg_assert_in_function(string_buffer, "ckg_string_clear: string_buffer is not valid | null\n");

		memory_zero(string_buffer, string_buffer_size);
	}

	void ckg_string_copy(char* string_buffer, u32 string_buffer_size, const char* source) {
		ckg_assert_in_function(string_buffer, "ckg_string_copy: string_buffer is not valid | null\n");
		ckg_assert_in_function(source, "ckg_string_copy: source is not valid | null\n");
		u32 source_length = ckg_cstring_length(source);
		ckg_string_clear(string_buffer, string_buffer_size);

		// Date: May 18, 2024
		// NOTE(Jovanni): We want to use source_length + 1 because we want to include the null terminator
		memory_copy(source, string_buffer, source_length + 1, string_buffer_size);
	}
	//************************** End Functions **************************
#pragma endregion

#pragma region ARENA

#define ARENA_DEFAULT_ALLOCATION_SIZE MegaBytes(1)

Boolean ckg_CKG_ARENA_FLAG_is_set(CKG_Arena* arena, CKG_ArenaFlag flag) {
    return arena->flag == flag;
}

CKG_Arena MACRO_ckg_arena_create(u32 allocation_size, const char* name, CKG_ArenaFlag flag) {
    CKG_Arena arena;
    arena.name = name;
    arena.flag = flag;
    arena.capacity = allocation_size;
    arena.used = 0;
    arena.base_address = ckg_memory_allocate(allocation_size != 0 ? allocation_size : ARENA_DEFAULT_ALLOCATION_SIZE);
    return arena;
}

void ckg_arena_free(CKG_Arena* arena) {
    ckg_assert_in_function(arena && arena->base_address, "arena_free: arena is null\n");
    ckg_memory_free(arena->base_address);
}

void ckg_arena_clear(CKG_Arena* arena) {
    ckg_assert_in_function(arena && arena->base_address, "arena_free: arena is null\n");
    memory_zero(arena->base_address, arena->used);
    arena->used = 0;
}

void* MACRO_ckg_arena_push(CKG_Arena* arena, u32 element_size) {
    // Date: May 11, 2024
    // TODO(Jovanni): For right now just assert if you don't have enough memory but later on make it grow.
    ckg_assert_in_function(arena && arena->base_address, "arena_push: arena is null\n");

    if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_DEFAULT)) {
        ckg_assert_in_function((arena->used + element_size <= arena->capacity), "arena_push: (default arena) can't push element ran out of memory\n");
        
    } else if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_CIRCULAR)) {
		if ((arena->used + element_size > arena->capacity)) {
			arena->used = 0;
			ckg_assert_in_function((arena->used + element_size <= arena->capacity), "arena_push: can't push element ran out of memory, circular buffer\n");
        }
    } else if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_VECTOR)) {
        if ((arena->used + element_size > arena->capacity)) {
            arena->capacity += element_size;
            arena->capacity *= 2;
            arena->base_address = ckg_memory_reallocate(arena->base_address, arena->capacity, arena->capacity * 2);
        	ckg_assert_in_function(arena->base_address, "arean_push: invalid reallocation address given");
        }
    } else {
        ckg_assert_in_function(FALSE, "arean_push: invalid arena flag set");
    }

    u8* ret = memory_advance_new_ptr(arena->base_address, arena->used);
	arena->used += element_size;

    return ret;
}
#pragma endregion