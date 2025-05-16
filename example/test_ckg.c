
#include "../ckg.h"
#include "./tests/test_functions.c"

void* custom_alloc_callback(CKG_Allocator* allocator, size_t allocation_size) {
	CKG_Arena* arena = (CKG_Arena*)allocator->ctx;
	return ckg_arena_push_custom(arena, allocation_size);
}

void custom_free_callback(CKG_Allocator* allocator, void* data) {
	(void)allocator; 
	(void)data;
	return;
}

#define TOTAL_MEMORY_SIZE KiloBytes(30)

int main() {
	u8 program_stack_memory[TOTAL_MEMORY_SIZE] = {0};
	CKG_Arena arena = ckg_arena_create_fixed(program_stack_memory, TOTAL_MEMORY_SIZE, true);
	ckg_bind_custom_allocator(custom_alloc_callback, custom_free_callback, &arena);

	ckg_arena_temp(&arena, {
		test_ckg_memory_operations();
		test_ckg_arena_operations();
		test_ckg_str_operations();
		test_ckg_vector_operations();
		test_ckg_ring_buffer_overwrite_behavior();
	});
	
	test_serialization();
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
	CKG_LOG_SUCCESS("After ${third} bit set: %d\n", number_to_endian_swap);

	ckg_assert(GET_BIT(number_to_endian_swap, 0));

	for (char i = 0; i < 26; i++) {
		char c = i + 'a';
		ckg_assert_msg(ckg_char_is_alpha(c), "Character: %c\n", c);

		c = i + 'A';
		ckg_assert_msg(ckg_char_is_alpha(c), "Character: %c\n", c);
	}
	
	CKG_StringView* split_strings = ckg_sv_split(CKG_LIT_ARG("They said it couldn't be done. They tried to recite the dark magics to me! THEY DON'T KNOW I WAS THERE WHEN THEY WERE WRITTEN!"), CKG_LIT_ARG(" "));
	for (u32 i = 0; i < ckg_vector_count(split_strings); i++) {
		CKG_StringView line = split_strings[i];
		CKG_LOG_SUCCESS("str #%d | %.*s\n", i, line.length, line.data);
	}

	ckg_vector_free(split_strings);

	CKG_LOG_DEBUG("JUST MAKING SURE THIS IS GOOD!\n");

	CKG_StringView str_between_test = ckg_sv_between_delimiters(CKG_LIT_ARG("WOW - ${Hello!}"), CKG_LIT_ARG("${"), CKG_LIT_ARG("}"));
	CKG_LOG_DEBUG("String_Between: %.*s | %d\n", str_between_test.length, str_between_test.data, (int)str_between_test.length);

	CKG_LOG_WARN("================================ THIS WORKS ALL THE WAY I THINK! CKG END ================================\n");

	typedef struct Person {
		char* name;
		int age;
	} Person;

	CKG_HashMap(char*, Person) person_map = NULLPTR;

	Person p1;
	p1.name = "john";
	p1.age = 41;

	char* test = "dsfsdf";
	u64 h = siphash24(test, sizeof(char*));

	ckg_hashmap_put_key_ptr(person_map, "dsfsdf", p1);
	Person p2 = ckg_hashmap_get_key_ptr(person_map, "dsfsdf");
	printf("%s\n", p2.name);

	/// 
	/// ckg_hashmap_insert(person_map, "stick_bug", p1);
	/// Person p2 = ckg_hashmap_get(person_map, "stick_bug");

	int x = (1 + 2, 3 + 4);  // x is 7


	ckg_arena_free(&arena);
	return 0;
}