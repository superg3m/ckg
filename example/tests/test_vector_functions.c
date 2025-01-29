#include "../../ckg.h"

void test_ckg_vector_operations() {
	int* int_vector = NULLPTR;

	for (int i = 0; i < 200; i++) {
		ckg_vector_push(int_vector, i);
	}

	for (int i = 0; i < (int)ckg_vector_count(int_vector); i++) {
		ckg_assert(int_vector[i] == i);
	}

	ckg_vector_push(int_vector, 4);

	CKG_LOG_SUCCESS("All vector tests passed!\n"); 

	ckg_vector_free(int_vector);
	return;
}

void test_ckg_stack_operations() {
	int* int_stack = NULLPTR;

	for (int i = 0; i < 200; i++) {
		ckg_stack_push(int_stack, i);
	}

	u64 stack_count = ckg_stack_count(int_stack);
	for (u64 i = 0; i < stack_count; i++) {
		int value2 = ckg_stack_pop(int_stack);
		ckg_assert(value2 == (199 - i));
	}

	if (ckg_stack_empty(int_stack)) {
		ckg_stack_free(int_stack);
	}

	CKG_LOG_SUCCESS("All vector tests passed!\n"); 
	return;
}