#pragma once

// unify this to be a single file
#if defined(CKG_EXTERN)
    #define CKG_API extern
#else
    #define CKG_API
#endif

#if defined (CKG_INCLUDE_ALL)
    #define CKG_INCLUDE_TYPES
    #define CKG_INCLUDE_LOGGER
    #define CKG_INCLUDE_ASSERT
    #define CKG_INCLUDE_MEMORY
    #define CKG_INCLUDE_ARENA
    #define CKG_INCLUDE_CSTRING
    #define CKG_INCLUDE_CHAR
    #define CKG_INCLUDE_COLLECTIONS
    #define CKG_INCLUDE_PLATFORM
#endif

#if defined (CKG_IMPL_ALL)
    #define CKG_IMPL_TYPES
    #define CKG_IMPL_LOGGER
    #define CKG_IMPL_ASSERT
    #define CKG_IMPL_MEMORY
    #define CKG_IMPL_ARENA
    #define CKG_IMPL_CSTRING
    #define CKG_IMPL_CHAR
    #define CKG_IMPL_COLLECTIONS
    #define CKG_IMPL_PLATFORM
#endif

#if define(CKG_INCLUDE_TYPES)
    #include <stdint.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <stdlib.h>

    typedef int8_t  s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef u8 Boolean;

    #define FALSE 0
    #define TRUE 1
    #define NULLPTR 0
    #define PI 3.14159265359

    #define stringify(entry) #entry
    #define glue(a, b) a##b

    #define KiloBytes(value) ((u64)(value) * 1024L)
    #define MegaBytes(value) ((u64)KiloBytes(value) * 1024L)
    #define GigaBytes(value) ((u64)MegaBytes(value) * 1024L)

    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
    #define MAX(a, b) (((a) > (b)) ? (a) : (b))
    #define CLAMP(value, min_value, max_value) (MIN(MAX(value, min_value), max_value))

    #define local_persist static
    #define internal static

    // Date: July 12, 2024
    // TODO(Jovanni): Test this to make sure its actually works but it makes sense to me
    #define OFFSET_OF(type, member) sizeof((u64)(&(((type*)0)->member)))

    #define FIRST_DIGIT(number) ((int)number % 10);

    CKG_API void U32_EndianSwap(u32* number_to_endian_swap);
    CKG_API void U64_EndianSwap(u64* number_to_endian_swap);
    #define GET_BIT(number, bit_to_check) ((number & (1 << bit_to_check)) >> bit_to_check)
    #define SET_BIT(number, bit_to_set) number |= (1 << bit_to_set);
    #define UNSET_BIT(number, bit_to_unset) number &= (~(1 << bit_to_unset));

    #define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

    #define PLATFORM_MAX_PATH 256

    #if defined(_WIN32)
        #define PLATFORM_WINDOWS
        #define OS_DELIMITER '\\'
        #define CRASH __debugbreak()
    #elif defined(__APPLE__)
        #define PLATFORM_APPLE
        #define OS_DELIMITER '/'
        #define CRASH __builtin_trap()
    #elif defined(__linux__) || defined(__unix__) || defined(__POSIX__)
        #define PLATFORM_LINUX
        #define OS_DELIMITER '/'
        #define CRASH __builtin_trap()
    #else
        #error "Unknown Platform???"
    #endif

    CKG_API void ckg_stack_trace_dump();
#endif

#if define(CKG_INCLUDE_LOGGER)
    //Regular text
    #define CKG_BLACK "\033[0;30m"
    #define CKG_RED "\033[0;31m"
    #define CKG_GREEN "\033[0;32m"
    #define CKG_YELLOW "\033[0;33m"
    #define CKG_BLUE "\033[0;34m"
    #define CKG_PURPLE "\033[0;35m"
    #define CKG_CYAN "\033[0;36m"

    //Regular background
    #define CKG_BLACK_BACKGROUND "\033[40m"
    #define CKG_RED_BACKGROUND "\033[41m"
    #define CKG_GREENN_BACKGROUND "\033[42m"
    #define CKG_YELLOW_BACKGROUND "\033[43m"
    #define CKG_BLUE_BACKGROUND "\033[44m"
    #define CKG_PURPLE_BACKGROUND "\033[45m"
    #define CKG_CYAN_BACKGROUND "\033[46m"
    #define CKG_COLOR_RESET "\033[0m"

    #define CKG_LOG_LEVEL_CHARACTER_LIMIT 15
    #define CKG_PLATFORM_CHARACTER_LIMIT 512

    // Log Levels
    #define LOG_LEVEL_FATAL 0
    #define LOG_LEVEL_ERROR 1
    #define LOG_LEVEL_WARN 2
    #define LOG_LEVEL_DEBUG 3
    #define LOG_LEVEL_SUCCESS 4
    #define LOG_LEVEL_PRINT 5
    #define LOG_LEVEL_COUNT 6
    typedef u8 CKG_LogLevel;

    CKG_API void MACRO_ckg_log_output(CKG_LogLevel log_level, const char* message, ...);
    #define ckg_log_output(log_level, message, ...) MACRO_ckg_log_output(log_level, message, ##__VA_ARGS__)
    #define CKG_LOG_PRINT(message, ...) ckg_log_output(LOG_LEVEL_PRINT, message, ##__VA_ARGS__)
    #define CKG_LOG_SUCCESS(message, ...) ckg_log_output(LOG_LEVEL_SUCCESS, message, ##__VA_ARGS__)
    #define CKG_LOG_DEBUG(message, ...) ckg_log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
    #define CKG_LOG_WARN(message, ...) ckg_log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__)
    #define CKG_LOG_ERROR(message, ...) ckg_log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
    #define CKG_LOG_FATAL(message, ...) ckg_log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
