#pragma once

#include "./ckg_types.h"
//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
	// Modifies String Buffer

	// Does not modify String Buffer

	/**
	 * @brief returns a string buffer with nullterm
	 * must free with ckg_free()
	 * @param s1 
	 * @return char* 
	 */
	char* ckg_cstr_alloc(const char* s1);

	/**
	 * @brief Requires the string buffer to be cleared to zero terminated
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 * @param source 
	 */
	void ckg_cstr_append(char* string_buffer, size_t string_buffer_capacity, const char* to_append);
	void ckg_cstr_append_char(char* string_buffer, size_t string_buffer_capacity, const char to_append);

	/**
	 * @brief Requires the string buffer to be cleared to zero terminated
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 * @param index 
	 */
	void ckg_cstr_insert(char* string_buffer, size_t string_buffer_capacity, const char* to_insert, const u32 index);
	void ckg_cstr_insert_char(char* string_buffer, size_t string_buffer_capacity, const char to_insert, const u32 index);
	
	/**
	 * @brief Requires the string buffer to be cleared to zero, modifies string_buffer
	 * 
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 */
	void ckg_cstr_copy(char* string_buffer, size_t string_buffer_capacity, const char* to_copy);

	/**
	 * @brief generate a random string and copy it to the dest pointer
	 * 
	 * @param dest 
	 * @param length 
	 */
	void ckg_cstr_random(char* dest, size_t length);
	
	/**
	 * @brief Tests each charater in the string for equaility
	 * returns TRUE(1) if equal and FALSE(0) if not equal
	 * => if (ckg_cstr_equal("hi", "hi"))
	 * 
	 * 
	 * @param s1 
	 * @param s2 
	 * @return Boolean 
	 */
	Boolean ckg_cstr_equal(const char* s1, const char* s2);
	u32 ckg_cstr_length(const char* c_string);
	void ckg_cstr_clear(char* string_buffer);
	// Inclusive start and end STR: SHOW | 0, 0 is: S | 0, 1 is: SH
	void ckg_substring(const char* string_buffer, char* returned_buffer, u32 start_range, u32 end_range);
	Boolean ckg_cstr_contains(const char* string_buffer, const char* contains);
	s32 ckg_cstr_index_of(const char* string_buffer, const char* sub_string);
	s32 ckg_cstr_last_index_of(const char* string_buffer, const char* sub_string);
	Boolean ckg_cstr_starts_with(const char* string_buffer, const char* starts_with);
	Boolean ckg_cstr_ends_with(const char* string_buffer, const char* ends_with);
	void ckg_cstr_reverse(const char* str, char* returned_reversed_string_buffer, size_t reversed_buffer_capacity);
	void ckg_cstr_int_to_cstr(char* string_buffer, size_t string_buffer_capacity, int number);
	// ------------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

