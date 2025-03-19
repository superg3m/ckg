#ifdef __cplusplus
    #define CKG_API extern "C"
#else 
    #define CKG_API
#endif 

#if defined(CKG_IMPL)
    #define CKG_IMPL_TYPES
    #define CKG_IMPL_LOGGER
    #define CKG_IMPL_ASSERT
    #define CKG_IMPL_MEMORY
    #define CKG_IMPL_ARENA
    #define CKG_IMPL_CSTRING
    #define CKG_IMPL_CHAR
    #define CKG_IMPL_COLLECTIONS
    #define CKG_IMPL_IO
#endif

#define CKG_INCLUDE_TYPES
#define CKG_INCLUDE_LOGGER
#define CKG_INCLUDE_ASSERT
#define CKG_INCLUDE_MEMORY
#define CKG_INCLUDE_ARENA
#define CKG_INCLUDE_STRING_VIEW
#define CKG_INCLUDE_CHAR
#define CKG_INCLUDE_COLLECTIONS
#define CKG_INCLUDE_IO

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
    typedef size_t   u64;

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
    #define GET_BIT(number, bit_to_check) ((number & (1 << bit_to_check)) >> bit_to_check)
    #define SET_BIT(number, bit_to_set) number |= (1 << bit_to_set);
    #define UNSET_BIT(number, bit_to_unset) number &= (~(1 << bit_to_unset));

    #define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

    #define PLATFORM_MAX_PATH 256

    #if defined(_WIN32)
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
    #elif defined(__GNUC__) || defined(__GNUG__)
        #define UNUSED_FUNCTION __attribute__((used))
    #elif defined(_MSC_VER)
        #define UNUSED_FUNCTION
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
        #define ckg_assert(expression)                                    \
            do {                                                          \
                if (!(expression)) {                                      \
                    ckg_stack_trace_dump();                               \
                    char msg[] = "Func: %s, File: %s:%d\n";               \
                    CKG_LOG_FATAL(msg, __func__, __FILE__, __LINE__);     \
                    CRASH;                                                \
                }                                                         \
            } while (FALSE)                                               \

        #define ckg_assert_msg(expression, message, ...)	              \
            do {                                                          \
                if (!(expression)) {                                      \
                    ckg_stack_trace_dump();                               \
                    char msg[] = "Func: %s, File: %s:%d\n";               \
                    CKG_LOG_FATAL(msg, __func__, __FILE__, __LINE__);     \
                    CKG_LOG_FATAL(message, ##__VA_ARGS__);                \
                    CRASH;                                                \
                }                                                         \
            } while (FALSE)                                               \

    #else
            #define ckg_assert(expression)
            #define ckg_assert_msg(expression, message, ...)
    #endif
#endif

#define CKG_ERRORS
#if defined(CKG_ERRORS)
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
        CKG_ERROR_IO_FILE_NOT_FOUND = (CKG_ERROR_IO_MASK | 0),
        CKG_ERROR_IO_COUNT = 1,

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

    char* CKG_ERROR_IO_STRINGS[CKG_ERROR_IO_COUNT] = {
        stringify(CKG_ERROR_IO_FILE_NOT_FOUND)
    };

    char* CKG_ERROR_ARGS_STRINGS[CKG_ERROR_ARGS_COUNT] = {
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

    CKG_API char* ckg_error_str(CKG_Error error_code) {
        int error_type = CKG_ERROR_TYPE_MASK & error_code;
        int error_index = (~CKG_ERROR_TYPE_MASK) & error_code;
            
        if (error_type == CKG_ERROR_IO_MASK) {
            return CKG_ERROR_IO_STRINGS[error_index];
        } else if (error_type == CKG_ERROR_ARGS_MASK) {
            return CKG_ERROR_ARGS_STRINGS[error_index];
        }
    }
#endif

typedef struct CKG_StringView {
    u8* data;
    u32 length;
} CKG_StringView;

#define CKG_SV_LIT(string_literal) (CKG_StringView){string_literal, sizeof(string_literal) - 1}
CKG_StringView ckg_sv_create(u8* data, u32 length);

#if defined(CKG_INCLUDE_MEMORY)
    typedef void*(CKG_Alloc_T)(CKG_Allocator* allocator, size_t allocation_size);
    typedef void(CKG_Free_T)(CKG_Allocator* allocator, void* data);
    typedef struct CKG_Allocator CKG_Allocator;

    CKG_API void* ckg_alloc(size_t allocation_size);
    CKG_API void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size);
    CKG_API void  ckg_free(void* data);

    /**
     * @brief Compares the bytes in the two buffers returns true if equal
     * 
     * @param buffer_one 
     * @param buffer_two 
     * @param b1_allocation_size 
     * @param b2_allocation_size 
     * @return bool 
     */
    CKG_API bool ckg_memory_compare(const void* buffer_one, const void* buffer_two, u64 b1_allocation_size, u64 b2_allocation_size);
    CKG_API void ckg_memory_copy(const void* source, void* destination, u64 source_size_in_bytes, u64 destination_size_in_bytes);
    CKG_API void ckg_memory_zero(void* data, u64 data_size_in_bytes);

    CKG_API void MACRO_ckg_memory_delete_index(void* data, u64 number_of_elements, u64 data_capacity, u64 element_size_in_bytes, u64 index);
    CKG_API void MACRO_ckg_memory_insert_index(void* data, u64 number_of_elements, u64 data_capacity, u64 element_size_in_bytes, u64 index);

    #define ckg_memory_fill(_buffer, _buffer_count, _fill_element) \
    {														       \
        for (int i = 0; i < (int)_buffer_count; i++) { 			   \
            _buffer[i] = _fill_element;                            \
        }                                                  	       \
    }                                                              \
    
    #define ckg_memory_delete_index(data, number_of_elements, data_capacity, index) MACRO_ckg_memory_delete_index(data, number_of_elements, data_capacity, sizeof(data[0]), index)
    #define ckg_memory_insert_index(data, number_of_elements, data_capacity, element, index) MACRO_ckg_memory_insert_index(data, number_of_elements, data_capacity, sizeof(data[0]), index); data[index] = element;
#endif

#if defined(CKG_INCLUDE_ARENA)
    #define ARENA_DEFAULT_ALLOCATION_SIZE MegaBytes(1)

    typedef enum CKG_ArenaFlag {
        CKG_ARENA_FLAG_FIXED = 0,
        CKG_ARENA_FLAG_CIRCULAR,
        CKG_ARENA_FLAG_COUNT,
    };

    typedef struct CKG_Arena CKG_Arena;
    
    /**
     * @brief 
     * 
     * @param memory 
     * @param allocation_size 
     * @param flag 
     * @param alignment
     * @return CKG_API* 
     */
    CKG_API CKG_Arena* ckg_arena_create_custom(void* memory, size_t allocation_size, CKG_ArenaFlag flag, u8 alignment);
    CKG_API void* ckg_arena_push_custom(CKG_Arena* arena, size_t element_size);	
    CKG_API void ckg_arena_zero(CKG_Arena* arena);
    CKG_API void ckg_arena_reset(CKG_Arena* arena);
    CKG_API void ckg_arena_pop_custom(CKG_Arena* arena, size_t bytes_to_pop);
    
    #define ckg_arena_create_fixed(memory, allocation_size) ckg_arena_create_custom(memory, allocation_size, CKG_ARENA_FLAG_FIXED, 0)
    #define ckg_arena_create_circular(memory, allocation_size) ckg_arena_create_custom(memory, allocation_size, CKG_ARENA_FLAG_CIRCULAR 0)
    #define ckg_arena_push(arena, type) ((type*)ckg_arena_push_custom(arena, sizeof(type)))
    #define ckg_arena_push_array(arena, type, element_count) ((type*)ckg_arena_push_custom(arena, sizeof(type) * element_count))
    #define ckg_arena_pop(arena, type) ckg_arena_pop_custom(arena, sizeof(type))
    #define ckg_arena_pop_array(arena, type) ckg_arena_pop_custom(arena, sizeof(type) * element_count)
#endif

//
// ===================================================== CKG_IMPL =====================================================
//

#if defined(CKG_IMPL_MEMORY)
    typedef struct CKG_Allocator {
        CKG_Alloc_T* allocate;
        CKG_Free_T* free;
        void* ctx;
    };

    internal CKG_Allocator allocator = {ckg_default_libc_malloc, ckg_default_libc_free};

    internal void* ckg_default_libc_malloc(CKG_Allocator* allocator, size_t allocation_size) {
        void* ret = malloc(allocator, allocation_size);
        ckg_memory_zero(ret, allocation_size);
        return ret;
    }

    internal void ckg_default_libc_free(CKG_Allocator* allocator, void* data) {
        free(allocator, data);
    }

    void* ckg_alloc(size_t allocation_size) {
        ckg_assert(allocation_size != 0);
        return allocator.allocate(allocation_size);
    }

    void ckg_free(void* data) {
        ckg_assert(data);

        allocator.free(data);
    }

    void* ckg_realloc(void* data, size_t old_allocation_size, size_t new_allocation_size) {
        ckg_assert(old_allocation_size != 0);
        ckg_assert(new_allocation_size != 0);

        void* ret = ckg_alloc(new_allocation_size);
        ckg_memory_copy(data, ret, old_allocation_size, new_allocation_size);
        ckg_free(data);
        return ret;
    }

    Boolean ckg_memory_compare(const void* buffer_one, const void* buffer_two, u64 buffer_one_size, u64 buffer_two_size) {
        ckg_assert(buffer_one);
        ckg_assert(buffer_two);

        if (buffer_one_size != buffer_two_size) {
            return FALSE;
        }

        u8* buffer_one_data = (u8*)buffer_one;
        u8* buffer_two_data = (u8*)buffer_two;
        for (u64 i = 0; i < buffer_one_size; i++) {
            if (buffer_one_data[i] != buffer_two_data[i]) {
                return FALSE;
            }
        }

        return TRUE;
    }

    void ckg_memory_copy(const void* source, void* destination, u64 source_size_in_bytes, u64 destination_size_in_bytes) {
        ckg_assert(source);
        ckg_assert(destination);
        ckg_assert(source_size_in_bytes <= destination_size_in_bytes);
        if (source_size_in_bytes == 0) {
            return;
        }

        u8* temp_data_copy = (u8*)ckg_alloc(source_size_in_bytes);
        for (u64 i = 0; i < source_size_in_bytes; i++) {
            temp_data_copy[i] = ((u8*)source)[i];
        }

        for (u64 i = 0; i < source_size_in_bytes; i++) {
            ((u8*)destination)[i] = temp_data_copy[i];
        }

        ckg_free(temp_data_copy);
    }

    void ckg_memory_zero(void* data, u64 data_size_in_bytes) {
        for (u64 i = 0; i < data_size_in_bytes; i++) {
            ((u8*)data)[i] = 0;
        }
    }

    // Date: September 12, 2024
    // TODO(Jovanni): MAKE SURE YOU TEST THIS. Its seems to maybe work?
    void MACRO_ckg_memory_delete_index(void* data, u64 number_of_elements, u64 data_capacity, u64 element_size_in_bytes, u64 index) {
        ckg_assert((s32)number_of_elements - 1 >= 0);
        ckg_assert(index < data_capacity);
        ckg_assert(index >= 0);

        u8* byte_data = (u8*)data;

        u64 total_size = element_size_in_bytes * data_capacity;
        u64 source_offset = (index + 1) * element_size_in_bytes;
        u64 dest_offset =  index * element_size_in_bytes;

        u64 payload_source_size = (number_of_elements * element_size_in_bytes) - source_offset;
        ckg_memory_copy(byte_data + source_offset, byte_data + dest_offset, payload_source_size, total_size - source_offset);
    }

    // Date: September 12, 2024
    // TODO(Jovanni): MAKE SURE YOU TEST THIS. Its seems to maybe work?
    void MACRO_ckg_memory_insert_index(void* data, u64 number_of_elements, u64 data_capacity, u64 element_size_in_bytes, u64 index) {
        ckg_assert((number_of_elements + 1) < data_capacity);
        ckg_assert(index < data_capacity - 1);
        ckg_assert(index >= 0);

        u8* byte_data = (u8*)data;

        u64 total_size = element_size_in_bytes * data_capacity;
        u64 source_offset = index * element_size_in_bytes;
        u64 dest_offset = (index + 1) * element_size_in_bytes;

        u64 payload_source_size = (number_of_elements * element_size_in_bytes) - source_offset;
        ckg_memory_copy(byte_data + source_offset, byte_data + dest_offset, payload_source_size, total_size - source_offset);
    }
#endif

#if defined(CKG_IMPL_ARENA) 
    typedef struct CKG_Arena {
        u8* base_address;
        size_t capacity;
        size_t used;
        u8 alignment;
        CKG_ArenaFlag flag;
    } CKG_Arena;

    internal bool ckg_is_set(CKG_Arena* arena, CKG_ArenaFlag flag) {
        return arena->flag == flag;
    }

    CKG_Arena* ckg_arena_create_custom(void* memory, size_t allocation_size, CKG_ArenaFlag flag, u8 alignment) {
        ckg_assert_msg(memory, "Memory can't be a null pointer!\n");
        ckg_assert_msg(allocation_size != 0, "Can't have a zero allocation size!\n");
        ckg_assert_msg(allocation_size >= sizeof(CKG_Arena), "Not enough allocation space for bootstraping the arena!\n");
        ckg_assert_msg(memory, "Memory can't be a null pointer!\n");
        ckg_assert_msg(flag >= 0 && flag <= (CKG_ARENA_FLAG_COUNT - 1), "Can't have a arena flag outside of the acceptable range!\n");

        CKG_Arena* arena = (CKG_Arena*)memory; // bootstrap
        arena->used = sizeof(CKG_Arena);
        arena->capacity = allocation_size;
        arena->base_address = (u8*)memory + arena->used;
        arena->alignment = alignment == 0 ? 8 : alignment;
        arena->flag = flag;

        return arena;
    }

    void ckg_arena_zero(CKG_Arena* arena) {
        ckg_assert_msg(arena, "Must have a valid arena!\n");

        ckg_memory_zero(arena->base_address, arena->capacity);
        arena->used = 0;
    }

    void ckg_arena_reset(CKG_Arena* arena) {
        ckg_assert_msg(arena, "Must have a valid arena!\n");

        arena->used = 0;
    }

    void* ckg_arena_push_custom(CKG_Arena* arena, size_t element_size) {
        ckg_assert_msg(arena, "Must have a valid arena!\n");
        ckg_assert_msg(element_size != 0, "Element size can't be zero!\n");

        if (ckg_is_set(arena, CKG_ARENA_FLAG_FIXED)) {
            ckg_assert((arena->used + element_size <= arena->capacity), "Ran out of arena memory!\n");
        } else if (ckg_is_set(arena, CKG_ARENA_FLAG_CIRCULAR)) {
            if ((arena->used + element_size > arena->capacity)) {
                arena->used = 0;
                ckg_assert((arena->used + element_size <= arena->capacity), "Element size exceeds circular arena allocation capacity!\n");
            }
        }

        u8* ret = arena->base_address + arena->used;
        arena->used += element_size;
        if ((arena->used & (arena->alignment - 1)) != 0) { // if first bit is set then its not aligned
            arena->used += (arena->alignment - (arena->used & (arena->alignment - 1)));
        }

        return ret;
    }
#endif


/**
 * @brief returns null terminated file data 
 * 
 * @param file_name 
 * @param file_name_length [OPTIONAL]
 * @param file_size 
 * @param err
 * @return u8* 
 */
u8* ckg_io_read_file(char* file_name, u32 file_name_length, u32* file_size, CKG_Error* err);