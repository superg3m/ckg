#pragma once

#include "../ckg_types.h"

//========================== Begin Types ==========================
typedef struct CKG_Arena {
	const char* name;
    void* base_address;
    u64 capacity;
	u64 used;
	u32 flag;
} CKG_Arena;

typedef enum CKG_ArenaFlag {
  CKG_ARENA_FLAG_DEFAULT,
  CKG_ARENA_FLAG_CIRCULAR,
  CKG_ARENA_FLAG_VECTOR,
  CKG_ARENA_FLAG_COUNT
} CKG_ArenaFlag;
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
	CKG_Arena MACRO_ckg_arena_create(u32 allocation, const char* name, CKG_ArenaFlag flag);
	void* MACRO_ckg_arena_push(CKG_Arena* arena, u32 element_size);	
	
	void ckg_arena_free(CKG_Arena* arena);
	void ckg_arena_clear(CKG_Arena* arena);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
#define ckg_arena_create(allocation_size, name) MACRO_ckg_arena_create(allocation_size, name, CKG_ARENA_FLAG_DEFAULT)
#define ckg_arena_create_custom(allocation_size, name, flags) MACRO_ckg_arena_create(allocation_size, name, flags)

#define ckg_arena_push(arena, type) ((type*)MACRO_ckg_arena_push(arena, sizeof(type)))
#define ckg_arena_push_array(arena, type, element_count) ((type*)MACRO_ckg_arena_push(arena, sizeof(type) * element_count))
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++

#if defined(CKG_IMPL)
	#include "./ckg_memory.h"
	#include "../Assert/ckg_assert.h"

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
		arena.base_address = ckg_alloc(allocation_size != 0 ? allocation_size : ARENA_DEFAULT_ALLOCATION_SIZE);
		return arena;
	}

	void ckg_arena_free(CKG_Arena* arena) {
		ckg_assert(arena && arena->base_address);
		ckg_free(arena->base_address);
	}

	void ckg_arena_clear(CKG_Arena* arena) {
		ckg_assert(arena && arena->base_address);
		ckg_memory_zero(arena->base_address, arena->used);
		arena->used = 0;
	}

	void* MACRO_ckg_arena_push(CKG_Arena* arena, u32 element_size) {
		ckg_assert(arena && arena->base_address);

		if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_DEFAULT)) {
			ckg_assert((arena->used + element_size <= arena->capacity));
		} else if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_CIRCULAR)) {
			if ((arena->used + element_size > arena->capacity)) {
				arena->used = 0;
				ckg_assert((arena->used + element_size <= arena->capacity));
			}
		} else if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_VECTOR)) {
			if ((arena->used + element_size > arena->capacity)) {
				arena->capacity += element_size;
				arena->capacity *= 2;
				arena->base_address = ckg_realloc(arena->base_address, arena->capacity, arena->capacity * 2);
				ckg_assert(arena->base_address);
			}
		} else {
			ckg_assert(FALSE);
		}

		u8* ret = ((u8*)arena->base_address) + arena->used;
		arena->used += element_size;

		return ret;
	}
#endif // CKG_IMPL