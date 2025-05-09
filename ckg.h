#pragma once

#ifdef __cplusplus
    #define CKG_API extern "C"
#else 
    #define CKG_API
#endif 

#if defined(CKG_IMPL)
    #define CKG_IMPL_TYPES
    #define CKG_IMPL_LOGGER
    #define CKG_IMPL_ASSERT
    #define CKG_IMPL_ERRORS
    #define CKG_IMPL_MEMORY
    #define CKG_IMPL_ARENA
    #define CKG_IMPL_STRING
    #define CKG_IMPL_CHAR
    #define CKG_IMPL_COLLECTIONS
    #define CKG_IMPL_SERIALIZATION
    #define CKG_IMPL_IO
    #define CKG_IMPL_OS
#endif

#define CKG_INCLUDE_TYPES
#define CKG_INCLUDE_LOGGER
#define CKG_INCLUDE_ASSERT
#define CKG_INCLUDE_ERRORS
#define CKG_INCLUDE_MEMORY
#define CKG_INCLUDE_ARENA
#define CKG_INCLUDE_STRING
#define CKG_INCLUDE_CHAR
#define CKG_INCLUDE_COLLECTIONS
#define CKG_INCLUDE_SERIALIZATION
#define CKG_INCLUDE_IO
#define CKG_INCLUDE_OS

// KEY NOTES:
// - Whenever you see [OPTIONAL] that means you can use NULLPTR for that param

#define CKG_INCLUDE_TYPES
#if defined(CKG_INCLUDE_TYPES)
    #include <stdint.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef int8_t  s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    #define NULLPTR 0
    #define PI 3.14159265359

    #define stringify(entry) #entry
    #define glue(a, b) a##b

    #define KiloBytes(value) ((size_t)(value) * 1024L)
    #define MegaBytes(value) ((size_t)KiloBytes(value) * 1024L)
    #define GigaBytes(value) ((size_t)MegaBytes(value) * 1024L)

    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
    #define MAX(a, b) (((a) > (b)) ? (a) : (b))
    #define CLAMP(value, min_value, max_value) (MIN(MAX(value, min_value), max_value))

    #define local_persist static
    #define internal static


    CKG_API void U32_EndianSwap(u32* number_to_endian_swap);
    CKG_API void U64_EndianSwap(u64* number_to_endian_swap);

    // Date: July 12, 2024
    // TODO(Jovanni): Test this to make sure its actually works but it makes sense to me
    #define OFFSET_OF(type, member) sizeof((size_t)(&(((type*)0)->member)))
    #define FIRST_DIGIT(number) ((int)number % 10);
    #define GET_BIT(number, bit_to_check) ((number & (1 << bit_to_check)) >> bit_to_check)
    #define SET_BIT(number, bit_to_set) number |= (1 << bit_to_set);
    #define UNSET_BIT(number, bit_to_unset) number &= (~(1 << bit_to_unset));

    #define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

    #define PLATFORM_MAX_PATH 256

    #if defined(_WIN32)
        #define NOMINMAX
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
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

    #if defined(__clang__)
        #define UNUSED_FUNCTION __attribute__((used))
        #define WRITE_FENCE() __asm__ volatile("" ::: "memory"); __asm__ volatile("sfence" ::: "memory")
        #define READ_FENCE() __asm__ volatile("" ::: "memory");
    #elif defined(__GNUC__) || defined(__GNUG__)
        #define UNUSED_FUNCTION __attribute__((used))
        #define WRITE_FENCE() __asm__ volatile("" ::: "memory"); __asm__ volatile("sfence" ::: "memory")
        #define READ_FENCE() __asm__ volatile("" ::: "memory");
    #elif defined(_MSC_VER)
        #define UNUSED_FUNCTION
        #define WRITE_FENCE() _WriteBarrier(); _mm_sfence()
        #define READ_FENCE() _ReadBarrier()
    #endif

    CKG_API void ckg_stack_trace_dump();
#endif

#if defined(CKG_INCLUDE_LOGGER)
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

    #define CKG_LOG_LEVEL_CHARACTER_LIMIT 12
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

    CKG_API void MACRO_ckg_log_output(CKG_LogLevel log_level, char* message, ...);
    #define ckg_log_output(log_level, message, ...) MACRO_ckg_log_output(log_level, message, ##__VA_ARGS__)
    #define CKG_LOG_PRINT(message, ...) ckg_log_output(LOG_LEVEL_PRINT, message, ##__VA_ARGS__)
    #define CKG_LOG_SUCCESS(message, ...) ckg_log_output(LOG_LEVEL_SUCCESS, message, ##__VA_ARGS__)
    #define CKG_LOG_DEBUG(message, ...) ckg_log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
    #define CKG_LOG_WARN(message, ...) ckg_log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__)
    #define CKG_LOG_ERROR(message, ...) ckg_log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
    #define CKG_LOG_FATAL(message, ...) ckg_log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
#endif

#if defined(CKG_INCLUDE_ASSERT)
    #define CKG_ASSERT_ENABLED true
    #if CKG_ASSERT_ENABLED == true 
        #define ckg_assert(expression)                                    \
            do {                                                          \
                if (!(expression)) {                                      \
                    ckg_stack_trace_dump();                               \
                    char msg[] = "Func: %s, File: %s:%d\n";               \
                    CKG_LOG_FATAL(msg, __func__, __FILE__, __LINE__);     \
                    CRASH;                                                \
                }                                                         \
            } while (false)                                               \

        #define ckg_assert_msg(expression, message, ...)	              \
            do {                                                          \
                if (!(expression)) {                                      \
                    ckg_stack_trace_dump();                               \
                    char msg[] = "Func: %s, File: %s:%d\n";               \
                    CKG_LOG_FATAL(msg, __func__, __FILE__, __LINE__);     \
                    CKG_LOG_FATAL(message, ##__VA_ARGS__);                \
                    CRASH;                                                \
                }                                                         \
            } while (false)                                               \

    #else
            #define ckg_assert(expression)
            #define ckg_assert_msg(expression, message, ...)
    #endif
#endif

#if defined(CKG_INCLUDE_ERRORS)
    /*
    +------------+----------------------------+
    | Error Type |        Error Code          |
    | (4bits)    |         (28bits)           |
    +------------+----------------------------+
    */

    #define CKG_ERROR_SUCCESS 0
    #define CKG_ERROR_TYPE_COUNT 2
    #define CKG_ERROR_TYPE_MASK (0b1111 << 28)

    #define CKG_ERROR_IO_MASK (0 << 28)
    #define CKG_ERROR_ARGS_MASK (1 << 28)
    typedef enum CKG_Error {
        CKG_ERROR_IO_RESOURCE_NOT_FOUND = (CKG_ERROR_IO_MASK | 0),
        CKG_ERROR_IO_RESOURCE_TOO_BIG,
        CKG_ERROR_IO_COUNT = 2,

        CKG_ERROR_ARG_ONE_INVALID = (CKG_ERROR_ARGS_MASK | 0),
        CKG_ERROR_ARG_ONE_NULLPTR,
        CKG_ERROR_ARG_ONE_ZERO,
        CKG_ERROR_ARG_TWO_INVALID,
        CKG_ERROR_ARG_TWO_NULLPTR,
        CKG_ERROR_ARG_TWO_ZERO,
        CKG_ERROR_ARG_THREE_INVALID,
        CKG_ERROR_ARG_THREE_NULLPTR,
        CKG_ERROR_ARG_THREE_ZERO,
        CKG_ERROR_ARG_FOUR_INVALID,
        CKG_ERROR_ARG_FOUR_NULLPTR,
        CKG_ERROR_ARG_FOUR_ZERO,
        CKG_ERROR_ARGS_COUNT = 12
    } CKG_Error;

    CKG_API char* ckg_error_str(CKG_Error error_code);
#endif

#if defined(CKG_INCLUDE_MEMORY)
    typedef struct CKG_Allocator CKG_Allocator;
    typedef void*(CKG_Alloc_T)(CKG_Allocator* allocator, size_t allocation_size);
    typedef void(CKG_Free_T)(CKG_Allocator* allocator, void* data);

    typedef struct CKG_Allocator {
        CKG_Alloc_T* allocate;
        CKG_Free_T* free;
        void* ctx;
    } CKG_Allocator;

    CKG_API void ckg_bind_custom_allocator(CKG_Alloc_T* a, CKG_Free_T* f, void* ctx);

    CKG_API void* ckg_alloc(size_t allocation_size);
    CKG_API void* MACRO_ckg_free(void* data);
    CKG_API void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size);

    /**
     * @brief Compares the bytes in the two buffers returns true if equal
     * 
     * @param buffer_one 
     * @param buffer_two 
     * @param b1_allocation_size 
     * @param b2_allocation_size 
     * @return bool 
     */
    CKG_API bool ckg_memory_compare(void* buffer_one, void* buffer_two, size_t b1_allocation_size, size_t b2_allocation_size);
    CKG_API void ckg_memory_copy(void* source, void* destination, size_t source_size_in_bytes, size_t destination_size_in_bytes);
    CKG_API void ckg_memory_zero(void* data, size_t data_size_in_bytes);

    CKG_API void MACRO_ckg_memory_delete_index(void* data, size_t number_of_elements, size_t data_capacity, size_t element_size_in_bytes, size_t index);
    CKG_API void MACRO_ckg_memory_insert_index(void* data, size_t number_of_elements, size_t data_capacity, size_t element_size_in_bytes, size_t index);

    #define ckg_memory_fill(_buffer, _buffer_count, _fill_element) \
    {														       \
        for (int i = 0; i < (int)_buffer_count; i++) { 			   \
            _buffer[i] = _fill_element;                            \
        }                                                  	       \
    }                
    
    #ifdef __cplusplus
        #define ckg_free(data) data = (decltype(data))MACRO_ckg_free(data)
    #else 
        #define ckg_free(data) data = MACRO_ckg_free(data)
    #endif
    
    #define ckg_memory_delete_index(data, number_of_elements, data_capacity, index) MACRO_ckg_memory_delete_index(data, number_of_elements, data_capacity, sizeof(data[0]), index)
    #define ckg_memory_insert_index(data, number_of_elements, data_capacity, element, index) MACRO_ckg_memory_insert_index(data, number_of_elements, data_capacity, sizeof(data[0]), index); data[index] = element;
