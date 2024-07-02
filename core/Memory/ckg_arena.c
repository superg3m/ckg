#include "../ckg_arena.h"
#include "../../core/ckg_memory.h"
#include "../../core/ckg_assert.h"

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