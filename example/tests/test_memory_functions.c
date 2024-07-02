#include "../../ckg.h"

void test_ckg_memory_operations() {
	// Test ckg_memory_allocate
	int* ptr1 = ckg_memory_allocate(sizeof(int));
	ckg_assert_in_function(ptr1 != NULLPTR, "Error: Memory allocation failed\n");
	*ptr1 = 5;
	ckg_assert_in_function(*ptr1 == 5, "Error: Memory allocation failed\n");
	ckg_memory_free(ptr1);

	// Test ckg_memory_callocate
	int* ptr2 = ckg_memory_allocate(10 * sizeof(int));
	ckg_assert_in_function(ptr2 != NULLPTR, "Error: Memory allocation failed\n");
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
	ckg_assert_in_function(ptr4 != NULLPTR, "Error: Memory reallocation failed\n");
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

	CKG_LOG_SUCCESS("All memory tests passed!\n");
	return;
}