#endif

#if defined(CKG_INCLUDE_ARENA)
    #define ARENA_DEFAULT_ALLOCATION_SIZE MegaBytes(1)

    typedef enum CKG_ArenaFlag {
        CKG_ARENA_FLAG_INVALID = -1,
        CKG_ARENA_FLAG_FIXED = 0x1,
        CKG_ARENA_FLAG_CIRCULAR = 0x2,
        CKG_ARENA_FLAG_STACK_MEMORY = 0x4,
        CKG_ARENA_FLAG_COUNT = 4,
    } CKG_ArenaFlag;

    typedef struct CKG_Arena {
        u8* base_address;
        size_t capacity;
        size_t used_save_point;
        size_t used;
        u8 alignment;
        u32 flags;
    } CKG_Arena;
    
    /**
     * @brief 
     * 
     * @param memory 
     * @param allocation_size 
     * @param flag 
     * @param alignment
     * @return CKG_API* 
     */
    CKG_API CKG_Arena ckg_arena_create_custom(void* memory, size_t allocation_size, u32 flags, u8 alignment);
    CKG_API void ckg_arena_free(CKG_Arena* arena);
    CKG_API void* ckg_arena_push_custom(CKG_Arena* arena, size_t element_size);	
    CKG_API void ckg_arena_begin_temp(CKG_Arena* arena);
    CKG_API void ckg_arena_end_temp(CKG_Arena* arena);
    CKG_API void ckg_arena_zero(CKG_Arena* arena);
    CKG_API void ckg_arena_reset(CKG_Arena* arena);
    CKG_API void MACRO_ckg_arena_pop(CKG_Arena* arena, size_t bytes_to_pop);
    
    #define ckg_arena_create_fixed(memory, allocation_size, is_stack_memory) ckg_arena_create_custom(memory, allocation_size, CKG_ARENA_FLAG_FIXED|(is_stack_memory ? CKG_ARENA_FLAG_STACK_MEMORY : 0), 0)
    #define ckg_arena_create_circular(memory, allocation_size, is_stack_memory) ckg_arena_create_custom(memory, allocation_size, CKG_ARENA_FLAG_CIRCULAR|(is_stack_memory ? CKG_ARENA_FLAG_STACK_MEMORY : 0), 0)
    #define ckg_arena_push(arena, type) ((type*)ckg_arena_push_custom(arena, sizeof(type)))
    #define ckg_arena_push_array(arena, type, element_count) ((type*)ckg_arena_push_custom(arena, sizeof(type) * element_count))
    #define ckg_arena_pop(arena, type) MACRO_ckg_arena_pop(arena, sizeof(type))
    #define ckg_arena_pop_array(arena, type) MACRO_ckg_arena_pop(arena, sizeof(type) * element_count)
    #define ckg_arena_temp(arena, code_block) ckg_arena_begin_temp(arena); code_block; ckg_arena_end_temp(arena);
#endif

#if defined(CKG_INCLUDE_STRING)
    /**
	 * @brief returns a string buffer with nullterm
	 * in most cases free with ckg_free()
	 * @param s1 
	 * @return char* 
	 */
	CKG_API char*  ckg_str_alloc(char* s1, size_t length);
    CKG_API size_t ckg_cstr_length(char* c_string);
    CKG_API void   ckg_str_clear(char* s1, size_t length);
    CKG_API void   ckg_str_copy(char* dest, size_t dest_capacity, char* source, size_t source_length);
	CKG_API void   ckg_str_append(char* str, size_t str_length, size_t str_capacity, char* to_append, size_t to_append_length);
	CKG_API void   ckg_str_append_char(char* str, size_t str_length, size_t str_capacity, char to_append);
	CKG_API void   ckg_str_insert(char* str, size_t str_length, size_t str_capacity, char* to_insert, size_t to_insert_length, size_t index);
	CKG_API void   ckg_str_insert_char(char* str, size_t str_length, size_t str_capacity, char to_insert, size_t index);
    CKG_API void   ckg_str_reverse(char* str, size_t str_length, char* returned_reversed_string_buffer, size_t reversed_buffer_capacity);
    CKG_API char*  ckg_str_va_sprint(size_t* allocation_size_ptr, char* fmt, va_list args);
    CKG_API char*  MACRO_ckg_cstr_sprint(size_t* allocation_size_ptr, char* fmt, ...);
    #define ckg_cstr_sprint(allocation_size_ptr, fmt, ...) MACRO_ckg_cstr_sprint(allocation_size_ptr, fmt, ##__VA_ARGS__)

    CKG_API bool ckg_str_equal(char* s1, size_t s1_length, char* s2, size_t s2_length);
    CKG_API bool ckg_str_contains(char* s1, size_t s1_length, char* contains, size_t contains_length);
	CKG_API s64  ckg_str_index_of(char* str, size_t str_length, char* substring, size_t substring_length);
	CKG_API s64  ckg_str_last_index_of(char* str, size_t str_length, char* substring, size_t substring_length);
	CKG_API bool ckg_str_starts_with(char* str, size_t str_length, char* starts_with, size_t starts_with_length);
	CKG_API bool ckg_str_ends_with(char* str, size_t str_length, char* ends_with, size_t ends_with_length);


    typedef struct CKG_StringView {
        char* data;
        size_t length;
    } CKG_StringView;
    
    CKG_StringView  ckg_sv_create(char* data, size_t length);
    CKG_StringView  ckg_sv_between_delimiters(char* str, u64 str_length, char* start_delimitor, u64 start_delimitor_length, char* end_delimitor, u64 end_delimitor_length);
    CKG_StringView* ckg_sv_split(char* data, size_t length, char* delimitor, size_t delimitor_length);
    
    #define CKG_SV_LIT(literal) (CKG_StringView){literal, sizeof(literal) - 1}
    #define CKG_SV_EMPTY() (CKG_StringView){"", 0}
    #define CKG_LIT_ARG(literal) literal, sizeof(literal) - 1

    #define ckg_sv_equal(sv1, sv2) ckg_str_equal(sv1.data, sv1.length, sv2.data, sv2.length)
    #define ckg_sv_contains(sv1, sv2) ckg_str_contains(sv1.data, sv1.length, sv2.data, sv2.length)
	#define ckg_sv_index_of(sv1, sv2) ckg_str_index_of(sv1.data, sv1.length, sv2.data, sv2.length)
	#define ckg_sv_last_index_of(sv1, sv2) ckg_str_last_index_of(sv1.data, sv1.length, sv2.data, sv2.length)
	#define ckg_sv_starts_with(sv1, sv2) ckg_str_starts_with(sv1.data, sv1.length, sv2.data, sv2.length)
	#define ckg_sv_ends_with(sv1, sv2) ckg_str_ends_with(sv1.data, sv1.length, sv2.data, sv2.length)
#endif

#if defined(CKG_INCLUDE_CHAR)
    #define ckg_char_is_digit(c) (c >= '0' && c <= '9')
    #define ckg_char_is_upper(c) (c >= 'A' && c <= 'Z')
    #define ckg_char_is_lower(c) (c >= 'a' && c <= 'z')

    CKG_API bool ckg_char_is_alpha(char c);
    CKG_API bool ckg_char_is_alpha_numeric(char c);
#endif