#if defined(CKG_IMPL)
	#include "./ckg_memory.h"
	#include "./ckg_assert.h"

	u32 ckg_cstr_length(const char* cstring) {
		ckg_assert(cstring);

		u32 length = 0;
		char* cursor = (char*)cstring;
		while(*cursor++ != '\0') {
			length++;
		}
		return length;
	}

	Boolean ckg_cstr_equal(const char* s1, const char* s2) {
		ckg_assert(s1);
		ckg_assert(s2);

		u32 s1_length = ckg_cstr_length(s1);
		u32 s2_length = ckg_cstr_length(s2);

		return ckg_memory_compare(s1, s2, s1_length, s2_length);
	}

	void ckg_cstr_insert(char* str, size_t str_capacity, const char* to_insert, const u32 index) {
		ckg_assert(str);
		ckg_assert(to_insert);

		const u32 str_length = ckg_cstr_length(str);
		const u32 to_insert_length = ckg_cstr_length(to_insert);

		const u32 new_length = str_length + to_insert_length;

		ckg_assert(index >= 0 && index <= str_length);
		ckg_assert_msg(new_length < str_capacity, "string_insert: str_capacity is %lld but new valid cstring length is %d + %d + 1(null_term)= %d\n", str_capacity, str_length, to_insert_length, new_length + 1);
		u8* move_source_ptr = (u8*)(str + index);
		u8* move_dest_ptr = (u8*)(move_source_ptr + to_insert_length);

		ckg_memory_copy(move_source_ptr, move_dest_ptr, str_length - index, str_capacity - (index + to_insert_length));
		
		u8* copy_dest_ptr = (u8*)(str + index);
		ckg_memory_copy(to_insert, copy_dest_ptr, to_insert_length, str_capacity);
	}

	void ckg_cstr_insert_char(char* str, size_t str_capacity, const char to_insert, const u32 index) {
		ckg_assert(str);
		ckg_assert(to_insert);

		u32 str_length = ckg_cstr_length(str);
		u32 source_length = 1;

		ckg_assert(index >= 0 && index <= str_length);
		Boolean expression = str_length + source_length < str_capacity;
		ckg_assert_msg(expression, "ckg_cstr_insert_char: str overflow new_capacity_required: %d >= current_capacity: %lld\n",  str_length + source_length, str_capacity);

		char* source_ptr = str + index;

		ckg_memory_copy(source_ptr, source_ptr + 1, str_length - index, str_capacity - (index + 1));
		str[index] = to_insert;
	}

	void ckg_cstr_append(char* str, size_t str_capacity, const char* to_append) {
		u32 str_length = ckg_cstr_length(str);
		ckg_cstr_insert(str, str_capacity, to_append, str_length);
	}

	void ckg_cstr_append_char(char* str, size_t str_capacity, const char to_append) {
		u32 str_length = ckg_cstr_length(str);
		ckg_cstr_insert_char(str, str_capacity, to_append, str_length);
	}

	void ckg_cstr_clear(char* str) {
		ckg_assert(str);

		size_t str_length = ckg_cstr_length(str); 
		ckg_memory_zero(str, str_length);
	}

	void ckg_cstr_copy(char* str, size_t str_capacity, const char* to_copy) {
		ckg_assert(to_copy);
		ckg_assert(str);

		u32 source_length = ckg_cstr_length(to_copy);
		ckg_cstr_clear(str);

		ckg_memory_copy(to_copy, str, source_length + 1, str_capacity);
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

	void ckg_substring(const char* str, char* returned_buffer, u32 start, u32 end) {
		ckg_assert(str);
		ckg_assert(returned_buffer);
		size_t str_length = ckg_cstr_length(str); 

		Boolean start_check = (start >= 0) && (start <= str_length - 1);
		Boolean end_check = (end >= 0) && (end <= str_length - 1);

		ckg_assert_msg(start_check, "ckg_substring: Start range is outside expected range: [%d - %lld] got: %d", 0, str_length - 1, start);
		ckg_assert_msg(end_check, "ckg_substring: End range is outside expected range: [%d - %lld] got: %d", 0, str_length - 1, end);
		ckg_assert_msg(start <= end, "ckg_substring: Start range is greater than end range[start: %d > end: %d]", start, end);

		//char* str = "hello"
		//0 - 4 = hello\0 = 6
		//0 - 0 = h\0 = 2
		//0 - 1 = he\0 = 3
		//1 - 4 = ello\0 = 5

		u32 counter = 0;
		for (u32 i = start; i <= end; i++) {
			returned_buffer[counter++] = str[i];
		}
		returned_buffer[counter] = '\0'; 
	}

	Boolean ckg_cstr_contains(const char* str, const char* contains) {
		ckg_assert(str);
		ckg_assert(contains);

		size_t str_length = ckg_cstr_length(str); 
		size_t contains_length = ckg_cstr_length(contains);

		if (str_length == 0 && contains_length == 0) {
			return TRUE;
		} else if ((contains_length == 0) || (str_length == 0)) {
			return FALSE;
		}

		if (contains_length > str_length) {
			return FALSE;
		}

		// "\0" = 0
		// "a\0" = 0
		// "fss\0" = 2
		
		Boolean contains_substring = FALSE;
		for (u32 i = 0; !contains_substring && (i <= str_length - contains_length); i++) {
			if (str[i] != contains[0]) {
				continue;
			}

			u32 end_index = (u32)(i + (contains_length - 1));
			if (end_index > str_length) {
				break;
			}

			char* temp_string = ckg_alloc(contains_length + 1);
			ckg_substring(str, temp_string, i, end_index);
			if (ckg_cstr_equal(temp_string, contains)) {
				contains_substring = TRUE;
			}
			ckg_free(temp_string);
		}

		return contains_substring;
	}

	s32 ckg_cstr_index_of(const char* str, const char* sub_string) {
		ckg_assert(str);
		ckg_assert(sub_string);
		
		size_t str_length = ckg_cstr_length(str); 
		size_t contains_length = ckg_cstr_length(sub_string);

		if (str_length == 0 && contains_length == 0) {
			return 0;
		} else if (contains_length == 0) {
			return -1;
		} else if (str_length == 0) {
			return -1;
		}

		if (contains_length > str_length) {
			return -1;
		}
		
		s32 ret_index = -1;
		for (u32 i = 0; i <= str_length - contains_length; i++) {
			if (ret_index != -1) {
				break;
			}
			
			if (str[i] != sub_string[0]) {
				continue;
			}

			s32 end_index = (u32)(i + (contains_length - 1));
			if (end_index > str_length) {
				break;
			}

			char* temp_string = ckg_alloc((end_index - i) + 1);
			ckg_substring(str, temp_string, i, end_index);
			if (ckg_cstr_equal(temp_string, sub_string)) {
				ret_index = i;
			}
			ckg_free(temp_string);
		}

		return ret_index;
	}

	s32 ckg_cstr_last_index_of(const char* str, const char* sub_string) {
		ckg_assert(str);
		ckg_assert(sub_string);
		
		size_t str_length = ckg_cstr_length(str); 
		size_t contains_length = ckg_cstr_length(sub_string);

		if (str_length == 0 && contains_length == 0) {
			return 0;
		} else if (contains_length == 0) {
			return -1;
		} else if (str_length == 0) {
			return -1;
		}

		if (contains_length > str_length) {
			return -1;
		}
		
		s32 ret_index = -1;
		for (u32 i = 0; i <= str_length - contains_length; i++) {
			if (str[i] != sub_string[0]) {
				continue;
			}

			s32 end_index = (u32)(i + (contains_length - 1));
			if (end_index > str_length) {
				break;
			}

			char* temp_string = ckg_alloc((end_index - i) + 1);
			ckg_substring(str, temp_string, i, end_index);
			if (ckg_cstr_equal(temp_string, sub_string)) {
				ret_index = i;
			}
			ckg_free(temp_string);
		}

		return ret_index;
	}

	Boolean ckg_cstr_starts_with(const char* str, const char* starts_with) {
		ckg_assert(str);
		ckg_assert(starts_with);

		
		u32 str_length = ckg_cstr_length(str); 
		u32 starts_with_length = ckg_cstr_length(starts_with);

		if (str_length == 0 && starts_with_length == 0) {
			return TRUE;
		} else if (str[0] != starts_with[0] || str_length < starts_with_length) {
			return FALSE;
		}

		Boolean starts_with_substring = FALSE;
		char* temp_string = ckg_alloc(starts_with_length);
		ckg_substring(str, temp_string, (u32)0, starts_with_length - 1);
		if (ckg_cstr_equal(temp_string, starts_with)) {
			starts_with_substring = TRUE;
		}
		ckg_free(temp_string);

		return starts_with_substring;
	}

	Boolean ckg_cstr_ends_with(const char* str, const char* ends_with) {
		ckg_assert(str);
		ckg_assert(ends_with);

		u32 str_length = ckg_cstr_length(str); 
		u32 ends_with_length = ckg_cstr_length(ends_with);

		if ((str_length == 0) || (ends_with_length == 0)) {
			return TRUE;
		} else if (str_length < ends_with_length) {
			return FALSE;
		}

		u32 start_index = MAX((s32)str_length - 1, 0) - MAX((s32)ends_with_length - 1, 0);
		if (str[start_index] != ends_with[0]) {
			return FALSE;
		}

		Boolean starts_with_substring = FALSE;
		char* temp_string = ckg_alloc(str_length - start_index);
		ckg_substring(str, temp_string, start_index, str_length - 1);
		if (ckg_cstr_equal(temp_string, ends_with)) {
			starts_with_substring = TRUE;
		}
		ckg_free(temp_string);

		return starts_with_substring;
	}

	void ckg_cstr_reverse(const char* str, char* returned_reversed_string_buffer, size_t reversed_buffer_capacity) {
		ckg_assert(str);

		u32 str_length = ckg_cstr_length(str);
		ckg_assert(reversed_buffer_capacity > str_length);
		u32 str_guarenteed_capacity = str_length + 1;

		for (int i = str_length - 1; i >= 0; i--) {
			ckg_cstr_append_char(returned_reversed_string_buffer, str_guarenteed_capacity, str[i]);
		}
	}

	void ckg_cstr_int_to_cstr(char* string_buffer, size_t string_buffer_capacity, int number) {
		while (number != 0) {
			char c = '0' + (number % 10);
			ckg_cstr_insert_char(string_buffer, string_buffer_capacity, c, 0);
			number /= (int)10;
		}
	}
#endif // CKG_IMPL