#endif


#if defined(CKG_INCLUDE_ASSERT)
    #define CKG_ASSERT_ENABLED TRUE
    #if CKG_ASSERT_ENABLED == TRUE	   
        #define ckg_assert(expression)                            \
        do {                                                      \
            if (!(expression)) {                                  \
                ckg_stack_trace_dump();                           \
                char msg[] = "Func: %s, File: %s:%d\n";           \
                CKG_LOG_FATAL(msg, __func__, __FILE__, __LINE__); \
                CRASH;                                            \
            }                                                     \
        } while (FALSE)

        #define ckg_assert_msg(expression, message, ...)	\
            do {                                            \
                if (!(expression)) {                        \
                    ckg_stack_trace_dump();                 \
                    CKG_LOG_FATAL(message, ##__VA_ARGS__);  \
                    CRASH;                                  \
                }                                           \
            } while (FALSE)
    #else
            #define ckg_assert(expression)
            #define ckg_assert_msg(expression, message, ...)
    #endif
#endif

#if (CKG_INCLUDE_MEMORY)
    typedef void* (CKG_MemoryAllocator)(size_t);
    typedef void (CKG_MemoryFree)(void*);

    /**
     * @brief Note that the callback provided should zero out the memory allocation.
     * Failing to bind the allocation callback will result in a default allocation callback.
     */
    CKG_API void ckg_bind_alloc_callback(CKG_MemoryAllocator* func_allocator);

    /**
     * @brief Failing to bind the callback will result in a default free callback.
     */
    CKG_API void ckg_bind_free_callback(CKG_MemoryFree* func_allocator);

    CKG_API void* ckg_alloc(size_t allocation_size);
    CKG_API void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size);
    CKG_API void* MACRO_ckg_free(void* data);

    /**
     * @brief Compares the bytes in the two buffers
     * 
     * @param buffer_one 
     * @param buffer_two 
     * @param b1_allocation_size 
     * @param b2_allocation_size 
     * @return Boolean 
     */
    CKG_API Boolean ckg_memory_compare(const void* buffer_one, const void* buffer_two, u32 b1_allocation_size, u32 b2_allocation_size);
    CKG_API void ckg_memory_copy(const void* source, void* destination, size_t source_size_in_bytes, size_t destination_size_in_bytes);
    CKG_API void ckg_memory_zero(void* data, size_t data_size_in_bytes);

    CKG_API void MACRO_ckg_memory_delete_index(void* data, u32 number_of_elements, u32 data_capacity, size_t element_size_in_bytes, u32 index);
    CKG_API void MACRO_ckg_memory_insert_index(void* data, u32 number_of_elements, u32 data_capacity, size_t element_size_in_bytes, u32 index);

    #define ckg_memory_fill(buffer, buffer_count, fill_element) \
    {														\
        for (u32 i = 0; i < buffer_count; i++) { 			\
            buffer[i] = fill_element;                       \
        }                                                  	\
    }

    #define ckg_free(data) data = MACRO_ckg_free(data)
    #define ckg_memory_delete_index(data, number_of_elements, data_capacity, index) MACRO_ckg_memory_delete_index(data, number_of_elements, data_capacity, sizeof(data[0]), index)
    #define ckg_memory_insert_index(data, number_of_elements, data_capacity, element, index) MACRO_ckg_memory_insert_index(data, number_of_elements, data_capacity, sizeof(data[0]), index); data[index] = element;
#endif


