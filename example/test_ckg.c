
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

void linked_list_operations() {
	CKG_LinkedList* linked_list = ckg_linked_list_create(char*, TRUE);
	CKG_Node* address = ckg_linked_list_insert(linked_list, 0, (void*)"hello");
	ckg_linked_list_push(linked_list, (void*)"hello_sailor1!");
	ckg_linked_list_push(linked_list, (void*)"hello_sailor2!");
	ckg_linked_list_push(linked_list, (void*)"hello_sailor3!");
	ckg_linked_list_push(linked_list, (void*)"hello_sailor4!");
	char* test_str = (char*)ckg_linked_list_remove(linked_list, ckg_linked_list_node_to_index(linked_list, address)).data;
	CKG_LOG_DEBUG("list value: %s\n", test_str);
	test_str = (char*)ckg_linked_list_pop(linked_list).data;
	CKG_LOG_DEBUG("list value: %s\n", test_str);
	test_str = (char*)ckg_linked_list_pop(linked_list).data;
	CKG_LOG_DEBUG("list value: %s\n", test_str);
	test_str = (char*)ckg_linked_list_pop(linked_list).data;
	CKG_LOG_DEBUG("list value: %s\n", test_str);
	test_str = (char*)ckg_linked_list_pop(linked_list).data;
	CKG_LOG_DEBUG("list value: %s\n", test_str);
	ckg_linked_list_free(linked_list);

	CKG_LinkedList* linked_list_int = ckg_linked_list_create(u32, FALSE);	
	u32 value1[5] = {
		1,
		2,
		3,
		4,
		5,
	};

	ckg_linked_list_insert(linked_list_int, 0, &value1[0]);
	ckg_linked_list_push(linked_list_int, &value1[1]);
	ckg_linked_list_push(linked_list_int, &value1[2]);
	ckg_linked_list_push(linked_list_int, &value1[3]);
	ckg_linked_list_push(linked_list_int, &value1[4]);

	u32* test_u32 = (u32*)ckg_linked_list_remove(linked_list_int, 4).data;
	CKG_LOG_DEBUG("list value: %d\n", *test_u32);
	ckg_free(test_u32);

	test_u32 = (u32*)ckg_linked_list_pop(linked_list_int).data;
	CKG_LOG_DEBUG("list value: %d\n", *test_u32);
	ckg_free(test_u32);

	test_u32 = (u32*)ckg_linked_list_pop(linked_list_int).data;
	CKG_LOG_DEBUG("list value: %d\n", *test_u32);
	ckg_free(test_u32);

	test_u32 = (u32*)ckg_linked_list_pop(linked_list_int).data;
	CKG_LOG_DEBUG("list value: %d\n", *test_u32);
	ckg_free(test_u32);

	test_u32 = (u32*)ckg_linked_list_pop(linked_list_int).data;
	CKG_LOG_DEBUG("list value: %d\n", *test_u32);
	ckg_free(test_u32);
	ckg_linked_list_free(linked_list_int);
}

int main() {
	#if defined(PLATFORM_WINDOWS)
		ckg_bind_alloc_callback(win32_memory_alloc_callback);
		ckg_bind_free_callback(win32_memory_free_callback);
	#endif

	test_ckg_memory_operations();
	test_ckg_arena_operations();
	test_ckg_str_operations();
	test_ckg_vector_operations();

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

	CKG_LOG_WARN("================================ THIS WORKS ALL THE WAY I THINK! CKG END ================================\n");
	return 0;
}