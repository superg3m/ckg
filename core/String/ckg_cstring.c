#include "./ckg_cstring.h"

#include "../Memory/ckg_memory.h"
#include "../Assert/ckg_assert.h"

//************************* Begin Functions *************************
u32 ckg_cstr_length(const char* cstring) {
	ckg_assert(cstring);

	u32 length = 0;
	char* cursor = (char*)cstring;
	while(*cursor++ != '\0') {
		length++;
	}
	return length;
}

char* ckg_cstr_alloc(const char* s1) {
	char* ret = NULLPTR;
	ckg_assert(s1);

	u32 s1_length = ckg_cstr_length(s1);
	u32 s1_capacity = s1_length + 1;

	ret = ckg_alloc(s1_capacity);
	ckg_memory_copy(s1, ret, s1_capacity, s1_capacity);
	
	return ret;
}

Boolean ckg_cstr_equal(const char* s1, const char* s2) {
	ckg_assert(s1);
	ckg_assert(s2);

	u32 s1_length = ckg_cstr_length(s1);
	u32 s2_length = ckg_cstr_length(s2);

	return ckg_memory_compare(s1, s2, s1_length, s2_length);
}

void ckg_cstr_insert(char* string_buffer, size_t string_buffer_capacity, const char* to_insert, const u32 index) {
	ckg_assert(string_buffer);
	ckg_assert(to_insert);

	const u32 string_buffer_length = ckg_cstr_length(string_buffer);
	const u32 to_insert_length = ckg_cstr_length(to_insert);

	const u32 new_length = string_buffer_length + to_insert_length;

	ckg_assert(index >= 0 && index <= string_buffer_length);
	ckg_assert_msg(new_length < string_buffer_capacity, "string_insert: string_buffer_capacity is %lld but new valid cstring length is %d + %d + 1(null_term)= %d\n", string_buffer_capacity, string_buffer_length, to_insert_length, new_length + 1);
	u8* move_source_ptr = string_buffer + index;
	u8* move_dest_ptr = move_source_ptr + to_insert_length;

	ckg_memory_move(move_source_ptr, move_dest_ptr, string_buffer_length - index);
	
	u8* copy_dest_ptr = string_buffer + index;
	ckg_memory_copy(to_insert, copy_dest_ptr, to_insert_length, string_buffer_capacity);
}

void ckg_cstr_insert_char(char* string_buffer, size_t string_buffer_capacity, const char to_insert, const u32 index) {
	ckg_assert(string_buffer);
	ckg_assert(to_insert);

	u32 string_buffer_length = ckg_cstr_length(string_buffer);
	u32 source_length = 1;

	ckg_assert(index >= 0 && index <= string_buffer_length);
	Boolean expression = string_buffer_length + source_length < string_buffer_capacity;
	ckg_assert_msg(expression, "ckg_cstr_insert_char: string_buffer overflow new_capacity_required: %d >= current_capacity: %lld\n",  string_buffer_length + source_length, string_buffer_capacity);

	char* source_ptr = string_buffer + index;
	size_t data_payload_size = ckg_cstr_length(source_ptr);

	ckg_memory_move(source_ptr, source_ptr + 1, string_buffer_length - index);
	string_buffer[index] = to_insert;
}

void ckg_cstr_append(char* string_buffer, size_t string_buffer_capacity, const char* to_append) {
	u32 string_buffer_length = ckg_cstr_length(string_buffer);
	ckg_cstr_insert(string_buffer, string_buffer_capacity, to_append, string_buffer_length);
}

void ckg_cstr_append_char(char* string_buffer, size_t string_buffer_capacity, const char to_append) {
	u32 string_buffer_length = ckg_cstr_length(string_buffer);
	ckg_cstr_insert_char(string_buffer, string_buffer_capacity, to_append, string_buffer_length);
}

void ckg_cstr_clear(char* string_buffer) {
	ckg_assert(string_buffer);

	size_t string_buffer_length = ckg_cstr_length(string_buffer); 
	ckg_memory_zero(string_buffer, string_buffer_length);
}

void ckg_cstr_copy(char* string_buffer, size_t string_buffer_capacity, const char* to_copy) {
	ckg_assert(to_copy);
	ckg_assert(string_buffer);

	u32 source_length = ckg_cstr_length(to_copy);
	ckg_cstr_clear(string_buffer);

	ckg_memory_copy(to_copy, string_buffer, source_length + 1, string_buffer_capacity);
}