#if defined(CKG_INCLUDE_ARENA)
    #define CKG_ARENA_FLAG_FIXED 0
    #define CKG_ARENA_FLAG_CIRCULAR 1
    #define CKG_ARENA_FLAG_EXTENDABLE_PAGES 2
    #define CKG_ARENA_FLAG_COUNT 3
    typedef u8 CKG_ArenaFlag;
    typedef struct CKG_Arena CKG_Arena;


    CKG_API CKG_Arena* MACRO_ckg_arena_create(size_t allocation_size, const char* name, CKG_ArenaFlag flag, u8 alignment);
    CKG_API void* MACRO_ckg_arena_push(CKG_Arena* arena, size_t element_size);	
    CKG_API CKG_Arena* MACRO_ckg_arena_free(CKG_Arena* arena);
    CKG_API void ckg_arena_clear(CKG_Arena* arena);

    #define ckg_arena_create(allocation_size, name) MACRO_ckg_arena_create(allocation_size, name, CKG_ARENA_FLAG_EXTENDABLE_PAGES, 0)
    #define ckg_arena_create_custom(allocation_size, name, flags, alignment) MACRO_ckg_arena_create(allocation_size, name, flags, alignment)
    #define ckg_arena_free(arena) arena = MACRO_ckg_arena_free(arena)
    #define ckg_arena_push(arena, type) ((type*)MACRO_ckg_arena_push(arena, sizeof(type)))
    #define ckg_arena_push_array(arena, type, element_count) ((type*)MACRO_ckg_arena_push(arena, sizeof(type) * element_count))
#endif

#if defined(CKG_INCLUDE_CSTRING)
	/**
	 * @brief returns a string buffer with nullterm
	 * must free with ckg_free()
	 * @param s1 
	 * @return char* 
	 */
	CKG_API char* ckg_cstr_alloc(const char* s1);

	/**
	 * @brief Requires the string buffer to be cleared to zero terminated
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 * @param source 
	 */
	CKG_API void ckg_cstr_append(char* string_buffer, size_t string_buffer_capacity, const char* to_append);
	CKG_API void ckg_cstr_append_char(char* string_buffer, size_t string_buffer_capacity, const char to_append);

	/**
	 * @brief Requires the string buffer to be cleared to zero terminated
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 * @param index 
	 */
	CKG_API void ckg_cstr_insert(char* string_buffer, size_t string_buffer_capacity, const char* to_insert, const u32 index);
	CKG_API void ckg_cstr_insert_char(char* string_buffer, size_t string_buffer_capacity, const char to_insert, const u32 index);
	
	/**
	 * @brief Requires the string buffer to be cleared to zero, modifies string_buffer
	 * 
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 */
	CKG_API void ckg_cstr_copy(char* string_buffer, size_t string_buffer_capacity, const char* to_copy);

	/**
	 * @brief generate a random string and copy it to the dest pointer
	 * 
	 * @param dest 
	 * @param length 
	 */
	CKG_API void ckg_cstr_random(char* dest, size_t length);
	
	/**
	 * @brief Tests each charater in the string for equaility
	 * returns TRUE(1) if equal and FALSE(0) if not equal
	 * => if (ckg_cstr_equal("hi", "hi"))
	 * 
	 * 
	 * @param s1 
	 * @param s2 
	 * @return Boolean 
	 */
	CKG_API Boolean ckg_cstr_equal(const char* s1, const char* s2);
	CKG_API u32 ckg_cstr_length(const char* c_string);
	CKG_API void ckg_cstr_clear(char* string_buffer);
	// Inclusive start and end STR: SHOW | 0, 0 is: S | 0, 1 is: SH
	CKG_API void ckg_substring(const char* string_buffer, char* returned_buffer, u32 start_range, u32 end_range);
	CKG_API Boolean ckg_cstr_contains(const char* string_buffer, const char* contains);
	CKG_API s32 ckg_cstr_index_of(const char* string_buffer, const char* sub_string);
	CKG_API s32 ckg_cstr_last_index_of(const char* string_buffer, const char* sub_string);
	CKG_API Boolean ckg_cstr_starts_with(const char* string_buffer, const char* starts_with);
	CKG_API Boolean ckg_cstr_ends_with(const char* string_buffer, const char* ends_with);
	CKG_API void ckg_cstr_reverse(const char* str, char* returned_reversed_string_buffer, size_t reversed_buffer_capacity);
	CKG_API void ckg_cstr_int_to_cstr(char* string_buffer, size_t string_buffer_capacity, int number);
#endif