#if defined(CKG_INCLUDE_COLLECTIONS)
    //
    // ========== START CKG_VECTOR ==========
    //
    typedef struct CKG_VectorHeader {
        size_t count;
        size_t capacity;
        size_t element_size;
    } CKG_VectorHeader;

    CKG_API void* ckg_vector_grow(void* vector, size_t element_size, size_t capacity);
    CKG_API void* MACRO_ckg_vector_free(void* vector);

    #define VECTOR_DEFAULT_CAPACITY 1
    #define ckg_vector_header_base(vector) ((CKG_VectorHeader*)(((u8*)vector) - sizeof(CKG_VectorHeader)))
    #define ckg_vector_count(vector) (*ckg_vector_header_base(vector)).count
    #define ckg_vector_capacity(vector) (*ckg_vector_header_base(vector)).capacity

    #define ckg_stack_count(stack) (*ckg_vector_header_base(stack)).count

    #ifdef __cplusplus
        #define ckg_vector_push(vector, element) vector = (decltype(vector))ckg_vector_grow(vector, sizeof(vector[0]), 0); vector[ckg_vector_header_base(vector)->count++] = element
        #define ckg_stack_push(stack, element) stack = (decltype(stack))ckg_vector_grow(stack, sizeof(stack[0]), 0); stack[ckg_vector_header_base(stack)->count++] = element
    #else
        #define ckg_vector_push(vector, element) vector = ckg_vector_grow(vector, sizeof(vector[0]), 0); vector[ckg_vector_header_base(vector)->count++] = element
        #define ckg_stack_push(stack, element) stack = ckg_vector_grow(stack, sizeof(stack[0]), 0); stack[ckg_vector_header_base(stack)->count++] = element
    #endif
    
    #define ckg_vector_free(vector) vector = MACRO_ckg_vector_free(vector)
    #define ckg_stack_free(stack) stack = MACRO_ckg_vector_free(stack)
    #define ckg_stack_pop(stack) stack[--ckg_vector_header_base(stack)->count]
    #define ckg_stack_peek(stack) stack[ckg_stack_count(stack) - 1]
    #define ckg_stack_empty(stack) (ckg_stack_count(stack) == 0)
    //
    // ========== END CKG_VECTOR ==========
    //


    //
    // ========== START CKG_CircularBuffer ==========
    //
    typedef struct CKG_RingBufferHeader {
        int read;
        int write;
        int count;
        int capacity;
        size_t element_size;
    } CKG_RingBufferHeader;
    
    void* ckg_ring_buffer_create(size_t element_size, int capacity);
    void* MACRO_ckg_ring_buffer_free(void* buffer);
    #define ckg_ring_buffer_free(buffer) buffer = MACRO_ckg_ring_buffer_free(buffer)
    #define ckg_ring_buffer_header_base(buffer) ((CKG_RingBufferHeader*)(((char*)buffer) - sizeof(CKG_RingBufferHeader)))
    #define ckg_ring_buffer_read(buffer) (*ckg_ring_buffer_header_base(buffer)).read
    #define ckg_ring_buffer_write(buffer) (*ckg_ring_buffer_header_base(buffer)).write
    #define ckg_ring_buffer_count(buffer) (*ckg_ring_buffer_header_base(buffer)).count
    #define ckg_ring_buffer_capacity(buffer) (*ckg_ring_buffer_header_base(buffer)).capacity

    #define ckg_ring_buffer_full(buffer) (ckg_ring_buffer_count(buffer) == ckg_ring_buffer_capacity(buffer))
    #define ckg_ring_buffer_empty(buffer) (ckg_ring_buffer_count(buffer) == 0)
    #define ckg_ring_buffer_enqueue(buffer, element) ckg_assert_msg(!ckg_ring_buffer_full(buffer), "Ring buffer is full!\n"); buffer[ckg_ring_buffer_write(buffer)] = element; ckg_ring_buffer_header_base(buffer)->count++; ckg_ring_buffer_header_base(buffer)->write = (ckg_ring_buffer_write(buffer) + 1) % ckg_ring_buffer_capacity(buffer);
    #define ckg_ring_buffer_dequeue(buffer) buffer[ckg_ring_buffer_read(buffer)]; --ckg_ring_buffer_header_base(buffer)->count; ckg_ring_buffer_header_base(buffer)->read = (ckg_ring_buffer_read(buffer) + 1) % ckg_ring_buffer_capacity(buffer); ckg_assert_msg(ckg_ring_buffer_count(buffer) > -1, "Ring buffer is empty!\n");    
    //
    // ========== END CKG_CircularBuffer ==========
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
        size_t count;
        bool is_pointer_type;
    } CKG_LinkedList;

    CKG_API CKG_LinkedList* MACRO_ckg_linked_list_create(size_t element_size_in_bytes, bool is_pointer_type);
    CKG_API CKG_Node* ckg_linked_list_insert(CKG_LinkedList* linked_list, size_t index, void* data);
    CKG_API CKG_Node* ckg_linked_list_get_node(CKG_LinkedList* linked_list, size_t index);
    CKG_API void* ckg_linked_list_get(CKG_LinkedList* linked_list, size_t index);
    CKG_API void* ckg_linked_list_peek_head(CKG_LinkedList* linked_list);
    CKG_API void* ckg_linked_list_peek_tail(CKG_LinkedList* linked_list);
    CKG_API CKG_Node* ckg_linked_list_push(CKG_LinkedList* linked_list, void* data);
    CKG_API CKG_Node ckg_linked_list_pop(CKG_LinkedList* linked_list);
    CKG_API CKG_Node ckg_linked_list_remove(CKG_LinkedList* linked_list, size_t index);
    CKG_API void* MACRO_ckg_linked_list_free(CKG_LinkedList* linked_list);
    CKG_API size_t ckg_linked_list_node_to_index(CKG_LinkedList* linked_list, CKG_Node* address);

    #define ckg_linked_list_create(type, is_pointer_type) MACRO_ckg_linked_list_create(sizeof(type), is_pointer_type)

    #ifdef __cplusplus
        #define ckg_linked_list_free(linked_list) linked_list = (decltype(linked_list))MACRO_ckg_linked_list_free(linked_list)
    #else 
        #define ckg_linked_list_free(linked_list) linked_list = MACRO_ckg_linked_list_free(linked_list)
    #endif
    //
    // ========== END CKG_LinkedList ==========
    //
#endif 

#if defined(CKG_INCLUDE_SERIALIZATION)
    typedef enum CKG_CollectionType {
        CKG_COLLECTION_VECTOR,
        CKG_COLLECTION_STACK,
        CKG_COLLECTION_RING_BUFFER,
        CKG_COLLECTION_LINKED_LIST
    } CKG_CollectionType;

    typedef enum CKG_DataType {
        CKG_DATA_TYPE_CSTRING,
        CKG_DATA_TYPE_STRING_VIEW,
        CKG_DATA_TYPE_BITS
    } CKG_DataType;

    CKG_API void  ckg_serialize_collection(void* collection, FILE* file_handle, CKG_CollectionType collection_type, CKG_DataType data_type);
    
    /**
     * @brief 
     * REMARKS:  -----------------------------------------------------------------------------------------------------------------------
     *  CKG_StringView - If you deserialize using CKG_DATA_TYPE_STRING_VIEW the ascii data is allocated inside .data of the stringview
     *  for (int i = 0; i < ckg_vector_count(sv_vector); i++) {
     *      CKG_StringView sv = sv_vector[i]
     *      ckg_free(sv.data);
     *  }
     * 
     *  CString - If you deserialize using CKG_DATA_TYPE_CSTRING the ascii data is allocated
     *  for (int i = 0; i < ckg_vector_count(str_vector); i++) {
     *      char* str = str_vector[i]
     *      ckg_free(str);
     *  }
     * 
     * @param file_handle 
     * @param collection_type 
     * @param data_type 
     * @return CKG_API* 
     */
    CKG_API void* ckg_deserialize_collection(FILE* file_handle, CKG_CollectionType collection_type, CKG_DataType data_type);
#endif

#if defined(CKG_INCLUDE_IO)
    bool ckg_io_path_exists(char* path);
    /**
     * @brief returns null terminated file data 
     * 
     * @param file_name 
     * @param file_name_length
     * @param file_size [OPTIONAL]
     * @param err [OPTIONAL]
     * @return u8* 
     */
    CKG_API u8* ckg_io_read_entire_file(char* file_name, size_t* returned_file_size, CKG_Error* err);
#endif

#if defined(CKG_INCLUDE_OS)
    typedef void* CKG_DLL;

    // Date: May 05, 2025
    // TODO(Jovanni): ACTUALLY TEST THIS BECUASE NOT SURE IF VOID* will work with HMOUDLE

    /**
     * @brief
     * 
     * @param dll_name 
     * @param err [OPTIONAL]
     * @return CKG_DLL* 
     */
    CKG_API CKG_DLL ckg_io_load_dll(char* dll_name, CKG_Error* err);

    /**
     * @brief 
     * 
     * @param dll 
     * @param proc_name 
     * @param err [OPTIONAL]
     * @return void* 
     */
    CKG_API void* ckg_os_get_proc_address(CKG_DLL dll, char* proc_name, CKG_Error* err);

    /**
     * @brief 
     * 
     * @param dll 
     * @return CKG_DLL* 
     */
    CKG_API CKG_DLL MACRO_ckg_os_free_dll(CKG_DLL dll);

    #define ckg_os_free_dll(dll) dll = MACRO_ckg_os_free_dll(dll)
#endif

//
// ===================================================== CKG_IMPL =====================================================
//

