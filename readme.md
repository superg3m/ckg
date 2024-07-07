# CKG
The point of the ckit granular (ckg) is building out everything at a granular level  and then using these building block to build a good common use case version. so very few types and allocation is decided by the caller in most cases.

# How to build
1. ./bootstrap.ps1
2. ./build.ps1
2. ./run.ps1

- Collection of tools, data structures, and algorithms that I find useful
- If cl.exe is not defined in your terminal run vars.ps1
- Compile with CUSTOM_PLATFORM_IMPL defined if you want to change how platform specific functions work.


# Goals

## CORE
- [x] ckg_types.c

### Assert
- [x] ckg_assert.c
	- [x] ckg_assert_msg(expression, msg, ...)
	- [x] ckg_assert(expression)

### Logger (Cross-Platform)
- [x] ckg_logger.c
	- [x] CKG_LOG_FATAL(msg, ...)
	- [x] CKG_LOG_ERROR(msg, ...)
	- [x] CKG_LOG_WARN(msg, ...)
	- [x] CKG_LOG_DEBUG(msg, ...)
	- [x] CKG_LOG_SUCCESS(msg, ...)
	- [x] CKG_LOG_PRINT(msg, ...)

### String
- [x] ckg_cstring.c
	- [x] ckg_cstr_alloc(s1);
	- [x] ckg_cstr_append(string_buffer, string_buffer_capacity, to_append);
	- [x] ckg_cstr_append_char(string_buffer, string_buffer_capacity, char to_append);
	- [x] ckg_cstr_insert(string_buffer, string_buffer_capacity, to_insert, index);
	- [x] ckg_cstr_insert_char(string_buffer, string_buffer_capacity, char to_insert, index);
	- [x] ckg_cstr_copy(string_buffer, string_buffer_capacity, to_copy);
	- [x] ckg_cstr_random(dest, length);
	- [x] ckg_cstr_equal(s1, s2);
	- [x] ckg_cstr_length(c_string);
	- [x] ckg_cstr_clear(string_buffer);
	- [x] ckg_substring(string_buffer, start_range, end_range);
	- [x] ckg_cstr_contains(string_buffer, contains);
	- [x] ckg_cstr_index_of(string_buffer, sub_string);
	- [x] ckg_cstr_last_index_of(string_buffer, sub_string);
	- [x] ckg_cstr_split(string_buffer, delimitor);
	- [x] ckg_cstr_starts_with(string_buffer, starts_with);
	- [x] ckg_cstr_ends_with(string_buffer, ends_with);
	- [x] ckg_cstr_reverse(string_buffer);

### Memory
- [x] ckg_memory.c
- [x] ckg_arena.c
### FileIO
- [x] ckg_file_io.c // should revist this though not robust at all