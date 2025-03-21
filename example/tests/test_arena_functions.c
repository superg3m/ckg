#include "../../ckg.h"

void test_ckg_arena_operations() {
  u8 function_memory[1024] = {0};
  CKG_Arena* arena = ckg_arena_create_fixed(function_memory, 1024);

  // Test arena_push
  int* int_ptr = ckg_arena_push(arena, int);
  *int_ptr = 5;
  ckg_assert(*int_ptr == 5);

  // Test arena_push_array
  int* int_array = ckg_arena_push_array(arena, int, 5);
  for (int i = 0; i < 5; i++) {
    int_array[i] = i;
  }
  for (int i = 0; i < 5; i++) {
    ckg_assert(int_array[i] == i);
  }

  // Test arena_clear
  ckg_arena_reset(arena);

  // Test arena_free
  ckg_arena_free(arena);

  const int arena_size_common = (int)ckg_arena_sizeof() + (sizeof(int) * 16);
  // Test circular arena
  CKG_Arena* circular_arena = ckg_arena_create_custom(function_memory, arena_size_common, CKG_ARENA_FLAG_CIRCULAR, sizeof(int));
  for (u32 i = 0; i < 32; i++) {
    int* ptr = ckg_arena_push(circular_arena, int);
    *ptr = i;
  }

  int* last_ptr = ckg_arena_push(circular_arena, int);
  *last_ptr = 42;
  ckg_arena_free(circular_arena);

  // Test vector arena
  CKG_Arena* fixed_arena = ckg_arena_create_custom(function_memory, arena_size_common, CKG_ARENA_FLAG_FIXED, sizeof(int));
  for (u32 i = 0; i < 16; i++) {
    int* ptr = ckg_arena_push(fixed_arena, int);
    *ptr = i;
  }

  ckg_arena_free(fixed_arena);

  CKG_LOG_SUCCESS("All arena tests passed!\n");
  return;
}