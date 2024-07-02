#pragma once

#include "./ckg_types.h"
//************************* Begin Functions *************************
	#ifdef __cplusplus
	extern "C" {
	#endif
		u32 cstring_length(const char* c_string);
		char* ckg_string_allocate(const char* s1);
		Boolean string_equal(const char* s1, const char* s2);


		/**
		 * @brief Requires the string buffer to be cleared to zero terminated
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 * @param source 
		 */
		void ckg_string_append(char* string_buffer, size_t string_buffer_capacity, const char* source);
		void ckg_string_append_char(char* string_buffer, size_t string_buffer_capacity, const char source);

		/**
		 * @brief Requires the string buffer to be cleared to zero terminated
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 * @param index 
		 */
		void ckg_string_insert(char* string_buffer, size_t string_buffer_capacity, const char* source, const u32 index);
		void ckg_string_insert_char(char* string_buffer, size_t string_buffer_capacity, const char source, const u32 index);

		/**
		 * @brief clears a string_buffer to zero
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 */
		void ckg_string_clear(char* string_buffer);

		
		/**
		 * @brief Requires the string buffer to be cleared to zero, modifies string_buffer
		 * Requires the string buffer to be cleared to zero terminated
		 * 
		 * @param string_buffer 
		 * @param string_buffer_size 
		 */
		void ckg_string_copy(char* string_buffer, size_t string_buffer_capacity, const char* source);


		/**
		 * @brief generate a random string and copy it to the dest pointer
		 * 
		 * @param dest 
		 * @param length 
		 */
		void string_random(char *dest, size_t length);

		char* string_substring(const char* string_buffer, u32 start_range, u32 end_range);
		Boolean string_contains(const char* string_buffer, const char* contains);
		Boolean string_starts_with(const char* string_buffer, const char* starts_with);
		Boolean string_ends_with(const char* string_buffer, const char* ends_with);
		char* string_reverse(const char* string_buffer);
		char* string_temp_reverse(const char* string_buffer);

	#ifdef __cplusplus
	}
	#endif
	//************************** End Functions **************************