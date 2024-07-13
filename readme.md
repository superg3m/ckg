# CKG's Core Thesis
- The point of the ckit granular (ckg) is building out everything at a granular level.
	- Valid Allocations are passed as parameters along with the capacity in most cases.
	- Using this small library to build out [CKIT](https://github.com/superg3m/ckit) (A much more sophisticated C library build)
- This library will be completly cross-platform
- Collection of tools, data structures, and algorithms that I find useful
- ckg can't allocate in string functions or any other functions on its own because if it did the ckit memory tracker would not work

#### NOTE 
I consider CKG almost done I would like to revist the FileIO section but other than that this is a solid granular library
I have some tests but, i'm not confident in the validitiy of the string section.

# How to build using [c-build](https://github.com/superg3m/c-build)
1. ./bootstrap.ps1
2. ./build.ps1 or ./build.ps1 -debug
2. ./debug.ps1
2. ./run.ps1

## CORE ( All Cross-Platform)
- [x] ckg_types.c

### Assert
- [x] ckg_assert.h
	- [x] ckg_assert_msg(expression, msg, ...)
	- [x] ckg_assert(expression)

- [ ] ckg_stack_trace.h (Only for windows plans are to use backtrace for gcc)
	- [x] ckg_stack_trace_dump()

### Logger
- [x] ckg_logger.h
	- [x] CKG_LOG_FATAL(msg, ...)
	- [x] CKG_LOG_ERROR(msg, ...)
	- [x] CKG_LOG_WARN(msg, ...)
	- [x] CKG_LOG_DEBUG(msg, ...)
	- [x] CKG_LOG_SUCCESS(msg, ...)
	- [x] CKG_LOG_PRINT(msg, ...)

### String
- [x] ckg_cstring.h
	- [x] ckg_cstr_append(str, str_capacity, to_append)
	- [x] ckg_cstr_append_char(str, str_capacity, char to_append)
	- [x] ckg_cstr_insert(str, str_capacity, to_insert, index)
	- [x] ckg_cstr_insert_char(str, str_capacity, char to_insert, index)
	- [x] ckg_cstr_copy(str, str_capacity, to_copy)
	- [x] ckg_cstr_random(dest, length)
	- [x] ckg_cstr_equal(s1, s2)
	- [x] ckg_cstr_length(c_string)
	- [x] ckg_cstr_clear(str)
	- [x] ckg_substring(str, start_range, end_range)
	- [x] ckg_cstr_contains(str, contains)
	- [x] ckg_cstr_index_of(str, sub_string)
	- [x] ckg_cstr_last_index_of(str, sub_string)
	- [x] ckg_cstr_split(str, delimitor)
	- [x] ckg_cstr_starts_with(str, starts_with)
	- [x] ckg_cstr_ends_with(str, ends_with)
	- [x] ckg_cstr_reverse(str)

### Memory
- [x] ckg_memory.h
    - [x] ckg_bind_alloc_callback(func_allocator)
    - [x] ckg_bind_free_callback(func_allocator)
    - [x] ckg_alloc(allocation_size)
    - [x] ckg_realloc(data, old_allocation_size, new_allocation_size)
    - [x] ckg_free(data)
    - [x] ckg_memory_compare(buffer_one, buffer_two, b1_allocation_size, b2_allocation_size)
    - [x] ckg_memory_copy(source, destination, source_size, destination_capacity)
		- handle overlapping addresses
		- This is done by copying so obviously its bad lmao
    - [x] ckg_memory_zero(data, data_size_in_bytes)
    - [x] ckg_memory_delete_index(data, data_capacity, element_size_in_bytes, index)

- [x] ckg_arena.h (REMOVE This, it should be a ckit thing only)
	- [x] ckg_arena_create(allocation, name, flag)
	- [x] ckg_arena_push(arena, type)	
	- [x] ckg_arena_free(arena)
	- [x] ckg_arena_clear(arena)

### FileIO (REMOVE This, it should be a ckit thing only)
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