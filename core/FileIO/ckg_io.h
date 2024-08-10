#pragma once
/*===========================================================
 * File: ckg_file_system.h
 * Date: May 14, 2024
 * Creator: Jovanni Djonaj
===========================================================*/
#include <stdio.h>
#include "../Assert/ckg_assert.h"

typedef struct CKG_FileSystem {
	char* file_name;
	FILE* handle;
	u8* data;
	size_t file_size;
	Boolean reachedEOF;
} CKG_FileSystem;

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
	CKG_FileSystem ckg_file_system_create(char* file_name);
	void ckg_file_open(CKG_FileSystem* file_system);
	void ckg_file_close(CKG_FileSystem* file_system);
	size_t ckg_file_size(CKG_FileSystem* file_system);
	char* ckg_file_get_next_line(CKG_FileSystem* file_system);
	char ckg_file_get_next_char(CKG_FileSystem* file_system);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************
#if defined(CKG_IMPL)
	#include "../String/ckg_cstring.h"

	CKG_FileSystem ckg_file_system_create(char* file_name) {
		CKG_FileSystem file_system;
		file_system.handle = NULLPTR;
		file_system.reachedEOF = FALSE;
		file_system.file_name = file_name;
		file_system.data = NULLPTR;
		return file_system;
	}

	internal u8* read_file_data(FILE* handle, size_t file_size) {
		u8* buffer = ckg_alloc(file_size);
		ckg_assert_msg(fread(buffer, file_size, 1 , handle) != file_size, "Error reading file");
		rewind(handle);
		return buffer;
	}


	void ckg_file_open(CKG_FileSystem* file_system) {
		file_system->handle = fopen(file_system->file_name, "r");
		ckg_assert_msg(file_system->handle != NULLPTR, "FILE IS NULL, CHECK INITIAL FILE NAME\n");
		fseek(file_system->handle, 0L, SEEK_END);
		file_system->file_size = ftell(file_system->handle);
		rewind(file_system->handle);

		file_system->data = read_file_data(file_system->handle, file_system->file_size);
	}

	char* ckg_file_get_next_line(CKG_FileSystem* file_system) {
		// Date: July 06, 2024
		// TODO(Jovanni): this is temperary it needs to grow
		char line[2500]; 
		ckg_memory_zero(line, 2500);
		char c;
		do {
			c = fgetc(file_system->handle);
			if (c != '\n' && c != EOF) {
				ckg_cstr_append_char(line, 2500, c);
			}
			if (c == EOF) {
				file_system->reachedEOF = TRUE;
			}
		} while (c != '\n' && c != EOF);
		return line;
	}

	char ckg_file_get_next_char(CKG_FileSystem* file_system) {
		return fgetc(file_system->handle);
	}

	void ckg_file_close(CKG_FileSystem* file_system) { 
		fclose(file_system->handle); 
	}
#endif // CKG_IMPL