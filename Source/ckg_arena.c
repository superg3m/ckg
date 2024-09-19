#include "../Include/ckg_arena.h"
#include "../Include/ckg_linked_list.h"
#include "../Include/ckg_memory.h"
#include "../Include/ckg_assert.h"

#define ARENA_DEFAULT_ALLOCATION_SIZE MegaBytes(1)

typedef struct CKG_ArenaPage {
	void* base_address;
	u64 capacity;
	u64 used;
} CKG_ArenaPage;

typedef struct CKG_Arena {
	const char* name;
	CKG_LinkedList* pages;
	CKG_ArenaFlag flag;
	u8 alignment;
} CKG_Arena;

Boolean ckg_CKG_ARENA_FLAG_is_set(CKG_Arena* arena, CKG_ArenaFlag flag) {
	return arena->flag == flag;
}

internal CKG_ArenaPage* ckg_arena_page_create(size_t allocation_size) {
	CKG_ArenaPage* ret = ckg_alloc(sizeof(CKG_ArenaPage));
	ret->used = 0;
	ret->capacity = allocation_size;
	ret->base_address = ckg_alloc(allocation_size != 0 ? allocation_size : ARENA_DEFAULT_ALLOCATION_SIZE);

	return ret;
}

CKG_Arena* MACRO_ckg_arena_create(size_t allocation_size, const char* name, CKG_ArenaFlag flag, u8 alignment) {
	CKG_Arena* arena = ckg_alloc(sizeof(CKG_Arena));
	arena->alignment = alignment == 0 ? 8 : alignment;
	arena->name = name;
	arena->flag = flag;
	arena->pages = ckg_linked_list_create(CKG_ArenaPage*, TRUE);
	CKG_ArenaPage* inital_page = ckg_arena_page_create(allocation_size);
	ckg_linked_list_push(arena->pages, inital_page);

	return arena;
}

CKG_Arena* MACRO_ckg_arena_free(CKG_Arena* arena) {
	ckg_assert(arena);

	for (u32 i = 0; i < arena->pages->count; i++) {
		CKG_ArenaPage* page = ckg_linked_list_remove(arena->pages, 0).data;
		ckg_assert(page->base_address);
		ckg_free(page->base_address);
		ckg_free(page);
	}
	ckg_linked_list_free(arena->pages);
	ckg_free(arena);

	return arena;
}

void ckg_arena_clear(CKG_Arena* arena) {
	ckg_assert(arena);

	for (u32 i = 0; i < arena->pages->count; i++) {
		CKG_ArenaPage* page = ckg_linked_list_get(arena->pages, i);
		ckg_assert(page->base_address);
		ckg_memory_zero(page->base_address, page->used);
		page->used = 0;
	}
}

void* MACRO_ckg_arena_push(CKG_Arena* arena, size_t element_size) {
	ckg_assert(arena);

	CKG_ArenaPage* last_page = ckg_linked_list_peek_tail(arena->pages);
	if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_FIXED)) { // single page assert if you run out of memory
		ckg_assert((last_page->used + element_size <= last_page->capacity));
	} else if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_CIRCULAR)) { // single page circle around if you run out of memory
		if ((last_page->used + element_size > last_page->capacity)) {
			last_page->used = 0;
			ckg_assert((last_page->used + element_size <= last_page->capacity));
		}
	} else if (ckg_CKG_ARENA_FLAG_is_set(arena, CKG_ARENA_FLAG_EXTENDABLE_PAGES)) {
		ckg_assert(last_page->base_address);
		if ((last_page->used + element_size > last_page->capacity)) {
			CKG_ArenaPage* next_page = ckg_arena_page_create((last_page->capacity + element_size) * 2);
			ckg_assert(next_page->base_address);
			ckg_linked_list_push(arena->pages, next_page);
		}
	} else {
		ckg_assert(FALSE);
	}

	last_page = ckg_linked_list_peek_tail(arena->pages); // tail might change

	u8* ret = ((u8*)last_page->base_address) + last_page->used;
	last_page->used += element_size;
	if ((last_page->used & (arena->alignment - 1)) != 0) { // if first bit is set then its not aligned
		last_page->used += (arena->alignment - (last_page->used & (arena->alignment - 1)));
	}

	return ret;
}