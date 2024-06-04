#include "../include/ckg.h"
#include <windows.h>

void* win32_memory_allocator_callback(u32 allocation_size) {
	void* ret = VirtualAlloc(0, allocation_size, MEM_COMMIT, PAGE_READWRITE);
	return ret;
}

void win32_memory_free_callback(void* data) {
	VirtualFree(data, 0, MEM_RELEASE);
}

void test_ckg_memory_operations() {
	// Test ckg_memory_allocate
	int* ptr1 = ckg_memory_allocate(sizeof(int));
	ckg_assert_in_function(ptr1 != NULL, "Error: Memory allocation failed\n");
	*ptr1 = 5;
	ckg_assert_in_function(*ptr1 == 5, "Error: Memory allocation failed\n");
	ckg_memory_free(ptr1);

	// Test ckg_memory_callocate
	int* ptr2 = ckg_memory_allocate(10 * sizeof(int));
	ckg_assert_in_function(ptr2 != NULL, "Error: Memory allocation failed\n");
	for (int i = 0; i < 10; i++) {
		ptr2[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		ckg_assert_in_function(ptr2[i] == i, "Error: Memory allocation failed\n");
	}
	ckg_memory_free(ptr2);

	// Test ckg_memory_reallocate
	int* ptr3 = ckg_memory_allocate(sizeof(int));
	int* ptr4 = ckg_memory_reallocate(ptr3, 2 * sizeof(int), 4 * sizeof(int));
	ckg_assert_in_function(ptr4 != NULL, "Error: Memory reallocation failed\n");
	*ptr4 = 5;
	ckg_assert_in_function(*ptr4 == 5, "Error: Memory reallocation failed\n");
	ckg_memory_free(ptr4);

	// Test ckg_memory_copy
	int arr1[] = {1, 2, 3};
	int arr2[3];
	memory_copy(arr2, arr1, 3 * sizeof(int), 3 * sizeof(int));
	ckg_assert_in_function(arr1[0] == arr2[0] && arr1[1] == arr2[1] && arr1[2] == arr2[2], "Error: Memory copy failed\n");

	// Test ckg_memory_zero
	int arr3[3] = {1, 2, 3};
	memory_zero(arr3, 3 * sizeof(int));
	ckg_assert_in_function(arr3[0] == 0 && arr3[1] == 0 && arr3[2] == 0, "Error: Memory zero failed\n");

	// Test ckg_memory_compare
	int arr4[] = {1, 2, 3};
	int arr5[] = {1, 2, 3};
	int arr6[] = {4, 5, 6};
	ckg_assert_in_function(memory_byte_compare(arr4, arr5, 3 * sizeof(int), 3 * sizeof(int)) == TRUE, "Error: Memory compare failed\n");
	ckg_assert_in_function(!memory_byte_compare(arr4, arr6, 3 * sizeof(int), 3 * sizeof(int)), "Error: Memory compare failed\n");

	printf("All memory tests passed!\n");
	return;
}

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

  printf("All arena tests passed!\n");
  return;
}

#define str4_capacity 14
#define str5_capacity 14
#define str6_capacity 14
#define str7_capacity 14
#define str8_capacity 14