#if defined(CKG_IMPL_TYPES)
    void U32_EndianSwap(u32* number_to_endian_swap) {
        u32 temp = *number_to_endian_swap;
        
        u32 b0 = (temp >> 0) & 0xFF;
        u32 b1 = (temp >> 8) & 0xFF;
        u32 b2 = (temp >> 16) & 0xFF;
        u32 b3 = (temp >> 24) & 0xFF;

        *number_to_endian_swap = (b0 << 24)|(b1 << 16)|(b2 << 8)|(b3 << 0);
    } 

    void U64_EndianSwap(u64* number_to_endian_swap) {
        u64 temp = *number_to_endian_swap;
        
        u64 b0 = (temp >> 0) & 0xFF;
        u64 b1 = (temp >> 8) & 0xFF;
        u64 b2 = (temp >> 16) & 0xFF;
        u64 b3 = (temp >> 24) & 0xFF;
        u64 b4 = (temp >> 32) & 0xFF;
        u64 b5 = (temp >> 40) & 0xFF;
        u64 b6 = (temp >> 48) & 0xFF;
        u64 b7 = (temp >> 56) & 0xFF;

        *number_to_endian_swap = (b0 << 56)|(b1 << 48)|(b2 << 40)|(b3 << 32)|(b4 << 24)|(b5 << 16)|(b6 << 8)|(b7 << 0);
    }

    #if defined(_MSC_VER )
        #include <DbgHelp.h>
        #pragma comment(lib, "dbghelp")
        void ckg_stack_trace_dump() {
            CKG_LOG_PRINT("------------------ Error Stack Trace ------------------\n");
            // Date: July 02, 2024
            // NOTE(Jovanni): This only works for windows and when debug symbols are compiled into the program
            void *stack[100];
            unsigned short number_of_captured_frames;
            SYMBOL_INFO *symbol;
            HANDLE process;

            process = GetCurrentProcess();
            SymInitialize(process, NULLPTR, true);

            number_of_captured_frames = CaptureStackBackTrace(0, 100, stack, NULLPTR);
            symbol = (SYMBOL_INFO *)ckg_alloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char));
            symbol->MaxNameLen = 255;
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

            int count = 0;
            for (int i = number_of_captured_frames - 4; i > 0; i--) {
                DWORD64 displacement = 0;
                if (SymFromAddr(process, (DWORD64)(stack[i]), &displacement, symbol)) {
                    DWORD displacementLine = 0;
                    IMAGEHLP_LINE64 line;
                    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
                    if (SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &displacementLine, &line)) {
                        printf("%d: %s - %s:%d\n", count, symbol->Name, line.FileName, line.LineNumber);
                    } else {
                        printf("%d: %s\n", count, symbol->Name);
                    }
                }
                count++;
            }

            ckg_free(symbol);
            CKG_LOG_PRINT("------------------ Error Stack Trace End ------------------\n");
        }
    #elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
        void ckg_stack_trace_dump() {
            CKG_LOG_PRINT("------------------ Error Stack Trace ------------------\n");
            // backtrace
            CKG_LOG_PRINT("------------------ Error Stack Trace End ------------------\n");
        }
    #endif
#endif

#if defined(CKG_IMPL_LOGGER)
    void MACRO_ckg_log_output(CKG_LogLevel log_level, char* message, ...) {
        char log_level_strings[LOG_LEVEL_COUNT][CKG_LOG_LEVEL_CHARACTER_LIMIT] = {
            "[FATAL]  : ",
            "[ERROR]  : ",
            "[WARN]   : ",
            "[DEBUG]  : ",
            "[SUCCESS]: ",
            "",
        };

        char* log_level_format[LOG_LEVEL_COUNT] = {
            CKG_RED_BACKGROUND,
            CKG_RED,
            CKG_PURPLE,
            CKG_BLUE,
            CKG_GREEN,
            CKG_COLOR_RESET
        };

        char out_message[CKG_PLATFORM_CHARACTER_LIMIT];
        ckg_memory_zero(out_message, sizeof(out_message));

        char out_message2[CKG_PLATFORM_CHARACTER_LIMIT + CKG_LOG_LEVEL_CHARACTER_LIMIT];
        ckg_memory_zero(out_message2, sizeof(out_message2));  
        
        va_list args_list;
        va_start(args_list, message);
        vsnprintf(out_message, CKG_PLATFORM_CHARACTER_LIMIT, message, args_list);
        va_end(args_list);

        sprintf(out_message2, "%s%s", log_level_strings[log_level], out_message);

        size_t out_message2_length = ckg_cstr_length(out_message2);

        #if defined(PLATFORM_WINDOWS)
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD dwMode = 0;
            GetConsoleMode(hOut, &dwMode);
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        #endif

        if (out_message2[out_message2_length - 1] == '\n') {
            printf("%s%.*s%s\n", log_level_format[log_level], (int)(out_message2_length - 1), out_message2, CKG_COLOR_RESET);
        } else {
            printf("%s%.*s%s", log_level_format[log_level], (int)(out_message2_length), out_message2, CKG_COLOR_RESET);
        }
    }
#endif

#if defined(CKG_IMPL_ERRORS)
    internal char* CKG_ERROR_IO_STRINGS[CKG_ERROR_IO_COUNT] = {
        stringify(CKG_ERROR_IO_RESOURCE_NOT_FOUND),
        stringify(CKG_ERROR_IO_RESOURCE_TOO_BIG)
    };

    internal char* CKG_ERROR_ARGS_STRINGS[CKG_ERROR_ARGS_COUNT] = {
        stringify(CKG_ERROR_ARG_ONE_INVALID),
        stringify(CKG_ERROR_ARG_ONE_NULLPTR),
        stringify(CKG_ERROR_ARG_ONE_ZERO),
        stringify(CKG_ERROR_ARG_TWO_INVALID),
        stringify(CKG_ERROR_ARG_TWO_NULLPTR),
        stringify(CKG_ERROR_ARG_TWO_ZERO),
        stringify(CKG_ERROR_ARG_THREE_INVALID),
        stringify(CKG_ERROR_ARG_THREE_NULLPTR),
        stringify(CKG_ERROR_ARG_THREE_ZERO),
        stringify(CKG_ERROR_ARG_FOUR_INVALID),
        stringify(CKG_ERROR_ARG_FOUR_NULLPTR),
        stringify(CKG_ERROR_ARG_FOUR_ZERO)
    };

    char* ckg_error_str(CKG_Error error_code) {
        int error_type = CKG_ERROR_TYPE_MASK & error_code;
        int error_index = (~CKG_ERROR_TYPE_MASK) & error_code;
            
        if (error_type == CKG_ERROR_IO_MASK) {
            return CKG_ERROR_IO_STRINGS[error_index];
        } else if (error_type == CKG_ERROR_ARGS_MASK) {
            return CKG_ERROR_ARGS_STRINGS[error_index];
        }

        return NULLPTR; // SHOULD NEVER GET HERE!
    }

    internal void ckg_error_safe_set(CKG_Error* error, CKG_Error error_code) {
        if (error) {
            *error = error_code;
        }
    }
#endif 

#if defined(CKG_IMPL_MEMORY)
    internal void* ckg_default_libc_malloc(CKG_Allocator* allocator, size_t allocation_size) {
        (void)allocator;
        return malloc(allocation_size);
    }

    internal void ckg_default_libc_free(CKG_Allocator* allocator, void* data) {
        (void)allocator;
        free(data);
    }

    internal CKG_Allocator allocator = {ckg_default_libc_malloc, ckg_default_libc_free, 0};

    void ckg_bind_custom_allocator(CKG_Alloc_T* a, CKG_Free_T* f, void* ctx) {
        ckg_assert_msg(a, "Alloc function is nullptr\n");
        ckg_assert_msg(f, "Free function is nullptr\n");
        
        allocator.allocate = a;
        allocator.free = f;

        if (ctx) {
            allocator.ctx = ctx;
        }
    }

    void* ckg_alloc(size_t allocation_size) {
        ckg_assert(allocation_size != 0);

        void* ret = allocator.allocate(&allocator, allocation_size);
        ckg_memory_zero(ret, allocation_size);
        return ret;
    }

    void* MACRO_ckg_free(void* data) {
        ckg_assert(data);
        
        allocator.free(&allocator, data);
        return NULLPTR;
    }

    void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size) {
        ckg_assert(old_allocation_size != 0);
        ckg_assert(new_allocation_size != 0);

        void* ret = ckg_alloc(new_allocation_size);
        ckg_memory_copy(data, ret, old_allocation_size, new_allocation_size);
        ckg_free(data);
        return ret;
    }

    bool ckg_memory_compare(void* buffer_one, void* buffer_two, size_t buffer_one_size, size_t buffer_two_size) {
        ckg_assert(buffer_one);
        ckg_assert(buffer_two);

        if (buffer_one_size != buffer_two_size) {
            return false;
        }

        u8* buffer_one_data = (u8*)buffer_one;
        u8* buffer_two_data = (u8*)buffer_two;
        for (size_t i = 0; i < buffer_one_size; i++) {
            if (buffer_one_data[i] != buffer_two_data[i]) {
                return false;
            }
        }

        return true;
    }

    void ckg_memory_copy(void* source, void* destination, size_t source_size_in_bytes, size_t destination_size_in_bytes) {
        ckg_assert(source);
        ckg_assert(destination);
        ckg_assert(source_size_in_bytes <= destination_size_in_bytes);
        if (source_size_in_bytes == 0) {
            return;
        }

        u8* temp_data_copy = (u8*)ckg_alloc(source_size_in_bytes);
        for (size_t i = 0; i < source_size_in_bytes; i++) {
            temp_data_copy[i] = ((u8*)source)[i];
        }

        for (size_t i = 0; i < source_size_in_bytes; i++) {
            ((u8*)destination)[i] = temp_data_copy[i];
        }

        ckg_free(temp_data_copy);
    }

    void ckg_memory_zero(void* data, size_t data_size_in_bytes) {
        for (size_t i = 0; i < data_size_in_bytes; i++) {
            ((u8*)data)[i] = 0;
        }
    }

    // Date: September 12, 2024
    // TODO(Jovanni): MAKE SURE YOU TEST THIS. Its seems to maybe work?
    void MACRO_ckg_memory_delete_index(void* data, size_t number_of_elements, size_t data_capacity, size_t element_size_in_bytes, size_t index) {
        ckg_assert((s32)number_of_elements - 1 >= 0);
        ckg_assert(index < data_capacity);
        ckg_assert(index >= 0);

        u8* byte_data = (u8*)data;

        size_t total_size = element_size_in_bytes * data_capacity;
        size_t source_offset = (index + 1) * element_size_in_bytes;
        size_t dest_offset =  index * element_size_in_bytes;

        size_t payload_source_size = (number_of_elements * element_size_in_bytes) - source_offset;
        ckg_memory_copy(byte_data + source_offset, byte_data + dest_offset, payload_source_size, total_size - source_offset);
    }

    // Date: September 12, 2024
    // TODO(Jovanni): MAKE SURE YOU TEST THIS. Its seems to maybe work?
    void MACRO_ckg_memory_insert_index(void* data, size_t number_of_elements, size_t data_capacity, size_t element_size_in_bytes, size_t index) {
        ckg_assert((number_of_elements + 1) < data_capacity);
        ckg_assert(index < data_capacity - 1);
        ckg_assert(index >= 0);

        u8* byte_data = (u8*)data;

        size_t total_size = element_size_in_bytes * data_capacity;
        size_t source_offset = index * element_size_in_bytes;
        size_t dest_offset = (index + 1) * element_size_in_bytes;

        size_t payload_source_size = (number_of_elements * element_size_in_bytes) - source_offset;
        ckg_memory_copy(byte_data + source_offset, byte_data + dest_offset, payload_source_size, total_size - source_offset);
    }
