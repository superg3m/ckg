#include "../ckg.h"
#include "./tests/test_functions.c"
#include <windows.h>

void* win32_memory_alloc_callback(size_t allocation_size) {
	void* ret = VirtualAlloc(0, allocation_size, MEM_COMMIT, PAGE_READWRITE);
	return ret;
}

void win32_memory_free_callback(void* data) {
	VirtualFree(data, 0, MEM_RELEASE);
}

int main() {
	ckg_bind_alloc_callback(win32_memory_alloc_callback);
	ckg_bind_free_callback(win32_memory_free_callback);

	test_ckg_math();

	test_ckg_memory_operations();
	test_ckg_arena_operations();
	test_ckg_str_operations();
	test_ckg_vector_operations();

	return 0;
}