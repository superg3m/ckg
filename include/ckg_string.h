#pragma once
/*===========================================================
 * File: ckg_string.h
 * Date: May 18, 2024
 * Creator: Jovanni Djonaj
===========================================================*/
#include "./ckg_types.h"

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif

	u32 ckg_cstring_length(const char* c_string);
	Boolean ckg_cstring_compare(const char* s1, const char* s2);

	void ckg_string_append(char* string_buffer, u32 string_buffer_size, const char* source);
	void ckg_string_append_char(char* string_buffer, u32 string_buffer_size, const char source);

	/**
	 * @brief Requires the string buffer to be cleared to zero
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 * @param index 
	 */
	void ckg_string_insert(char* string_buffer, u32 string_buffer_size, const u32 index, const char* source);

	/**
	 * @brief Requires the string buffer to be cleared to zero
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 */
	void ckg_string_clear(char* string_buffer, u32 string_buffer_size);

	
	/**
	 * @brief Requires the string buffer to be cleared to zero
	 * 
	 * @param string_buffer 
	 * @param string_buffer_size 
	 */
	void ckg_string_copy(char* string_buffer, u32 string_buffer_size, const char* source);
	
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************