#endif

#if defined(CKG_IMPL_ARENA)
    internal bool ckg_arena_flag_is_set(CKG_Arena* arena, CKG_ArenaFlag flag) {
        return arena->flags & flag;
    }

    CKG_Arena ckg_arena_create_custom(void* memory, size_t allocation_size, u32 flags, u8 alignment) {
        ckg_assert_msg(memory, "Memory can't be a null pointer!\n");
        ckg_assert_msg(allocation_size != 0, "Can't have a zero allocation size!\n");
        ckg_assert_msg(!((flags & CKG_ARENA_FLAG_CIRCULAR) && (flags & CKG_ARENA_FLAG_FIXED)), "Can't have both a fixed an circular arena!\n");

        CKG_Arena arena;
        arena.used = 0;
        arena.capacity = allocation_size;
        arena.base_address = (u8*)memory;
        arena.alignment = alignment == 0 ? 8 : alignment;
        arena.flags = flags;

        return arena;
    }

    void ckg_arena_free(CKG_Arena* arena) {
        ckg_assert_msg(arena->flags != CKG_ARENA_FLAG_INVALID, "Arena is invalid!\n");

        if (!(arena->flags & CKG_ARENA_FLAG_STACK_MEMORY)) {
            ckg_free(arena->base_address);
        }

        arena->flags = (u32)CKG_ARENA_FLAG_INVALID;
    }

    void ckg_arena_zero(CKG_Arena* arena) {
        ckg_assert_msg(arena->flags != CKG_ARENA_FLAG_INVALID, "Arena is invalid!\n");

        ckg_memory_zero(arena->base_address, arena->capacity);
        arena->used = 0;
    }

    void ckg_arena_reset(CKG_Arena* arena) {
        ckg_assert_msg(arena->flags != CKG_ARENA_FLAG_INVALID, "Arena is invalid!\n");

        arena->used = 0;
    }

    void* ckg_arena_push_custom(CKG_Arena* arena, size_t element_size) {
        ckg_assert_msg(arena->flags != CKG_ARENA_FLAG_INVALID, "Arena is invalid!\n");
        ckg_assert_msg(element_size != 0, "Element size can't be zero!\n");

        if (arena->flags & CKG_ARENA_FLAG_FIXED) {
            ckg_assert_msg((arena->used + element_size <= arena->capacity), "Ran out of arena memory!\n");
        } else if (arena->flags & CKG_ARENA_FLAG_CIRCULAR) {
            if ((arena->used + element_size > arena->capacity)) {
                arena->used = sizeof(CKG_Arena);
                ckg_assert_msg((arena->used + element_size <= arena->capacity), "Element size exceeds circular arena allocation capacity!\n");
            }
        }

        u8* ret = arena->base_address + arena->used;
        arena->used += element_size;
        if ((arena->used & (arena->alignment - 1)) != 0) { // if first bit is set then its not aligned
            arena->used += (arena->alignment - (arena->used & (arena->alignment - 1)));
        }

        return ret;
    }

    void MACRO_ckg_arena_pop(CKG_Arena* arena, size_t bytes_to_pop) {
        ckg_assert_msg(arena->flags != CKG_ARENA_FLAG_INVALID, "Arena is invalid!\n");

        arena->used -= bytes_to_pop;
    }

    void ckg_arena_begin_temp(CKG_Arena* arena) {
        ckg_assert_msg(arena->flags != CKG_ARENA_FLAG_INVALID, "Arena is invalid!\n");

        arena->used_save_point = arena->used;
    }

    void ckg_arena_end_temp(CKG_Arena* arena) {
        ckg_assert_msg(arena->flags != CKG_ARENA_FLAG_INVALID, "Arena is invalid!\n");
        ckg_memory_zero(arena->base_address + arena->used_save_point, arena->capacity - arena->used_save_point);

        arena->used = arena->used_save_point;
        arena->used_save_point = 0;
    }
#endif