void ckg_cstr_random(char *dest, size_t length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        u64 index = rand() % (sizeof(charset) - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

char* ckg_substring(const char* string_buffer, u32 start, u32 end) {
	ckg_assert(string_buffer);
	size_t string_buffer_length = ckg_cstr_length(string_buffer); 


	Boolean start_check = start >= 0 && start <= string_buffer_length - 1;
	Boolean end_check = end >= 0 && end <= string_buffer_length - 1;

	ckg_assert_msg(start_check, "ckg_substring: Start range is outside expected range: [%d - %lld] got: %d", 0, string_buffer_length - 1, start);
	ckg_assert_msg(end_check, "ckg_substring: End range is outside expected range: [%d - %lld] got: %d", 0, string_buffer_length - 1, end);
	ckg_assert_msg(start <= end, "ckg_substring: Start range is greater than end range[start: %d > end: %d]", start, end);

	//char* str = "hello"
	//0 - 4 = hello\0 = 6
 	//0 - 0 = h\0 = 2
	//0 - 1 = he\0 = 3
	//1 - 4 = ello\0 = 5

	size_t allocation_size = (end - start) + 2;
	char* ret_sub_string = ckg_alloc(allocation_size);

	u32 counter = 0;
	for (int i = start; i <= end; i++) {
		ret_sub_string[counter++] = string_buffer[i];
	}

	return ret_sub_string;
}

Boolean ckg_cstr_contains(const char* string_buffer, const char* contains) {
	ckg_assert(string_buffer);
	ckg_assert(contains);

	size_t string_buffer_length = ckg_cstr_length(string_buffer); 
	size_t contains_length = ckg_cstr_length(contains);

	if (string_buffer_length == 0 && contains_length == 0) {
		return TRUE;
	} else if (contains_length == 0) {
		return FALSE;
	} else if (string_buffer_length == 0) {
		return FALSE;
	}

	if (contains_length > string_buffer_length) {
		return FALSE;
	}

	// "\0" = 0
	// "a\0" = 0
	// "fss\0" = 2
	
	Boolean contains_substring = FALSE;
	for (int i = 0; !contains_substring && (i <= string_buffer_length - contains_length); i++) {
		if (string_buffer[i] != contains[0]) {
			continue;
		}

		u32 end_index = (i + (contains_length - 1));
		if (end_index > string_buffer_length) {
			break;
		}

		char* temp_string = ckg_substring(string_buffer, i, end_index);
		if (ckg_cstr_equal(temp_string, contains)) {
			contains_substring = TRUE;
		}
		ckg_free(temp_string);
	}

	return contains_substring;
}

u32 ckg_cstr_index_of(const char* string_buffer, const char* sub_string) {
	ckg_assert(string_buffer);
	ckg_assert(sub_string);
	
	size_t string_buffer_length = ckg_cstr_length(string_buffer); 
	size_t contains_length = ckg_cstr_length(sub_string);

	if (string_buffer_length == 0 && contains_length == 0) {
		return 0;
	} else if (contains_length == 0) {
		return -1;
	} else if (string_buffer_length == 0) {
		return -1;
	}

	if (contains_length > string_buffer_length) {
		return -1;
	}
	
	u32 ret_index = -1;
	for (int i = 0; (ret_index == -1) && (i <= string_buffer_length - contains_length); i++) {
		if (string_buffer[i] != sub_string[0]) {
			continue;
		}

		u32 end_index = (i + (contains_length - 1));
		if (end_index > string_buffer_length) {
			break;
		}

		char* temp_string = ckg_substring(string_buffer, i, end_index);
		if (ckg_cstr_equal(temp_string, sub_string)) {
			ret_index = i;
		}
		ckg_free(temp_string);
	}

	return ret_index;
}

u32 ckg_cstr_last_index_of(const char* string_buffer, const char* sub_string) {
	ckg_assert(string_buffer);
	ckg_assert(sub_string);
	
	size_t string_buffer_length = ckg_cstr_length(string_buffer); 
	size_t contains_length = ckg_cstr_length(sub_string);

	if (string_buffer_length == 0 && contains_length == 0) {
		return 0;
	} else if (contains_length == 0) {
		return -1;
	} else if (string_buffer_length == 0) {
		return -1;
	}

	if (contains_length > string_buffer_length) {
		return -1;
	}
	
	u32 ret_index = -1;
	for (int i = 0; i <= string_buffer_length - contains_length; i++) {
		if (string_buffer[i] != sub_string[0]) {
			continue;
		}

		u32 end_index = (i + (contains_length - 1));
		if (end_index > string_buffer_length) {
			break;
		}

		char* temp_string = ckg_substring(string_buffer, i, end_index);
		if (ckg_cstr_equal(temp_string, sub_string)) {
			ret_index = i;
		}
		ckg_free(temp_string);
	}

	return ret_index;
}

char** ckg_cstr_split(const char* string_buffer, const char* delimitor) {
	ckg_assert_msg(FALSE, "NOT IMPLMENTED YET");

	ckg_assert(string_buffer);
	ckg_assert(delimitor);

	size_t string_buffer_length = ckg_cstr_length(string_buffer); 
	size_t delmitor_length = ckg_cstr_length(delimitor); 

	if (delmitor_length <= 0) {
		return NULLPTR;
	}

	char** ret = ckg_alloc(sizeof(char*) * 100);

	char* temp_buffer = ckg_alloc(string_buffer_length + 1);

	u32 sub_string_counter = 0;
	for (int i = 0; i < string_buffer_length; i++) {
		ckg_cstr_append_char(temp_buffer, string_buffer_length + 1, string_buffer[i]);
		char* temp_substring = ckg_substring(string_buffer, i, delmitor_length - 1);
		if (temp_substring[i] != delimitor[0]) {
			continue;
		}

		if (ckg_cstr_equal(temp_substring, delimitor)) {
			ckg_cstr_copy(ret[sub_string_counter++], ckg_cstr_length(temp_buffer) + 1, temp_buffer);
			ckg_cstr_clear(temp_buffer);
		}
		ckg_free(temp_substring);
	}
	ckg_free(temp_buffer);


	
	char* temp_string = ckg_alloc(string_buffer_length);
	char* current_string = ckg_cstr_alloc(temp_string);

	return ret;
}

Boolean ckg_cstr_starts_with(const char* string_buffer, const char* starts_with) {
	ckg_assert(string_buffer);
	ckg_assert(starts_with);

	
	size_t string_buffer_length = ckg_cstr_length(string_buffer); 
	size_t starts_with_length = ckg_cstr_length(starts_with);

	if (string_buffer_length == 0 && starts_with_length == 0) {
		return TRUE;
	} else if (string_buffer[0] != starts_with[0] || string_buffer_length < starts_with_length) {
		return FALSE;
	}

	Boolean starts_with_substring = FALSE;
	char* temp_string = ckg_substring(string_buffer, 0, starts_with_length - 1);
	if (ckg_cstr_equal(temp_string, starts_with)) {
		starts_with_substring = TRUE;
	}
	ckg_free(temp_string);

	return starts_with_substring;
}

Boolean ckg_cstr_ends_with(const char* string_buffer, const char* ends_with) {
	ckg_assert(string_buffer);
	ckg_assert(ends_with);

	size_t string_buffer_length = ckg_cstr_length(string_buffer); 
	size_t ends_with_length = ckg_cstr_length(ends_with);

	if (string_buffer_length == 0 && ends_with_length == 0 || ends_with_length == 0) {
		return TRUE;
	} else if (string_buffer_length < ends_with_length) {
		return FALSE;
	}

	u32 start_index = (string_buffer_length - 1) - (ends_with_length - 1);
	if (string_buffer[start_index] != ends_with[0]) {
		return FALSE;
	}

	Boolean starts_with_substring = FALSE;
	char* temp_string = ckg_substring(string_buffer, start_index, string_buffer_length - 1);
	if (ckg_cstr_equal(temp_string, ends_with)) {
		starts_with_substring = TRUE;
	}
	ckg_free(temp_string);

	return starts_with_substring;
}

char* ckg_cstr_reverse(const char* string_buffer) {
	ckg_assert(string_buffer);

	u32 string_buffer_length = ckg_cstr_length(string_buffer);
	u32 string_buffer_guarenteed_capacity = string_buffer_length + 1;
	
	char* ret_reversed_string = ckg_alloc(string_buffer_guarenteed_capacity);
	for (int i = string_buffer_length - 1; i >= 0; i--) {
		ckg_cstr_append_char(ret_reversed_string, string_buffer_guarenteed_capacity, string_buffer[i]);
	}

	return ret_reversed_string;
}
//************************** End Functions **************************