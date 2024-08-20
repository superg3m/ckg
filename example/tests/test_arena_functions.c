#include "../../ckg.h"

void test_ckg_arena_operations() {
  CKG_Arena* arena = ckg_arena_create(1024, "Test Arena");

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
  ckg_arena_clear(arena);

  // Test arena_free
  ckg_arena_free(arena);

  const int arena_size_common = sizeof(int) * 16;

  // Test extendable arena
  CKG_Arena* extendable_arena = ckg_arena_create(arena_size_common, "Extendable Arena");
  for (u32 i = 0; i < 32; i++) {
    int* ptr = ckg_arena_push(extendable_arena, int);
    *ptr = i;
  }
  ckg_arena_free(extendable_arena);

  // Test circular arena
  CKG_Arena* circular_arena = ckg_arena_create_custom(arena_size_common, "Circular Arena", CKG_ARENA_FLAG_CIRCULAR, sizeof(int));
  for (u32 i = 0; i < 32; i++) {
    int* ptr = ckg_arena_push(circular_arena, int);
    *ptr = i;
  }

  int* last_ptr = ckg_arena_push(circular_arena, int);
  *last_ptr = 42;
  ckg_arena_free(circular_arena);

  // Test vector arena
  CKG_Arena* fixed_arena = ckg_arena_create_custom(arena_size_common, "Fixed Arena", CKG_ARENA_FLAG_FIXED, sizeof(int));
  for (u32 i = 0; i < 16; i++) {
    int* ptr = ckg_arena_push(fixed_arena, int);
    *ptr = i;
  }

  ckg_arena_free(fixed_arena);

  CKG_LOG_SUCCESS("All arena tests passed!\n");
  return;
}