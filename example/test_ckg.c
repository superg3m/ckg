
#include "../ckg.h"

#include "./tests/test_functions.c"
#if defined(PLATFORM_WINDOWS)
	#include <windows.h>

	void* win32_memory_alloc_callback(size_t allocation_size) {
		void* ret = VirtualAlloc(0, allocation_size, MEM_COMMIT, PAGE_READWRITE);
		return ret;
	}

	void win32_memory_free_callback(void* data) {
		VirtualFree(data, 0, MEM_RELEASE);
	}
#endif

int main() {
	#if defined(PLATFORM_WINDOWS)
		ckg_bind_alloc_callback(win32_memory_alloc_callback);
		ckg_bind_free_callback(win32_memory_free_callback);
	#endif

	test_ckg_memory_operations();
	test_ckg_arena_operations();
	test_ckg_str_operations();
	test_ckg_vector_operations();
	test_ckg_stack_operations();

	linked_list_operations();

	u32 number_to_endian_swap = 2;
	U32_EndianSwap(&number_to_endian_swap);
	CKG_LOG_SUCCESS("EndianSwap: %d\n", number_to_endian_swap);

	U32_EndianSwap(&number_to_endian_swap);
	CKG_LOG_SUCCESS("EndianSwap: %d\n", number_to_endian_swap);

	CKG_LOG_SUCCESS("Before first bit set: %d\n", number_to_endian_swap);
	SET_BIT(number_to_endian_swap, 0);
	CKG_LOG_SUCCESS("After first bit set: %d\n", number_to_endian_swap);

	SET_BIT(number_to_endian_swap, 2);
	CKG_LOG_SUCCESS("After third bit set: %d\n", number_to_endian_swap);

	UNSET_BIT(number_to_endian_swap, 2);
	CKG_LOG_SUCCESS("After third bit set: %d\n", number_to_endian_swap);

	ckg_assert(GET_BIT(number_to_endian_swap, 0));

	for (char i = 0; i < 26; i++) {
		char c = i + 'a';
		ckg_assert_msg(ckg_char_is_alpha(c), "Character: %c\n", c);

		c = i + 'A';
		ckg_assert_msg(ckg_char_is_alpha(c), "Character: %c\n", c);
	}

	CKG_LOG_WARN("================================ THIS WORKS ALL THE WAY I THINK! CKG END ================================\n");
	return 0;
}