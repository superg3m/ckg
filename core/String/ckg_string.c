#include "../ckg_string.h"
#include "../ckg_memory.h"
#include "../ckg_assert.h"

//************************* Begin Functions *************************
u32 cstring_length(const char* cstring) {
	u32 length = 0;
	char* cursor = (char*)cstring;
	while(*cursor++ != '\0') {
		length++;
	}
	return length;
}

char* ckg_string_allocate(const char* s1) {
	ckg_assert_in_function(s1, "string_equal: first argument is not valid | null\n");

	u32 s1_length = cstring_length(s1);
	u32 s1_capacity = s1_length + 1;

	char* ret = ckg_memory_allocate(s1_capacity);
	memory_copy(s1, ret, s1_capacity, s1_capacity);

	return ret;
}

Boolean string_equal(const char* s1, const char* s2) {
	ckg_assert_in_function(s1, "string_equal: first argument is not valid | null\n");
	ckg_assert_in_function(s2, "string_equal: second argument is not valid | null\n");

	u32 s1_length = cstring_length(s1);
	u32 s2_length = cstring_length(s2);

	return memory_byte_compare(s1, s2, s1_length, s2_length);
}

void ckg_string_insert(char* string_buffer, size_t string_buffer_capacity, const char* source, const u32 index) {
	ckg_assert_in_function(string_buffer, "string_insert: string_buffer is not valid | null\n");
	ckg_assert_in_function(source, "string_insert: source is not valid | null\n");

	u32 string_buffer_length = cstring_length(string_buffer);
	u32 source_length = cstring_length(source);

	ckg_assert_in_function(index >= 0 && index <= string_buffer_length, "Index out of bounds");
	ckg_assert_in_function(string_buffer_length + source_length < string_buffer_capacity, "string_insert: string_buffer_capacity is %lld but new valid cstring length is %d + %d = %d\n", string_buffer_capacity, string_buffer_length, source_length + 1, string_buffer_length + source_length + 1);

	// Date: May 18, 2024
	// TODO(Jovanni): Test this
	// for (int i = string_buffer_length; i > index; i--) {
		// string_buffer[(i - 1) + source_length] = string_buffer[i - 1];
		// string_buffer[i - 1] = 'x';
	// }

	memory_move(string_buffer,  string_buffer_capacity - string_buffer_length, source_length, string_buffer_length);
	
	u8* dest_ptr = memory_advance_new_ptr(string_buffer, index);
	// Date: May 18, 2024
	// NOTE(Jovanni): We don't want source_length + 1 because we don't want to copy the null terminator
	memory_copy(source, dest_ptr, source_length, string_buffer_capacity);
}

void ckg_string_insert_char(char* string_buffer, size_t string_buffer_capacity, const char source, const u32 index) {
	ckg_assert_in_function(string_buffer, "string_insert_char string_buffer is not valid | null\n");
	ckg_assert_in_function(source, "string_insert_char source is not valid | null\n");

	u32 string_buffer_length = cstring_length(string_buffer);
	u32 source_length = 1;

	Boolean expression = index >= 0 && string_buffer_length + source_length < string_buffer_capacity;
	ckg_assert_in_function(expression, "ckg_string_insert_char: string_buffer overflow new_capacity_required: %d >= current_capacity: %lld\n",  string_buffer_length + source_length, string_buffer_capacity);

	char* source_ptr = memory_advance_new_ptr(string_buffer, index);
	size_t data_payload_size = cstring_length(source_ptr);

	memory_move(source_ptr,  string_buffer_capacity - index, source_length, data_payload_size);
	string_buffer[index] = source;
}

void ckg_string_append(char* string_buffer, size_t string_buffer_capacity, const char* source) {
	u32 string_buffer_length = cstring_length(string_buffer);
	ckg_string_insert(string_buffer, string_buffer_capacity, source, string_buffer_length);
}

void ckg_string_append_char(char* string_buffer, size_t string_buffer_capacity, const char source) {
	u32 string_buffer_length = cstring_length(string_buffer);
	ckg_string_insert_char(string_buffer, string_buffer_capacity, source, string_buffer_length);
}

void ckg_string_clear(char* string_buffer) {
	ckg_assert_in_function(string_buffer, "ckg_string_clear: string_buffer is not valid | null\n");

	size_t string_buffer_length = cstring_length(string_buffer); 
	memory_zero(string_buffer, string_buffer_length);
}

void ckg_string_copy(char* string_buffer, size_t string_buffer_capacity, const char* source) {
	ckg_assert_in_function(string_buffer, "ckg_string_copy: string_buffer is not valid | null\n");
	ckg_assert_in_function(source, "ckg_string_copy: source is not valid | null\n");
	u32 source_length = cstring_length(source);
	ckg_string_clear(string_buffer);

	// Date: May 18, 2024
	// NOTE(Jovanni): We want to use source_length + 1 because we want to include the null terminator
	memory_copy(source, string_buffer, source_length + 1, string_buffer_capacity);
}