#if defined(CKG_IMPL_STRING)
    char* ckg_cstr_alloc(char* s1, size_t length) {
        char* ret = ckg_alloc(length + 1) ;
        ckg_memory_copy(s1, ret, length, length);
        return ret;
    }

    size_t ckg_cstr_length(char* cstring) {
        ckg_assert(cstring);

        if (!cstring) {
            return 0; // This should never get here but the compiler want this
        }

        size_t length = 0;
        char* cursor = (char*)cstring;
        while(*cursor++ != '\0') {
            length++;
        }

        return length;
    }

    void ckg_cstr_clear(char* s1, size_t length) {
        ckg_memory_zero(s1, length);
    }

    CKG_StringView ckg_sv_create(char* data, size_t length) {
        ckg_assert(data);
        ckg_assert(length >= 0);

        CKG_StringView ret;
        ret.data = data;
        ret.length = length;

        return ret;
    }

    CKG_StringView ckg_sv_between_delimiters(char* str, u64 str_length, char* start_delimitor, u64 start_delimitor_length, char* end_delimitor, u64 end_delimitor_length) {
        ckg_assert(str);
        ckg_assert(start_delimitor);
        ckg_assert(end_delimitor);
        ckg_assert(!ckg_str_equal(start_delimitor, start_delimitor_length, end_delimitor, end_delimitor_length));

        s64 start_delimitor_index = ckg_str_index_of(str, str_length, start_delimitor, start_delimitor_length); 
        s64 end_delimitor_index = ckg_str_index_of(str, str_length, end_delimitor, end_delimitor_length);
        if (start_delimitor_index == -1 || end_delimitor_index == -1) {
            return CKG_SV_EMPTY();
        }

        if (start_delimitor_index == -1 || end_delimitor_index == -1) {
            return CKG_SV_EMPTY();
        } else if (start_delimitor_index > end_delimitor_index) {
            return CKG_SV_EMPTY(); // The start delimtor is after the end delimitor
        }

        CKG_StringView ret = CKG_SV_EMPTY();
        u64 start_str_index = (u64)(start_delimitor_index + start_delimitor_length);
        ret.data = str + start_str_index;
        ret.length = end_delimitor_index - start_str_index;

        return ret;
    }

    CKG_StringView* ckg_sv_split(char* data, size_t length, char* delimitor, size_t delimitor_length) {
        ckg_assert(data);
        ckg_assert(delimitor);
        ckg_assert_msg(delimitor_length > 0, "delimitor can not be a empty string!\n");

        if (length == 0) {
            CKG_StringView* ret_vector = NULLPTR;
            CKG_StringView current = ckg_sv_create(data, length);
            ckg_vector_push(ret_vector, current);

            return ret_vector;
        }

        CKG_StringView* ret_vector = NULLPTR;
        CKG_StringView str_view = ckg_sv_create(data, length);
        while (true) {
            s64 found_index = ckg_str_index_of(str_view.data, str_view.length, delimitor, delimitor_length);
            if (found_index == -1) {
                ckg_vector_push(ret_vector, str_view);
                return ret_vector;
            }

            if (found_index == 0) {
                ckg_vector_push(ret_vector, CKG_SV_EMPTY());
            } else {
                CKG_StringView substring = ckg_sv_create(str_view.data, found_index);
                ckg_vector_push(ret_vector, substring);
            }

            str_view.data += (found_index + 1);
            str_view.length -= (found_index + 1);
        }

        return ret_vector;
    }

    bool ckg_str_equal(char* s1, size_t s1_length, char* s2, size_t s2_length) {
        return ckg_memory_compare(s1, s2, s1_length, s2_length);
    }

    void ckg_str_copy(char* s1, size_t s1_capacity, char* s2, size_t s2_length) {
        ckg_memory_zero((void*)s1, s1_capacity);
        ckg_memory_copy(s2, s1, s2_length, s1_capacity);
    }

    void ckg_str_insert(char* str, size_t str_length, size_t str_capacity, char* to_insert, size_t to_insert_length, size_t index) {
        ckg_assert(str);
        ckg_assert(to_insert);

        size_t new_length = str_length + to_insert_length;

        ckg_assert(index >= 0 && index <= str_length);
        ckg_assert_msg(new_length < str_capacity, "ckg_str_insert: str_capacity is %lld but new valid cstring length is %d + %d + 1(null_term)= %d\n", str_capacity, str_length, to_insert_length, new_length + 1);
        u8* move_source_ptr = (u8*)(str + index);
        u8* move_dest_ptr = (u8*)(move_source_ptr + to_insert_length);

        ckg_memory_copy(move_source_ptr, move_dest_ptr, str_length - index, str_capacity - (index + to_insert_length));
        
        u8* copy_dest_ptr = (u8*)(str + index);
        ckg_memory_copy(to_insert, copy_dest_ptr, to_insert_length, str_capacity);
    }

    void ckg_str_insert_char(char* str, size_t str_length, size_t str_capacity, char to_insert, size_t index) {
        ckg_assert(str);
        ckg_assert(to_insert);
        ckg_assert(index >= 0 && index <= str_length);

        size_t to_insert_length = 1;
        bool expression = (str_length + to_insert_length) < str_capacity;
        ckg_assert_msg(expression, "ckg_str_insert_char: str overflow new_capacity_required: %d >= current_capacity: %lld\n",  str_length + to_insert_length, str_capacity);

        char* source_ptr = str + index;
        ckg_memory_copy(source_ptr, source_ptr + 1, str_length - index, str_capacity - (index + 1));
        str[index] = to_insert;
    }

    void ckg_str_append(char* str, size_t str_length, size_t str_capacity, char* to_append, size_t to_append_length) {
        ckg_str_insert(str, str_length, str_capacity, to_append, to_append_length, str_length);
    }

    void ckg_str_append_char(char* str, size_t str_length, size_t str_capacity, char to_append) {
        ckg_str_insert_char(str, str_length, str_capacity, to_append, str_length);
    }

    void ckg_str_reverse(char* str, size_t str_length, char* returned_reversed_string_buffer, size_t reversed_buffer_capacity) {
        ckg_assert(str);
        ckg_assert(reversed_buffer_capacity > str_length);

        for (s64 i = str_length - 1; i >= 0; i--) {
            ckg_str_append_char(returned_reversed_string_buffer, (str_length - 1) - i, reversed_buffer_capacity, str[i]);
        }
    }

    s64 ckg_str_index_of(char* str, size_t str_length, char* substring, size_t substring_length) {
        ckg_assert(str);
        ckg_assert(substring);

        if (str_length == 0 && substring_length == 0) {
            return 0;
        } else if (substring_length == 0) {
            return -1;
        } else if (str_length == 0) {
            return -1;
        }

        if (substring_length > str_length) {
            return -1;
        }
        
        s64 ret_index = -1;
        for (size_t i = 0; i <= str_length - substring_length; i++) {
            if (ret_index != -1) {
                break;
            }
            
            if (str[i] != substring[0]) {
                continue;
            }

            CKG_StringView current_view = ckg_sv_create(str + i, substring_length);
            if (ckg_str_equal(substring, substring_length, current_view.data, current_view.length)) {
                ret_index = i;
                break;
            }
        }

        return ret_index; // returns -1 if not found
    }

    bool ckg_str_contains(char* str, size_t str_length, char* contains, size_t contains_length) {
        ckg_assert(str);
        ckg_assert(contains);

        return ckg_str_index_of(str, str_length, contains, contains_length) != -1;
    }

    s64 ckg_str_last_index_of(char* str, size_t str_length, char* substring, size_t substring_length) {
        ckg_assert(str);
        ckg_assert(substring);

        if (str_length == 0 && substring_length == 0) {
            return 0;
        } else if (substring_length == 0) {
            return -1;
        } else if (str_length == 0) {
            return -1;
        }

        if (substring_length > str_length) {
            return -1;
        }
        
        s64 ret_index = -1;
        for (size_t i = 0; i <= (str_length - substring_length); i++) {
            if (str[i] != substring[0]) {
                continue;
            }

            CKG_StringView current_view = ckg_sv_create(str + i, substring_length);
            if (ckg_str_equal(current_view.data, current_view.length, substring, substring_length)) {
                ret_index = i;
            }
        }

        return ret_index;
    }

    bool ckg_str_starts_with(char* str, size_t str_length, char* starts_with, size_t starts_with_length) {
        ckg_assert(str);
        ckg_assert(starts_with);

        if (str_length == 0 && starts_with_length == 0) {
            return true;
        } else if (str[0] != starts_with[0] || str_length < starts_with_length) {
            return false;
        }
        
        if (ckg_str_equal(str, starts_with_length, starts_with, starts_with_length)) {
            return true;
        }

        return false;
    }

    bool ckg_str_ends_with(char* str, size_t str_length, char* ends_with, size_t ends_with_length) {
        ckg_assert(str);
        ckg_assert(ends_with);

        if ((str_length == 0) || (ends_with_length == 0)) {
            return true;
        } else if (str_length < ends_with_length) {
            return false;
        }

        size_t start_index = MAX(str_length - 1, 0) - MAX(ends_with_length - 1, 0);
        if (str[start_index] != ends_with[0]) {
            return false;
        }

        if (ckg_str_equal(str + start_index, ends_with_length, ends_with, ends_with_length)) {
            return true;
        }

        return false;
    }

    char* MACRO_ckg_cstr_va_sprint(size_t* allocation_size_ptr, char* fmt, va_list args) {
        size_t allocation_size = vsnprintf(NULLPTR, 0, fmt, args) + 1; // + 1 because null terminator
        char* ret = ckg_alloc(allocation_size);
        vsnprintf(ret, allocation_size, fmt, args);

        if (allocation_size_ptr != NULLPTR) {
            *allocation_size_ptr = allocation_size;
        } 

        return ret;
    }

    char* MACRO_ckg_cstr_sprint(size_t* allocation_size_ptr, char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        char* ret = MACRO_ckg_cstr_va_sprint(allocation_size_ptr, fmt, args);
        va_end(args);

        return ret;
    }
#endif

#if defined(CKG_IMPL_CHAR)
    bool ckg_char_is_alpha(char c) {
        c = (c & (0b11011111)); // mask off the 32 bit
        return ckg_char_is_upper(c);
    }

    bool ckg_char_is_alpha_numeric(char c) {
        return ckg_char_is_alpha(c) || ckg_char_is_digit(c);
    }
#endif


