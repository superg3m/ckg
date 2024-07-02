#include "../../ckg.h"

void test_ckg_arena_operations() {
  CKG_Arena arena = ckg_arena_create(1024, "Test Arena");

  // Test arena_push
  int* int_ptr = ckg_arena_push(&arena, int);
  *int_ptr = 5;
  ckg_assert_in_function(*int_ptr == 5, "Error: Arena push failed\n");

  // Test arena_push_array
  int* int_array = ckg_arena_push_array(&arena, int, 5);
  for (int i = 0; i < 5; i++) {
    int_array[i] = i;
  }
  for (int i = 0; i < 5; i++) {
    ckg_assert_in_function(int_array[i] == i, "Error: Arena push array failed\n");
  }

  // Test arena_clear
  ckg_arena_clear(&arena);
  ckg_assert_in_function(arena.used == 0, "Error: Arena clear failed\n");

  // Test arena_free
  ckg_arena_free(&arena);

  const int arena_size_common = sizeof(int) * 16;

    // Test default arena
  CKG_Arena default_arena = ckg_arena_create(arena_size_common, "Default Arena");
  for (int i = 0; i < 16; i++) {
    int* ptr = ckg_arena_push(&default_arena, int);
    *ptr = i;
  }
  ckg_arena_free(&default_arena);

  // Test circular arena
  CKG_Arena circular_arena = ckg_arena_create_custom(arena_size_common, "Circular Arena", CKG_ARENA_FLAG_CIRCULAR);
  for (int i = 0; i < 32; i++) {
    int* ptr = ckg_arena_push(&circular_arena, int);
    *ptr = i;
  }
  ckg_assert_in_function(circular_arena.used == arena_size_common, "Error: Circular arena grew unexpectedly\n");
  int* first_ptr = circular_arena.base_address;
  int* last_ptr = ckg_arena_push(&circular_arena, int);
  *last_ptr = 42;
  ckg_assert_in_function(*first_ptr == 42, "Error: Circular arena did not overwrite correctly\n");
  ckg_arena_free(&circular_arena);

  // Test vector arena
  CKG_Arena vector_arena = ckg_arena_create_custom(arena_size_common, "Vector Arena", CKG_ARENA_FLAG_VECTOR);
  for (int i = 0; i < 32; i++) {
    int* ptr = ckg_arena_push(&vector_arena, int);
    *ptr = i;
  }
  ckg_assert_in_function(vector_arena.used > arena_size_common, "Error: Vector arena did not grow\n");
  ckg_arena_free(&vector_arena);

  CKG_LOG_SUCCESS("All arena tests passed!\n");
  return;
}