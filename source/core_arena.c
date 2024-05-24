#include "../include/core_arena.h"
#include "../include/ckg.h"

// should register arena with memory

typedef struct CKG_Arena {
	const char* name;
    void* base_address;
    u64 capacity;
	u64 used;
	u32 flag;
} CKG_Arenas;

#define ARENA_DEFAULT_ALLOCATION_SIZE MegaBytes(1)

Boolean arena_flag_is_set(CKG_Arena* arena, ArenaFlag flag) {
    return arena->flag == flag;
}


CKG_Arena* MACRO_arena_create(u32 allocation_size, const char* name, ArenaFlag flag) {
    CKG_Arena* arena = ckg_memory_allocate(sizeof(CKG_Arena));
    arena->name = name;
    arena->flag = flag;
    arena->capacity = allocation_size;
    arena->used = 0;
    arena->base_address = ckg_memory_allocate(allocation_size != 0 ? allocation_size : ARENA_DEFAULT_ALLOCATION_SIZE);
    return arena;
}

void ckg_arena_free(CKG_Arena* arena) {
    ckg_assert_in_function(arena && arena->base_address, "arena_free: arena is null\n");
    ckg_memory_free(arena->base_address);
    ckg_memory_free(arena);
}

void arena_clear(CKG_Arena* arena) {
    ckg_assert_in_function(arena && arena->base_address, "arena_free: arena is null\n");
    memory_zero(arena->base_address, arena->used);
    arena->used = 0;
}

void* MACRO_arena_push(CKG_Arena* arena, u32 element_size) {
    // Date: May 11, 2024
    // TODO(Jovanni): For right now just assert if you don't have enough memory but later on make it grow.
    ckg_assert_in_function(arena && arena->base_address, "arena_push: arena is null\n");

    if (arena_flag_is_set(arena, ARENA_FLAG_DEFAULT)) {
        ckg_assert_in_function((arena->used + element_size < arena->capacity), "arena_push: can't push element ran out of memory\n");
        
    } else if (arena_flag_is_set(arena, ARENA_FLAG_CIRCULAR)) {
        arena->used = 0;
    } else if (arena_flag_is_set(arena, ARENA_FLAG_VECTOR)) {
        if ((arena->used + element_size >= arena->capacity)) {
            arena->capacity += element_size;
            arena->capacity *= 2;
            arena->base_address = ckg_memory_reallocate(arena->base_address, arena->capacity, arena->capacity * 2);
        }
    } else {
        ckg_assert_in_function(FALSE, "arean_push: invalid arena flag set");
    }

    u8* ret = memory_advance_new_ptr(arena->base_address, arena->used);

    return ret;
}