#if defined(CKG_INCLUDE_CHAR)
    CKG_API Boolean ckg_char_is_digit(char c);
    CKG_API Boolean ckg_char_is_alpha(char c);
    CKG_API Boolean ckg_char_is_alpha_numeric(char c);
    CKG_API Boolean ckg_char_is_upper(char c);
    CKG_API Boolean ckg_char_is_lower(char c);
#endif

#if defined(CKG_INCLUDE_MATH)
    #include <math.h>
    // more here later
    // round intrinsic
    // trig fucntion intrinsics or approximations with taylor series
#endif

#if defined (CKG_INCLUDE_COLLECTIONS)
    //
    // ========== START CKG_VECTOR ==========
    //
    typedef struct CKG_VectorHeader {
        u32 count;
        u32 capacity;
    } CKG_VectorHeader;

    CKG_API void* ckg_vector_grow(void* vector, size_t element_size);


    #define VECTOR_DEFAULT_CAPACITY 1
    #define ckg_vector_header_base(vector) ((CKG_VectorHeader*)(((u8*)vector) - sizeof(CKG_VectorHeader)))
    #define ckg_vector_count(vector) (*ckg_vector_header_base(vector)).count
    #define ckg_vector_capacity(vector) (*ckg_vector_header_base(vector)).capacity
    #define ckg_vector_push(vector, element) vector = ckg_vector_grow(vector, sizeof(element)); vector[ckg_vector_header_base(vector)->count++] = element
    #define ckg_vector_free(vector) ckg_free(ckg_vector_header_base(vector))
    //
    // ========== END CKG_VECTOR ==========
    //


    //
    // ========== START CKG_LinkedList ==========
    //
    typedef struct CKG_Node {
        struct CKG_Node* next;
        struct CKG_Node* prev;
        size_t element_size_in_bytes;
        void* data;
    } CKG_Node;

    typedef struct CKG_LinkedList {
        CKG_Node* head;
        CKG_Node* tail;
        size_t element_size_in_bytes;
        u32 count;
        Boolean is_pointer_type;
    } CKG_LinkedList;

    CKG_API CKG_LinkedList* MACRO_ckg_linked_list_create(size_t element_size_in_bytes, Boolean is_pointer_type);
    CKG_API CKG_Node* ckg_linked_list_insert(CKG_LinkedList* linked_list, u32 index, void* data);
    CKG_API CKG_Node* ckg_linked_list_get_node(CKG_LinkedList* linked_list, u32 index);
    CKG_API void* ckg_linked_list_get(CKG_LinkedList* linked_list, u32 index);
    CKG_API void* ckg_linked_list_peek_head(CKG_LinkedList* linked_list);
    CKG_API void* ckg_linked_list_peek_tail(CKG_LinkedList* linked_list);
    CKG_API CKG_Node* ckg_linked_list_push(CKG_LinkedList* linked_list, void* data);
    CKG_API CKG_Node ckg_linked_list_pop(CKG_LinkedList* linked_list);
    CKG_API CKG_Node ckg_linked_list_remove(CKG_LinkedList* linked_list, u32 index);
    CKG_API void* MACRO_ckg_linked_list_free(CKG_LinkedList* linked_list);
    CKG_API u32 ckg_linked_list_node_to_index(CKG_LinkedList* linked_list, CKG_Node* address);

    #define ckg_linked_list_create(type, is_pointer_type) MACRO_ckg_linked_list_create(sizeof(type), is_pointer_type)
    #define ckg_linked_list_free(linked_list) linked_list = MACRO_ckg_linked_list_free(linked_list)
    //
    // ========== END CKG_VECTOR ==========
    //
#endif 

// Date: September 22, 2024
// TODO(Jovanni): Make this good I hate the file system idea here!
#if defined(CKG_INCLUDE_PLATFORM)
    typedef struct CKG_FileSystem {
        char* file_name;
        FILE* handle;
        u8* data;
        size_t file_size;
        Boolean reachedEOF;
    } CKG_FileSystem;

    CKG_API CKG_FileSystem ckg_file_system_create(char* file_name);
    CKG_API void ckg_file_open(CKG_FileSystem* file_system);
    CKG_API void ckg_file_close(CKG_FileSystem* file_system);
    CKG_API size_t ckg_file_size(CKG_FileSystem* file_system);
    CKG_API char* ckg_file_get_next_line(CKG_FileSystem* file_system);
    CKG_API char ckg_file_get_next_char(CKG_FileSystem* file_system);
#endif

//
// ===================================================== CKG_IMPL =====================================================
//

// types
// logger
// assert
// mmemory
// arena
// cstring
// char
// collections
// math
// platforms