#if defined(CKG_IMPL_COLLECTIONS)
    //
    // ========== START CKG_VECTOR ==========
    //
    void* ckg_vector_grow(void* vector, size_t element_size, size_t capacity) {
        if (vector == NULLPTR) {
            size_t real_capacity = (capacity > 0 ? capacity : VECTOR_DEFAULT_CAPACITY);
            vector = ckg_alloc(sizeof(CKG_VectorHeader) + (real_capacity * element_size));
            vector = (u8*)vector + sizeof(CKG_VectorHeader);
            ckg_vector_header_base(vector)->capacity = real_capacity;
            ckg_vector_header_base(vector)->element_size = element_size;
        }

        size_t count = ckg_vector_count(vector);
        size_t capactiy = ckg_vector_capacity(vector);

        if (capactiy < count + 1) {
            size_t old_allocation_size = sizeof(CKG_VectorHeader) + (capactiy * element_size);
            size_t new_capactiy = capactiy * 2;
            size_t new_allocation_size = sizeof(CKG_VectorHeader) + (new_capactiy * element_size);

            vector = ckg_realloc(ckg_vector_header_base(vector), old_allocation_size, new_allocation_size);
            vector = (u8*)vector + sizeof(CKG_VectorHeader);

            ckg_vector_header_base(vector)->element_size = element_size;
            ckg_vector_header_base(vector)->count = count;
            ckg_vector_header_base(vector)->capacity = new_capactiy;
        }

        return vector;
    }

    void* MACRO_ckg_vector_free(void* vector) {
        CKG_VectorHeader* vector_base = ckg_vector_header_base(vector);
        vector_base->count = 0;
        vector_base->capacity = 0;
        ckg_free(vector_base);

        return vector_base;
    }
    //
    // ========== END CKG_VECTOR ==========
    //

    //
    // ========== START CKG_RingBuffer ==========
    //
    // Date: March 22, 2025
    // NOTE(Jovanni): Do we actually need this at all because we have a circular arena?
    void* ckg_ring_buffer_create(size_t element_size, int capacity) {
        size_t allocation_size = sizeof(CKG_RingBufferHeader) + (capacity * element_size);
        CKG_RingBufferHeader* header = ckg_alloc(allocation_size);
        header->element_size = element_size;
        header->capacity = capacity;

        void* buffer = (u8*)header + sizeof(CKG_RingBufferHeader);
        return buffer;
    }

    void* MACRO_ckg_ring_buffer_free(void* vector) {
        CKG_RingBufferHeader* ring_base = ckg_ring_buffer_header_base(vector);
        ring_base->count = 0;
        ring_base->capacity = 0;
        ring_base->read = 0;
        ring_base->write = 0;
        ckg_free(vector);

        return NULLPTR;
    }
    //
    // ========== END CKG_RingBuffer ==========
    //

    //
    // ========== START CKG_LinkedList ==========
    //
    CKG_LinkedList* MACRO_ckg_linked_list_create(size_t element_size_in_bytes, bool is_pointer_type) {
        CKG_LinkedList* ret = (CKG_LinkedList*)ckg_alloc(sizeof(CKG_LinkedList));
        ret->count = 0;
        ret->element_size_in_bytes = element_size_in_bytes;
        ret->head = NULLPTR;
        ret->tail = NULLPTR;
        ret->is_pointer_type = is_pointer_type;
        return ret;
    }

    CKG_Node* MACRO_ckg_node_create(CKG_LinkedList* linked_list, void* data) {
        CKG_Node* ret = (CKG_Node*)ckg_alloc(sizeof(CKG_Node));
        if (linked_list->is_pointer_type) {
            ret->data = data;
        } else {
            ret->data = ckg_alloc(linked_list->element_size_in_bytes); // user has to free
            ckg_memory_copy(data, ret->data, linked_list->element_size_in_bytes, linked_list->element_size_in_bytes); 
        }

        ret->element_size_in_bytes = linked_list->element_size_in_bytes;
        ret->next = NULLPTR;
        ret->prev = NULLPTR;
        return ret;
    }
    #define ckg_node_create(linked_list, data) MACRO_ckg_node_create(linked_list, data)

    /**
     * @brief returns a null ptr
     * 
     * @param node 
     * @return CKG_Node* 
     */
    internal CKG_Node* MACRO_ckg_node_free(CKG_LinkedList* linked_list, CKG_Node* node) {
        ckg_assert(linked_list);
        ckg_assert(node);
        node->element_size_in_bytes = 0;
        node->next = NULLPTR;
        node->prev = NULLPTR;
        ckg_free(node);

        return node;
    }
    #define ckg_node_free(linked_list, node) node = MACRO_ckg_node_free(linked_list, node)


    /**
     * @brief returns a null ptr
     * 
     * @param node 
     * @return CKG_Node* 
     */
    internal CKG_Node* MACRO_ckg_node_data_free(CKG_LinkedList* linked_list, CKG_Node* node) {
        ckg_assert(linked_list);
        ckg_assert(node);
        ckg_assert(node->data);
        node->element_size_in_bytes = 0;
        node->next = NULLPTR;
        node->prev = NULLPTR;
        if (!linked_list->is_pointer_type) {
            ckg_free(node->data);
        }
        ckg_free(node);

        return node;
    }
    #define ckg_node_data_free(linked_list, node) node = MACRO_ckg_node_data_free(linked_list, node)

    CKG_Node* ckg_linked_list_insert(CKG_LinkedList* linked_list, size_t index, void* data) {
        ckg_assert(linked_list);
        ckg_assert(data);
        ckg_assert(index >= 0);

        size_t old_count = linked_list->count++;
        if (linked_list->head == NULLPTR) { // there is not a head and by definition no tail
            CKG_Node* new_node_to_insert = ckg_node_create(linked_list, data);
            linked_list->head = new_node_to_insert;
            linked_list->tail = new_node_to_insert;

            return linked_list->head;
        }

        ckg_assert(index <= old_count);
        CKG_Node* new_node_to_insert = ckg_node_create(linked_list, data);

        if (index == 0) { // insert at head
            linked_list->head->prev = new_node_to_insert;
            new_node_to_insert->next = linked_list->head;
            linked_list->head = new_node_to_insert;
            
            return new_node_to_insert;
        }

        if (index == old_count) { // insert at tail
            linked_list->tail->next = new_node_to_insert;
            new_node_to_insert->prev = linked_list->tail;
            linked_list->tail = new_node_to_insert;

            return new_node_to_insert;
        }

        // Date: July 19, 2024
        // TODO(Jovanni): check if index is closer to count or not then reverse the loop if approaching from the tail end.
        // as opposed to the head end.
        CKG_Node* current_node = linked_list->head; 
        for (size_t i = 0; i < index; i++) {
            current_node = current_node->next;
        }

        new_node_to_insert->prev = current_node;
        new_node_to_insert->next = current_node->next;

        current_node->next->prev = new_node_to_insert;
        current_node->next = new_node_to_insert;

        return new_node_to_insert;
    }

    CKG_Node* ckg_linked_list_get_node(CKG_LinkedList* linked_list, size_t index) {
        ckg_assert(linked_list);
        CKG_Node* current_node = linked_list->head; 
        for (size_t i = 0; i < index; i++) {
            current_node = current_node->next;
        }

        return current_node;
    }

    void* ckg_linked_list_get(CKG_LinkedList* linked_list, size_t index) {
        return ckg_linked_list_get_node(linked_list, index)->data;
    }

    void* ckg_linked_list_peek_head(CKG_LinkedList* linked_list) {
        return ckg_linked_list_get_node(linked_list, 0)->data;
    }

    void* ckg_linked_list_peek_tail(CKG_LinkedList* linked_list) {
        return ckg_linked_list_get_node(linked_list, linked_list->count - 1)->data;
    }

    CKG_Node* ckg_linked_list_push(CKG_LinkedList* linked_list, void* data) {
        return ckg_linked_list_insert(linked_list, linked_list->count, data);
    }

    size_t ckg_linked_list_node_to_index(CKG_LinkedList* linked_list, CKG_Node* address) {
        CKG_Node* current_node = linked_list->head; 
        for (size_t i = 0; i < linked_list->count + 1; i++) {
            if (current_node == address) {
                return i;
            }
            current_node = current_node->next;
        }

        ckg_assert(false); // couldn't match a node to an address
        return 0; // should never get here
    }

    CKG_Node ckg_linked_list_pop(CKG_LinkedList* linked_list) {
        return ckg_linked_list_remove(linked_list, linked_list->count - 1);
    }

    CKG_Node ckg_linked_list_remove(CKG_LinkedList* linked_list, size_t index) {
        ckg_assert(linked_list); 
        ckg_assert(linked_list->count > 0); 
        ckg_assert(index >= 0);

        size_t old_count = linked_list->count--;
        if (index == 0 && old_count == 1) { // removing the head fully
            CKG_Node ret = *linked_list->head;
            ckg_node_free(linked_list, linked_list->head);
            linked_list->head = NULLPTR;

            return ret;
        }

        if (index == 0) { // remove head
            CKG_Node* cached_head = linked_list->head;
            linked_list->head = linked_list->head->next;
            CKG_Node ret = *cached_head; 
            ckg_node_free(linked_list, cached_head);

            return ret;
        }

        ckg_assert(index < old_count);
        if (index == (old_count - 1)) { // remove tail
            CKG_Node* cached_tail = linked_list->tail;
            linked_list->tail = linked_list->tail->prev;
            CKG_Node ret = *cached_tail; 
            ckg_node_free(linked_list, cached_tail);

            return ret;
        }

        CKG_Node* current_node = linked_list->head; 
        for (size_t i = 0; i < index; i++) {
            current_node = current_node->next;
        }

        current_node->next->prev = current_node->prev;
        current_node->prev->next = current_node->next;
        CKG_Node ret = *current_node; 
        ckg_node_free(linked_list, current_node);

        return ret;
    }

    void* MACRO_ckg_linked_list_free(CKG_LinkedList* linked_list) {
        ckg_assert(linked_list); 
        CKG_Node* current_node = linked_list->head; 
        CKG_Node* next_node = NULLPTR; 
        for (size_t i = 0; i < linked_list->count; i++) {
            next_node = current_node->next;
            ckg_node_data_free(linked_list, current_node);
            current_node = next_node;
        }
        ckg_free(linked_list);

        return linked_list;
    }
    //
    // ========== END CKG_LinkedList ==========
    //
#endif

