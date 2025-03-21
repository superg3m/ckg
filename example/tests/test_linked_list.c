#include "../../ckg.h"

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