void test_ckg_string_operations() {
	CKG_Arena string_pool = ckg_arena_create_custom(6, "string pool", CKG_ARENA_FLAG_CIRCULAR);

	// Test cstring_length
	const int str1_size = 6;
	char* str1 = ckg_arena_push_array(&string_pool, char, 6);
	ckg_string_copy(str1, str1_size, "Hello");
	ckg_assert_in_function(string_compare(str1, "Hello"), "Error: Incorrect string comparison\n");

	char* str1_P = ckg_arena_push(&string_pool, char);
	str1_P[0] = 'f';
	ckg_assert_in_function(string_compare(str1, str1_P), "Error: Incorrect string comparison\n");


	char* str1_PT = ckg_arena_push(&string_pool, char);
	str1_PT[0] = 'M';
	ckg_assert_in_function(string_compare(str1, str1_P), "Error: Incorrect string comparison\n");
	ckg_assert_in_function(string_compare(str1_PT, "Mllo"), "Error: Incorrect string comparison\n");

	ckg_assert_in_function(cstring_length(str1) == 5, "Error: Incorrect string length\n");

	// Test string_compare
	char* str2 = "Hello";
	char* str3 = "World";
	ckg_assert_in_function(!string_compare(str1, str2), "Error: Incorrect string comparison\n");
	ckg_assert_in_function(string_compare(str2, str2), "Error: Incorrect string comparison\n");
	ckg_assert_in_function(!string_compare(str2, str3), "Error: Incorrect string comparison\n");

	// Test ckg_string_append
	char str4[str4_capacity];
	memory_zero(str4, str4_capacity);
	ckg_string_append(str4, str4_capacity, "Hello");
	ckg_string_append(str4, str4_capacity, " World!");
	ckg_assert_in_function(!string_compare(str4, "Hello World"), "Error: Incorrect string append\n");
	ckg_assert_in_function(string_compare(str4, "Hello World!"), "Error: Incorrect string append\n");
	ckg_assert_in_function(!string_compare(str4, "Goodbye World!"), "Error: Incorrect string append\n");
	ckg_assert_in_function(!string_compare(str4, ""), "Error: Incorrect string append\n");


	// Test ckg_string_append_char
	char str5[str5_capacity];
	memory_zero(str5, str5_capacity);
	ckg_string_append(str5, str5_capacity, "Hello");
	ckg_string_append_char(str5, str5_capacity, '!');
	ckg_assert_in_function(string_compare(str5, "Hello!"), "Error: Incorrect string append char\n");
	ckg_assert_in_function(!string_compare(str5, "Goodbye!"), "Error: Incorrect string append char\n");

	// Test ckg_string_insert
	char str6[str6_capacity];
	memory_zero(str6, str6_capacity);
	ckg_string_insert(str6, str6_capacity, 0, "Hello");
	ckg_string_insert(str6, str6_capacity, 5, " World");
	ckg_assert_in_function(string_compare(str6, "Hello World"), "Error: Incorrect string insert, left: %s | right: %s\n", str6, "Hello World");
	ckg_assert_in_function(!string_compare(str6, "Goodbye World"), "Error: Incorrect string insert, left: %s | right: %s\n", str6, "Goodbye World");

	ckg_string_insert(str6, str6_capacity, 2, "V");
	ckg_assert_in_function(string_compare(str6, "HeVllo World"), "Error: Incorrect string insert, left: %s | right: %s\n", str6, "HeVllo World");

	ckg_string_insert(str6, str6_capacity, cstring_length(str6), "!");
	ckg_assert_in_function(string_compare(str6, "HeVllo World!"), "Error: Incorrect string insert, left: %s | right: %s\n", str6, "HeVllo World!");


	// Test ckg_string_clear
	char str7[str7_capacity] = "Hello";
	ckg_string_clear(str7, str7_capacity);
	ckg_assert_in_function(string_compare("", ""), "Error: Incorrect string clear\n");
	ckg_assert_in_function(!string_compare("", "should fail?"), "Error: Incorrect string clear\n");

	// Test ckg_string_copy
	char str8[str8_capacity];
	memory_zero(str4, str8_capacity);
	ckg_string_copy(str8, str8_capacity, "Hello!");
	ckg_assert_in_function(string_compare(str8, "Hello!"), "Error: Incorrect string copy\n");
	ckg_assert_in_function(!string_compare(str8, "Hello"), "Error: Incorrect string copy\n");
	ckg_assert_in_function(!string_compare(str8, "Goodbye"), "Error: Incorrect string copy\n");

	printf("All string tests passed!\n"); 
	return;
}

void test_ckg_vector_operations() {
	int* int_vector = NULLPTR;

	for (int i = 0; i < 200; i++) {
		vector_push(int_vector, i);
	}

	for (int i = 0; i < vector_length(int_vector); i++) {
		ckg_assert_in_function(int_vector[i] == i, "VECTOR FAILED!\n");
	}

	vector_push(int_vector, 4);

	printf("All vector tests passed!\n"); 
	return;
}

int main() {
	test_ckg_memory_operations();
	test_ckg_arena_operations();
	test_ckg_string_operations();
	test_ckg_vector_operations();

	return 0;
}