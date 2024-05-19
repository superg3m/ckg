
/*===========================================================
 * File: ckg_string.c
 * Date: May 18, 2024
 * Creator: Jovanni Djonaj
===========================================================*/
#include "../include/ckg_string.h"
#include "../include/ckg_memory.h"
#include "../include/ckg_assert.h"


//========================== Begin Types ==========================
//=========================== End Types ===========================

//************************* Begin Functions *************************


u32 ckg_cstring_length(const char* cstring) {
	u32 length = 0;
    char* cursor = (char*)cstring;
    while(*cursor++ != '\0') {
        length++;
    }
    return length;
}

Boolean ckg_string_compare(const char* s1, const char* s2) {
	assert_in_function(s1, "string_compare first argument is not valid | null\n");
    assert_in_function(s2, "string_compare second argument is not valid | null\n");

	u32 s1_length = ckg_cstring_length(s1);
	u32 s2_length = ckg_cstring_length(s2);

	return memory_byte_compare(s1, s2, s1_length, s2_length);
}

void ckg_string_insert(char* string_buffer, u32 string_buffer_size, const u32 index, const char* source) {
	assert_in_function(string_buffer, "string_insert string_buffer is not valid | null\n");
	assert_in_function(source, "string_insert source is not valid | null\n");

	u32 string_buffer_length = ckg_cstring_length(string_buffer);
	u32 source_length = ckg_cstring_length(source);

	assert_in_function(index >= 0 && string_buffer_length + source_length < string_buffer_size, "string_insert string_buffer_size is %d but new valid cstring length is %d\n", string_buffer_size, string_buffer_length + source_length + 1);

	// Date: May 18, 2024
	// TODO(Jovanni): Test this
	for (int i = string_buffer_length; i > index; i--) {
		string_buffer[(i - 1) + source_length] = string_buffer[i - 1];
		string_buffer[i - 1] = 'x';
	}
	
	u8* dest_ptr = memory_advance_new_ptr(string_buffer, index);
	// Date: May 18, 2024
	// NOTE(Jovanni): We don't want source_length + 1 because we don't want to copy the null terminator
	memory_copy(source, dest_ptr, source_length, string_buffer_size);
}

void ckg_string_insert_char(char* string_buffer, u32 string_buffer_size, const u32 index, const char source) {
	assert_in_function(string_buffer, "string_insert_char string_buffer is not valid | null\n");
	assert_in_function(source, "string_insert_char source is not valid | null\n");

	u32 string_buffer_length = ckg_cstring_length(string_buffer);
	u32 source_length = 1;

    assert_in_function(index >= 0 && string_buffer_length + source_length < string_buffer_size, "string_compare second argument is not valid | null\n");

	// Date: May 18, 2024
	// TODO(Jovanni): Test this
	for (int i = string_buffer_length; i > index; i--) {
		string_buffer[(i - 1) + source_length] = string_buffer[(i - 1)];
	}

	string_buffer[index] = source;
}

void ckg_string_append(char* string_buffer, u32 string_buffer_size, const char* source) {
	u32 string_buffer_length = ckg_cstring_length(string_buffer);
	ckg_string_insert(string_buffer, string_buffer_size, string_buffer_length, source);
}

void ckg_string_append_char(char* string_buffer, u32 string_buffer_size, const char source) {
	u32 string_buffer_length = ckg_cstring_length(string_buffer);
	ckg_string_insert_char(string_buffer, string_buffer_size, string_buffer_length, source);
}

void ckg_string_clear(char* string_buffer, u32 string_buffer_size) {
	memory_zero(string_buffer, string_buffer_size);
}

void ckg_string_copy(char* string_buffer, u32 string_buffer_size, const char* source) {
	u32 source_length = ckg_cstring_length(source);

	// Date: May 18, 2024
	// NOTE(Jovanni): We want to use source_length + 1 because we need inclukde the null terminator
	memory_copy(source, string_buffer, source_length + 1, string_buffer_size);
}
//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++



