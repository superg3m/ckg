#pragma once

#include "./ckg_types.h"
//========================== Begin Types ==========================
typedef enum CKG_ArenaFlag {
  CKG_ARENA_FLAG_FIXED,
  CKG_ARENA_FLAG_CIRCULAR,
  CKG_ARENA_FLAG_EXTENDABLE_PAGES,
  CKG_ARENA_FLAG_COUNT
} CKG_ArenaFlag;

typedef struct CKG_Arena CKG_Arena;
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
	CKG_Arena* MACRO_ckg_arena_create(size_t allocation_size, const char* name, CKG_ArenaFlag flag, u8 alignment);
	void* MACRO_ckg_arena_push(CKG_Arena* arena, size_t element_size);	
	
	CKG_Arena* MACRO_ckg_arena_free(CKG_Arena* arena);
	void ckg_arena_clear(CKG_Arena* arena);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
#define ckg_arena_create(allocation_size, name) MACRO_ckg_arena_create(allocation_size, name, CKG_ARENA_FLAG_EXTENDABLE_PAGES, 0)
#define ckg_arena_create_custom(allocation_size, name, flags, alignment) MACRO_ckg_arena_create(allocation_size, name, flags, alignment)

#define ckg_arena_free(arena) arena = MACRO_ckg_arena_free(arena)

#define ckg_arena_push(arena, type) ((type*)MACRO_ckg_arena_push(arena, sizeof(type)))
#define ckg_arena_push_array(arena, type, element_count) ((type*)MACRO_ckg_arena_push(arena, sizeof(type) * element_count))
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++