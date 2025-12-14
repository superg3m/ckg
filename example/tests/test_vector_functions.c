#include "../../ckg.h"

void test_ckg_vector_operations() {
	int* int_vector = NULLPTR;

	for (int i = 0; i < 1000; i++) {
		ckg_vector_push(int_vector, i);
	}

	for (int i = 0; i < (int)ckg_vector_count(int_vector); i++) {
		ckg_assert(int_vector[i] == i);
	}

	ckg_vector_push(int_vector, 4);

	CKG_LOG_SUCCESS("All vector tests passed!\n"); 

	ckg_vector_free(int_vector);
}

void test_ckg_stack_operations() {
	int* int_stack = NULLPTR;

	for (int i = 0; i < 2040; i++) {
		ckg_stack_push(int_stack, i + 1);
	}

	u64 stack_count = ckg_stack_count(int_stack);
	for (u64 i = 0; i < stack_count; i++) {
		u64 value2 = ckg_stack_pop(int_stack);
		ckg_assert(value2 == (2040 - i));
	}

	ckg_assert(ckg_stack_empty(int_stack));
	
	ckg_stack_free(int_stack);
	CKG_LOG_SUCCESS("All vector tests passed!\n"); 
}

void test_ckg_ring_buffer_overwrite_behavior() {
    const int cap = 8;
    int* ring = (int*)ckg_ring_buffer_create(sizeof(int), cap);

    // Fill buffer with initial values 1..8
    for (int i = 0; i < cap; i++) {
        ckg_ring_buffer_enqueue(ring, i + 1);
    }

    // Overwrite all values with 9..16
    for (int i = 0; i < cap; i++) {
		if (ckg_ring_buffer_full(ring)) {
			int d = ckg_ring_buffer_dequeue(ring);
			ckg_assert(i + 1 == d);
		}

        ckg_ring_buffer_enqueue(ring, cap + i + 1); // 9..16
    }

    // Now buffer should contain only 9..16
    for (int i = 0; i < cap; i++) {
        int val = ckg_ring_buffer_dequeue(ring);
        ckg_assert(val == (cap + i + 1)); // Should match 9..16
    }

    ckg_assert(ckg_ring_buffer_empty(ring));
    ckg_ring_buffer_free(ring);

    CKG_LOG_SUCCESS("Ring buffer overwrite test passed!\n");
}