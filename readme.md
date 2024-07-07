# CKG
The point of the ckit granular (ckg) is building out everything at a granular level  and then using these building block to build a good common use case version. so very few types and allocation is decided by the caller in most cases.

# How to build
1. ./bootstrap.ps1
2. ./build.ps1
2. ./run.ps1

- Collection of tools, data structures, and algorithms that I find useful

#### NOTE 
I consider CKG almost done I would like to revist the FileIO section but other than that this is a solid granular library
I have some tests but, i'm not confident in the validitiy of the string section.

# Goals

## CORE
- [x] ckg_types.c

### Assert (Not Cross-Platform)
- [x] ckg_assert.h
	- [x] ckg_assert_msg(expression, msg, ...)
	- [x] ckg_assert(expression)

- [ ] ckg_stack_trace.h (Only for windows plans are to use backtrace for gcc)
	- [x] ckg_stack_trace_dump()

### Logger (Cross-Platform)
- [x] ckg_logger.h
	- [x] CKG_LOG_FATAL(msg, ...)
	- [x] CKG_LOG_ERROR(msg, ...)
	- [x] CKG_LOG_WARN(msg, ...)
	- [x] CKG_LOG_DEBUG(msg, ...)
	- [x] CKG_LOG_SUCCESS(msg, ...)
	- [x] CKG_LOG_PRINT(msg, ...)

### String
- [x] ckg_cstring.h
	- [x] ckg_cstr_alloc(s1)
	- [x] ckg_cstr_append(string_buffer, string_buffer_capacity, to_append)
	- [x] ckg_cstr_append_char(string_buffer, string_buffer_capacity, char to_append)
	- [x] ckg_cstr_insert(string_buffer, string_buffer_capacity, to_insert, index)
	- [x] ckg_cstr_insert_char(string_buffer, string_buffer_capacity, char to_insert, index)
	- [x] ckg_cstr_copy(string_buffer, string_buffer_capacity, to_copy)
	- [x] ckg_cstr_random(dest, length)
	- [x] ckg_cstr_equal(s1, s2)
	- [x] ckg_cstr_length(c_string)
	- [x] ckg_cstr_clear(string_buffer)
	- [x] ckg_substring(string_buffer, start_range, end_range)
	- [x] ckg_cstr_contains(string_buffer, contains)
	- [x] ckg_cstr_index_of(string_buffer, sub_string)
	- [x] ckg_cstr_last_index_of(string_buffer, sub_string)
	- [x] ckg_cstr_split(string_buffer, delimitor)
	- [x] ckg_cstr_starts_with(string_buffer, starts_with)
	- [x] ckg_cstr_ends_with(string_buffer, ends_with)
	- [x] ckg_cstr_reverse(string_buffer)

### Memory
- [x] ckg_memory.h
    - [x] ckg_bind_alloc_callback(func_allocator)
    - [x] ckg_bind_free_callback(func_allocator)
    - [x] ckg_bind_allocator_plugin_callback(allocator_plugin, context)
    - [x] ckg_bind_free_plugin_callback(free_plugin, context)
    - [x] ckg_alloc(allocation_size)
    - [x] ckg_realloc(data, old_allocation_size, new_allocation_size)
    - [x] ckg_free(data)
    - [x] ckg_memory_compare(buffer_one, buffer_two, b1_allocation_size, b2_allocation_size)
    - [x] ckg_memory_copy(source, destination, source_size, destination_capacity)
    - [x] ckg_memory_move(source, destination, source_payload_size)
    - [x] ckg_memory_zero(data, data_size_in_bytes)
    - [x] ckg_memory_delete_index(data, data_capacity, element_size_in_bytes, index)

- [x] ckg_arena.h
	- [x] ckg_arena_create(allocation, name, flag)
	- [x] ckg_arena_push(arena, type)	
	- [x] ckg_arena_free(arena)
	- [x] ckg_arena_clear(arena)

### FileIO
- [ ] ckg_file_io.h // should revist this though not robust at all
	- [x] ckg_file_system_create(file_name)
	- [x] ckg_file_open(file_system)
	- [x] ckg_file_close(file_system)
	- [x] ckg_file_size(file_system)
	- [x] ckg_file_get_next_line(file_system)
	- [x] ckg_file_get_next_char(file_system)

## Tests
- [x] test_memory_functions()
- [x] test_arena_functions()
- [x] test_vector_functions()
- [ ] test_string_functions() // I don't trust that validity of these test not comprehensive enough I think