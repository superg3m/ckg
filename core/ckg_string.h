#pragma once

#include "./ckg_types.h"
//************************* Begin Functions *************************
	#ifdef __cplusplus
	extern "C" {
	#endif
		u32 ckg_cstr_length(const char* c_string);
		char* ckg_str_allocate(const char* s1);
		Boolean ckg_str_equal(const char* s1, const char* s2);


		/**
		 * @brief Requires the string buffer to be cleared to zero terminated
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 * @param source 
		 */
		void ckg_str_append(char* string_buffer, size_t string_buffer_capacity, const char* source);
		void ckg_str_append_char(char* string_buffer, size_t string_buffer_capacity, const char source);

		/**
		 * @brief Requires the string buffer to be cleared to zero terminated
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 * @param index 
		 */
		void ckg_str_insert(char* string_buffer, size_t string_buffer_capacity, const char* source, const u32 index);
		void ckg_str_insert_char(char* string_buffer, size_t string_buffer_capacity, const char source, const u32 index);

		/**
		 * @brief clears a string_buffer to zero
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 */
		void ckg_str_clear(char* string_buffer);

		
		/**
		 * @brief Requires the string buffer to be cleared to zero, modifies string_buffer
		 * Requires the string buffer to be cleared to zero terminated
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 */
		void ckg_str_copy(char* string_buffer, size_t string_buffer_capacity, const char* source);


		/**
		 * @brief generate a random string and copy it to the dest pointer
		 * 
		 * @param dest 
		 * @param length 
		 */
		void string_random(char *dest, size_t length);

		char* ckg_substring(const char* string_buffer, u32 start_range, u32 end_range);
		Boolean ckg_str_contains(const char* string_buffer, const char* contains);
		u32 ckg_str_index_of(const char* string_buffer, const char* sub_string);
		u32 ckg_str_last_index_of(const char* string_buffer, const char* sub_string);
		char** ckg_str_split(const char* string_buffer, const char* delimitor);
		Boolean ckg_str_starts_with(const char* string_buffer, const char* starts_with);
		Boolean ckg_str_ends_with(const char* string_buffer, const char* ends_with);
		char* ckg_str_reverse(const char* string_buffer);
	#ifdef __cplusplus
	}
	#endif
	//************************** End Functions **************************