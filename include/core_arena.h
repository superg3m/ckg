#pragma once
/*===========================================================
 * File: core_arena.h
 * Date: May 11, 2024
 * Creator: Jovanni Djonaj
===========================================================*/
#include "ckg.h"

//========================== Begin Types ==========================
typedef struct CKG_Arena CKG_Arena;

typedef enum ArenaFlag {
  ARENA_FLAG_DEFAULT,
  ARENA_FLAG_CIRCULAR,
  ARENA_FLAG_VECTOR,
  ARENA_FLAG_COUNT
} ArenaFlag;
//=========================== End Types ===========================

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
	CKG_Arena* MACRO_arena_create(u32 allocation, const char* name, ArenaFlag flag);
	void* MACRO_arena_push(CKG_Arena* arena, u32 element_size);	
	
	void arena_free(CKG_Arena* arena);
	void arena_clear(CKG_Arena* arena);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
#define arena_create(allocation_size, name) MACRO_arena_create(allocation_size, name, ARENA_FLAG_DEFAULT)
#define arena_create_custom(allocation_size, name, flags) MACRO_arena_create(allocation_size, name, flags)

#define arena_push(arena, type) ((type*)MACRO_arena_push(arena, sizeof(type)))
#define arena_push_array(arena, type, element_count) ((type*)MACRO_arena_push(arena, sizeof(type) * element_count))
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++