#if defined(CKG_IMPL_SERIALIZATION)
   void ckg_serialize_collection(void* collection, FILE* file_handle, CKG_CollectionType collection_type, CKG_DataType data_type) {
        ckg_assert(file_handle);

        switch (collection_type) {
            case CKG_COLLECTION_VECTOR: {
                CKG_VectorHeader* header = ckg_vector_header_base(collection);
                fwrite(header, sizeof(CKG_VectorHeader), 1, file_handle);
                if (data_type == CKG_DATA_TYPE_BITS) {
                    fwrite(collection, (header->element_size * header->count), 1, file_handle);
                } else if (data_type == CKG_DATA_TYPE_STRING_VIEW) {
                    CKG_StringView* sv_vector = (CKG_StringView*)collection;
                    for (int i = 0; i < header->count; i++) {
                        CKG_StringView sv = sv_vector[i];
                        fwrite(&sv.length, sizeof(size_t), 1, file_handle);
                        fwrite(sv.data, sv.length, 1, file_handle);
                    }
                } else if (data_type == CKG_DATA_TYPE_CSTRING) {
                    char** string_vector = (char**)collection;
                    for (int i = 0; i < header->count; i++) {
                        char* current_string = string_vector[i];
                        size_t count = ckg_cstr_length(current_string);
                        fwrite(&count, sizeof(size_t), 1, file_handle);
                        fwrite(current_string, count, 1, file_handle);
                    }
                }
            } break;

            case CKG_COLLECTION_RING_BUFFER: {
                CKG_RingBufferHeader* header = ckg_ring_buffer_header_base(collection);
                fwrite(header, sizeof(CKG_VectorHeader), 1, file_handle);
                if (data_type == CKG_DATA_TYPE_BITS) {
                    fwrite(collection, (header->element_size * header->count), 1, file_handle);
                } else if (data_type == CKG_DATA_TYPE_STRING_VIEW) {
                    CKG_StringView* string_vector = (CKG_StringView*)collection;
                    for (int i = 0; i < header->count; i++) {
                        CKG_StringView sv = string_vector[i];
                        fwrite(&sv.length, sizeof(size_t), 1, file_handle);
                        fwrite(sv.data, sv.length, 1, file_handle);
                    }
                } else if (data_type == CKG_DATA_TYPE_CSTRING) {
                    char** string_vector = (char**)collection;
                    for (int i = 0; i < header->count; i++) {
                        char* current_string = string_vector[i];
                        size_t count = ckg_cstr_length(current_string);
                        fwrite(&count, sizeof(size_t), 1, file_handle);
                        fwrite(current_string, count, 1, file_handle);
                    }
                }
            } break;

            case CKG_COLLECTION_LINKED_LIST: {

            } break;
        }
    }

    void* ckg_deserialize_collection(FILE* file_handle, CKG_CollectionType collection_type, CKG_DataType data_type) {
        ckg_assert(file_handle);

        switch (collection_type) {
            case CKG_COLLECTION_STACK:
            case CKG_COLLECTION_VECTOR: {
                CKG_VectorHeader header;
                fread(&header, sizeof(CKG_VectorHeader), 1, file_handle);

                if (data_type == CKG_DATA_TYPE_BITS) {
                    u8* vector = ckg_vector_grow(NULLPTR, header.element_size, header.capacity);
                    fread(vector, header.element_size, header.count, file_handle);
                    return vector;
                } else if (data_type == CKG_DATA_TYPE_STRING_VIEW) {
                    CKG_StringView* sv_vector = ckg_vector_grow(NULLPTR, header.element_size, header.capacity);

                    for (int i = 0; i < header.count; i++) {
                        CKG_StringView sv;
                        fread(&sv.length, sizeof(size_t), 1, file_handle);

                        sv.data = ckg_alloc(sv.length + 1);
                        fread((char*)sv.data, sv.length, 1, file_handle);
                       
                        ckg_vector_push(sv_vector, sv);
                    }

                    return sv_vector;
                } else if (data_type == CKG_DATA_TYPE_CSTRING) {
                    char** string_vector = ckg_vector_grow(NULLPTR, header.element_size, header.capacity);

                    for (int i = 0; i < header.count; i++) {
                        size_t char_count = 0;
                        fread(&char_count, sizeof(size_t), 1, file_handle);
                        char* current_string = ckg_alloc(char_count + 1); // prob want a way to specify if you should allocate or not
                        fread(current_string, char_count, 1, file_handle);

                        ckg_vector_push(string_vector, current_string);
                    }

                    return string_vector;
                }
            } break;

            case CKG_COLLECTION_RING_BUFFER: {
                CKG_RingBufferHeader header;
                fread(&header, sizeof(CKG_RingBufferHeader), 1, file_handle);

                if (data_type == CKG_DATA_TYPE_BITS) {
                    u8* ring_buffer = ckg_ring_buffer_create(header.element_size, header.capacity);
                    fread(ring_buffer, header.element_size, header.count, file_handle);
                    return ring_buffer;
                } else if (data_type == CKG_DATA_TYPE_STRING_VIEW) {
                    CKG_StringView* sv_ring_buffer = ckg_ring_buffer_create(header.element_size, header.capacity);

                    for (int i = 0; i < header.count; i++) {
                        CKG_StringView sv;
                        fread(&sv.length, sizeof(size_t), 1, file_handle);
                        sv.data = ckg_alloc(sv.length + 1);
                        fread((char*)sv.data, sv.length, 1, file_handle);

                        ckg_ring_buffer_enqueue(sv_ring_buffer, sv);
                    }

                    return sv_ring_buffer;
                } else if (data_type == CKG_DATA_TYPE_CSTRING) {
                    char** string_ring_buffer = ckg_ring_buffer_create(header.element_size, header.capacity);

                    for (int i = 0; i < header.count; i++) {
                        size_t char_count = 0;
                        fread(&char_count, sizeof(size_t), 1, file_handle);
                        char* current_string = ckg_alloc(char_count + 1);
                        fread(current_string, char_count, 1, file_handle);

                        ckg_ring_buffer_enqueue(string_ring_buffer, current_string);
                    }

                    return string_ring_buffer;
                }
            } break;

            case CKG_COLLECTION_LINKED_LIST:{
                // return linked_list;
            } break;
        }

        return NULLPTR;
    }
#endif

#if defined(CKG_IMPL_IO)
    #if defined(PLATFORM_WINDOWS)
        bool ckg_io_path_exists(char* path) {
            return (GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES);
        }

        u8* ckg_io_read_entire_file(char* file_name, size_t* returned_file_size, CKG_Error* err) {
            ckg_assert(ckg_io_path_exists(file_name));

            HANDLE file_handle = CreateFileA(file_name, GENERIC_READ, 0, NULLPTR, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULLPTR);
            if (file_handle == INVALID_HANDLE_VALUE) {
                ckg_error_safe_set(err, CKG_ERROR_IO_RESOURCE_NOT_FOUND);

                return NULLPTR;
            }

            LARGE_INTEGER large_int = {0};
            BOOL success = GetFileSizeEx(file_handle, &large_int);
            ckg_assert(success);

            size_t file_size = large_int.QuadPart + 1;
            if (file_size > SIZE_MAX) {
                CloseHandle(file_handle);
                ckg_error_safe_set(err, CKG_ERROR_IO_RESOURCE_TOO_BIG);

                return NULLPTR;
            }

            u8* file_data = (u8*)ckg_alloc(file_size + 1); // +1 for null-terminator

            DWORD bytes_read = 0;
            success = ReadFile(file_handle, file_data, (DWORD)file_size, &bytes_read, NULLPTR);
            CloseHandle(file_handle);

            ckg_assert(success && bytes_read == (file_size - 1));

            if (returned_file_size) {
                *returned_file_size = (size_t)file_size;
            }

            return file_data;
        }
    #else
        bool ckg_io_path_exists(char* path) {
            FILE *fptr = fopen(path, "r");

            if (fptr == NULLPTR) {
                return false;
            }

            fclose(fptr);

            return true;
        }

        u8* ckg_io_read_entire_file(char* file_name, size_t* returned_file_size, CKG_Error* err) {
            ckg_assert_msg(ckg_io_path_exists(file_name), "Path doesn't exist\n");

            FILE* file_handle = fopen(file_name, "rb");
            if (file_handle == NULLPTR) {
                ckg_error_safe_set(err, CKG_ERROR_IO_RESOURCE_NOT_FOUND)

                return NULLPTR;
            }

            fseek(file_handle, 0L, SEEK_END);
            size_t file_size = ftell(file_handle);
            rewind(file_handle);

            u8* file_data = ckg_alloc(file_size + 1); // +1 for null terminator

            if (fread(file_data, file_size, 1, file_handle) != 1) {
                fclose(file_handle);
                ckg_free(file_data);
                ckg_assert_msg(false, "Error reading file");
                return NULLPTR;
            }

            fclose(file_handle);

            if (returned_file_size) {
                *returned_file_size = file_size + 1;
            }

            return file_data;
        }
    #endif
#endif

#if defined(CKG_IMPL_OS)
    #if defined(PLATFORM_WINDOWS)
        CKG_DLL ckg_io_load_dll(char* dll_name, CKG_Error* err) {
            HMODULE library = LoadLibraryA(dll_name);
            if (!library) {
                ckg_error_safe_set(err, CKG_ERROR_IO_RESOURCE_NOT_FOUND);
                return NULLPTR;
            }

            return library;
        }

        void* ckg_os_get_proc_address(CKG_DLL dll, char* proc_name, CKG_Error* err) {
            ckg_assert(dll);

            void* proc = (void*)GetProcAddress(dll, proc_name);
            if (!proc) {
                ckg_error_safe_set(err, CKG_ERROR_IO_RESOURCE_NOT_FOUND);
                return NULLPTR;
            }

            return proc;
        }

        CKG_DLL MACRO_ckg_os_free_dll(CKG_DLL dll) {
            FreeLibrary(dll);
            return NULLPTR;
        }
    #else
        CKG_DLL ckg_io_load_dll(char* dll_name, CKG_Error* err) {
            void* library = dlopen(dll_name, RTLD_LAZY);
            if (!library) {
                ckg_error_safe_set(err, CKG_ERROR_IO_RESOURCE_NOT_FOUND);
                return NULLPTR;
            }

            return library;
        }

        void* ckg_os_get_proc_address(CKG_DLL dll, char* proc_name, CKG_Error* err) {
            void* proc = dlsym(dll, proc_name);
            if (!proc) {
                ckg_error_safe_set(err, CKG_ERROR_IO_RESOURCE_NOT_FOUND);
                return NULLPTR;
            }

            return proc;
        }

        CKG_DLL MACRO_ckg_os_free_dll(CKG_DLL dll) {
            dlclose(dll);
            return NULLPTR;
        }
    #endif
#endif