void string_random(char *dest, size_t length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        u64 index = rand() % (sizeof(charset) - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

/**
 * @brief Allocates memory that caller must free! Start and end is inclusive
 * 
 * @param string_buffer 
 * @param string_buffer_capacity 
 * @param start_range 
 * @param end_range 
 * @return char* 
 */
char* string_substring(const char* string_buffer, u32 start, u32 end) {
	ckg_assert_in_function(string_buffer, "string_substring: string_buffer is null!");
	size_t string_buffer_length = cstring_length(string_buffer); 


	Boolean start_check = start >= 0 && start <= string_buffer_length - 1;
	Boolean end_check = end >= 0 && end <= string_buffer_length - 1;

	ckg_assert_in_function(start_check, "string_substring: Start range is outside expected range: [%d - %lld] got: %d", 0, string_buffer_length - 1, start);
	ckg_assert_in_function(end_check, "string_substring: End range is outside expected range: [%d - %lld] got: %d", 0, string_buffer_length - 1, end);
	ckg_assert_in_function(start <= end, "string_substring: Start range is greater than end range[start: %d > end: %d]", start, end);

	//char* str = "hello"
	//0 - 4 = hello\0 = 6
 	//0 - 0 = h\0 = 2
	//0 - 1 = he\0 = 3
	//1 - 4 = ello\0 = 5

	size_t allocation_size = (end - start) + 2;
	char* ret_sub_string = ckg_memory_allocate(allocation_size);

	u32 counter = 0;
	for (int i = start; i <= end; i++) {
		ret_sub_string[counter++] = string_buffer[i];
	}

	return ret_sub_string;
}

Boolean string_contains(const char* string_buffer, const char* contains) {
	ckg_assert_in_function(string_buffer, "string_contains: string_buffer is null!");
	ckg_assert_in_function(contains, "string_contains: contains is null!");

	size_t string_buffer_length = cstring_length(string_buffer); 
	size_t contains_length = cstring_length(contains);

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
	for (int i = 0; !contains_substring && (i < string_buffer_length + 1); i++) {
		if (string_buffer[i] != contains[0]) {
			continue;
		}

		u32 end_index = (i + (contains_length - 1));
		if (end_index > string_buffer_length) {
			break;
		}

		char* temp_string = string_substring(string_buffer, i, end_index);
		if (string_equal(temp_string, contains)) {
			contains_substring = TRUE;
		}
		ckg_memory_free(temp_string);
	}

	return contains_substring;
}

Boolean string_starts_with(const char* string_buffer, const char* starts_with) {
	ckg_assert_in_function(string_buffer, "string_starts_with: string_buffer is null!");
	ckg_assert_in_function(starts_with, "string_starts_with: starts_with is null!");

	
	size_t string_buffer_length = cstring_length(string_buffer); 
	size_t starts_with_length = cstring_length(starts_with);

	if (string_buffer_length == 0 && starts_with_length == 0) {
		return TRUE;
	} else if (string_buffer[0] != starts_with[0] || string_buffer_length < starts_with_length) {
		return FALSE;
	}

	Boolean starts_with_substring = FALSE;
	char* temp_string = string_substring(string_buffer, 0, starts_with_length - 1);
	if (string_equal(temp_string, starts_with)) {
		starts_with_substring = TRUE;
	}
	ckg_memory_free(temp_string);

	return starts_with_substring;
}

Boolean string_ends_with(const char* string_buffer, const char* ends_with) {
	ckg_assert_in_function(string_buffer, "string_ends_with: string_buffer is null!");
	ckg_assert_in_function(ends_with, "string_ends_with: ends_with is null!");

	size_t string_buffer_length = cstring_length(string_buffer); 
	size_t ends_with_length = cstring_length(ends_with);

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
	char* temp_string = string_substring(string_buffer, start_index, string_buffer_length - 1);
	if (string_equal(temp_string, ends_with)) {
		starts_with_substring = TRUE;
	}
	ckg_memory_free(temp_string);

	return starts_with_substring;
}

char* string_reverse(const char* string_buffer) {
	ckg_assert_in_function(string_buffer, "string_ends_with: string_buffer is null!");

	u32 string_buffer_length = cstring_length(string_buffer);
	u32 string_buffer_guarenteed_capacity = string_buffer_length + 1;
	
	char* ret_reversed_string = ckg_memory_allocate(string_buffer_guarenteed_capacity);
	for (int i = string_buffer_length - 1; i >= 0; i--) {
		ckg_string_append_char(ret_reversed_string, string_buffer_guarenteed_capacity, string_buffer[i]);
	}

	return ret_reversed_string;
}
//************************** End Functions **************************