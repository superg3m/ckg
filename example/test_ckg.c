
#include "../ckg.h"
#include "./tests/test_functions.c"

void* custom_alloc_callback(CKG_Allocator* allocator, size_t allocation_size) {
	CKG_Arena* arena = (CKG_Arena*)allocator->ctx;
	return ckg_arena_push_custom(arena, allocation_size);
}

void custom_free_callback(CKG_Allocator* allocator, void* data) {
	CKG_Arena* arena = (CKG_Arena*)allocator->ctx;
	ckg_arena_pop_data(arena, data);
	return;
}

#define TOTAL_MEMORY_SIZE KiloBytes(256)

int main() {
	u8 program_stack_memory[TOTAL_MEMORY_SIZE] = {0};
	CKG_Arena arena = ckg_arena_create_fixed(program_stack_memory, TOTAL_MEMORY_SIZE, true);
	ckg_bind_custom_allocator(custom_alloc_callback, custom_free_callback, &arena);

	test_ckg_memory_operations();
	test_ckg_arena_operations();
	test_ckg_str_operations();
	test_ckg_vector_operations();
	test_ckg_ring_buffer_overwrite_behavior();
	ckg_arena_temp(&arena, {
		ckg_hashmap_test();
	});

	test_serialization();

	test_ckg_stack_operations();
	linked_list_operations();
	
	for (char i = 0; i < 26; i++) {
		char c = i + 'a';
		ckg_assert_msg(ckg_char_is_alpha(c), "Character: %c\n", c);

		c = i + 'A';
		ckg_assert_msg(ckg_char_is_alpha(c), "Character: %c\n", c);
	}
	
	CKG_StringView* split_strings = ckg_sv_split(CKG_LIT_ARG("They said it couldn't be done. They tried to recite the dark magics to me! THEY DON'T KNOW I WAS THERE WHEN THEY WERE WRITTEN!"), CKG_LIT_ARG(" "));
	for (int i = 0; i < ckg_vector_count(split_strings); i++) {
		CKG_StringView line = split_strings[i];
		CKG_LOG_SUCCESS("str #%d | %.*s\n", i, line.length, line.data);
	}

	ckg_vector_free(split_strings);

	CKG_LOG_DEBUG("JUST MAKING SURE THIS IS GOOD!\n");

	CKG_StringView str_between_test = ckg_sv_between_delimiters(CKG_LIT_ARG("WOW - ${Hello!}"), CKG_LIT_ARG("${"), CKG_LIT_ARG("}"));
	CKG_LOG_DEBUG("String_Between: ${%.*s} | %d\n", str_between_test.length, str_between_test.data, (int)str_between_test.length);
	CKG_LOG_WARN("================================ THIS WORKS ALL THE WAY I THINK! CKG END ================================\n");

	CKG_LOG_SUCCESS("used/cap: %zu / %zu = %f\n", arena.used, arena.capacity, (float)arena.used / (float)arena.capacity);
	ckg_arena_free(&arena);
	return 0;
}