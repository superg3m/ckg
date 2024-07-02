#include "../ckg.h"
#include "./tests/test_functions.c"
#include <windows.h>

void* win32_memory_allocator_callback(size_t allocation_size) {
	void* ret = VirtualAlloc(0, allocation_size, MEM_COMMIT, PAGE_READWRITE);
	return ret;
}

void win32_memory_free_callback(void* data) {
	VirtualFree(data, 0, MEM_RELEASE);
}

void error_test3(int value) {
	ckg_assert(FALSE, "ERR TEST3 FAILED | value: %d", value);
}

void error_test2(int value) {
	ckg_errorable(error_test3(value), "idk 2");
}

void error_test1(int value) {
	ckg_errorable(error_test2(value), "idk 1");
}


int main() {
	ckg_memory_bind_allocator_callback(win32_memory_allocator_callback);
	ckg_memory_bind_free_callback(win32_memory_free_callback);

	test_ckg_memory_operations();
	test_ckg_arena_operations();
	test_ckg_string_operations();
	test_ckg_vector_operations();

	ckg_errorable(error_test1(5), "failed inital");

	return 0;
}