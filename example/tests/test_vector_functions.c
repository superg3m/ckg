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
	return;
}