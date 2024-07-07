#pragma once

#include "../ckg_types.h"
//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
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
	void ckg_cstr_random(char *dest, size_t length);
	
	// Date: July 06, 2024
	// NOTE(Jovanni): These can be used for both ckg_cstring.h and ckg_string.h
	// ------------------------------------------------------------------------------------
	/**
	 * @brief Tests each charater in the string for equaility
	 * returns TRUE(1) if equal and FALSE(0) if not equal
	 * => if (ckg_str_equal("hi", "hi"))
	 * 
	 * 
	 * @param s1 
	 * @param s2 
	 * @return Boolean 
	 */
	Boolean ckg_str_equal(const char* s1, const char* s2);
	u32 ckg_str_length(const char* c_string);

	/**
	 * @brief clears a string_buffer to zero
	 * takes advantage of the face that we know the length
	 * @param string_buffer 
	 * @param string_buffer_size 
	 */
	void ckg_str_clear(char* string_buffer);

	/**
	 * @brief Allocates memory that caller must free! Start and end is inclusive
	 * 
	 * @param string_buffer 
	 * @param string_buffer_capacity 
	 * @param start_range 
	 * @param end_range 
	 * @return char* 
	 */
	char* ckg_substring(const char* string_buffer, u32 start_range, u32 end_range);
	Boolean ckg_str_contains(const char* string_buffer, const char* contains);
	u32 ckg_str_index_of(const char* string_buffer, const char* sub_string);
	u32 ckg_str_last_index_of(const char* string_buffer, const char* sub_string);
	char** ckg_str_split(const char* string_buffer, const char* delimitor);
	Boolean ckg_str_starts_with(const char* string_buffer, const char* starts_with);
	Boolean ckg_str_ends_with(const char* string_buffer, const char* ends_with);
	char* ckg_str_reverse(const char* string_buffer);
	// ------------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************