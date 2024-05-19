#include "../include/ckg_types.h"
#include "../include/ckg_assert.h"

#pragma region PLATFORM SERVICES
	#include "../include/ckg_platform_services.h"
	//========================== Begin Types ==========================
	//=========================== End Types ===========================

	//************************* Begin Functions *************************
	// DEFAULT IMPLEMENTATION
	#ifndef CUSTOM_PLATFORM_IMPL
		#ifdef PLATFORM_WINDOWS
			#include <windows.h>
			void* platform_allocate(unsigned long long  number_of_bytes) {
				return VirtualAlloc(NULL, number_of_bytes, MEM_COMMIT, PAGE_READWRITE);
			}

			/**
			 * @brief Keep in mind that free only need a pointer that is pointign the the right data
			 * to free so it doesn't matter if its a copy or not because the copy is pointing the he same data
			 * 
			 * @param data 
			 */
			void* MACRO_platform_free(void* data) {
				VirtualFree(data, 0, MEM_RELEASE); // This is really interesting
				data = NULLPTR;
				return data;
				// Date: May 08, 2024
				// TODO(Jovanni): Look into VirtualProtect() this allows you to change memory access to NO_ACCESS
				// can help find use after free bugs interesting concept
			}

			void platform_console_init() {
				AllocConsole();
				freopen("CONIN$", "r", stdin); 
				freopen("CONOUT$", "w", stdout); 
				freopen("CONOUT$", "w", stderr);

				HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);   
				SetConsoleDisplayMode(console_handle, CONSOLE_FULLSCREEN_MODE, 0);
			}

			void platform_console_shutdown() {
				FreeConsole();
			}

			void platform_console_write(const char* message, unsigned char color) {
				// Date: May 01, 2024
				// TODO(Jovanni): This code is very flaky I would suggest fixing it
				DWORD num_written_bytes = 0;
				unsigned long long message_size_in_bytes = ckg_cstring_length(message);

				HANDLE console_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
				char out_message[PLATFORM_CHARACTER_LIMIT];
				for (int i = 0; i < PLATFORM_CHARACTER_LIMIT; i++) { // Zeroing out the buffer
					out_message[i] = '\0';
				}

				int count = 0;
				int new_line_required = 0;
				Boolean is_fatal = (color == BACK_RED);
				while (count < message_size_in_bytes) {
					char c = message[count];
					if (c == '\n' && message[count + 1] == '\0') {
						new_line_required = 1;
						break;
					}
					out_message[count++] = c;
				}

				SetConsoleTextAttribute(console_output_handle, color);
				WriteConsoleA(console_output_handle, out_message, message_size_in_bytes, &num_written_bytes, NULL);
				SetConsoleTextAttribute(console_output_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				if (new_line_required == 1) {
					WriteConsoleA(console_output_handle, "\n", 1, &num_written_bytes, NULL);
				}
			}
		#elif PLATFORM_LINUX
			#define COLOR_RESET "\033[0"
			#define BLU "\033[34"
			#define GRN "\033[32"
			#define RED "\033[31"
			#define MAG "\033[35"
			#define WHT "\033[37"
			#define BLKB "\033[40"
			#define GRNB "\033[42"
			#define REDB "\033[41"

			int translate_color(unsigned char color) {
				switch (color) {
					case 0x0000: { // text color default clear.
						return 0;
					} break;

					case 0x0001: { // text color contains blue.
						return 1;
					} break;

					case 0x0002: { // text color contains green.
						return 2;
					} break;

					case 0x0004: { // text color contains red.
						return 3;
					} break;

					case (0x0001|0x0004): { // background color contains purple.
						return 4;
					} break;

					case (0x0001|0x0002|0x0004): { // background color contains red.
						return 5;
					} break;

					case 0x0010: { // background color contains blue.
						return 6;
					} break;

					case 0x0020: { // background color contains green.
						return 7;
					} break;

					case 0x0040: { // background color contains red.
						return 8;
					} break;
				}
			}

			void* _platform_allocate(size_t  number_of_bytes) {
				return malloc(number_of_bytes);
			}

			void MACRO_platform_free(size_t number_of_bytes, void** data) {
				free(*data);
			}
			
			// Date: April 13, 2024
			// TODO(Jovanni): Fix this to use linux's platfomr specific std console out
			void _platform_console_write(size_t message_size_in_bytes, const char* message, unsigned char color) {
				const char* color_strings[] = {COLOR_RESET, BLU, GRN, RED, MAG, WHT, BLKB, GRNB, REDB};
				printf("\033[%sm%s\033[0m", color_strings[translate_color(color)], message);
			}
		#elif PLATFORM_MACOS
		#endif
	#endif
	//************************** End Functions **************************
#pragma endregion

#pragma region MEMORY
	#include "../include/ckg_memory.h"
	#include "../include/ckg_assert.h"

	Boolean memory_byte_compare(const void* buffer_one, const void* buffer_two, u32 buffer_one_size, u32 buffer_two_size) {
		assert_in_function(buffer_one, "memory_byte_compare buffer_one IS NULL\n");
		assert_in_function(buffer_two, "memory_byte_compare buffer_two IS NULL\n");

		if (buffer_one_size != buffer_one_size) {
			return FALSE;
		}

		u8* buffer_one_data = (u8*)buffer_one;
		u8* buffer_two_data = (u8*)buffer_two;
		for (int i = 0; i < buffer_one_size; i++) {
			if (buffer_one_data[i] != buffer_two_data[i]) {
				return FALSE;
			}
		}

		return TRUE;
	}

	void memory_copy(const void* source, void* destination, u32 source_size, u32 destination_size) {
		assert_in_function(source, "MEMORY COPY SOURCE IS NULL\n");
		assert_in_function(destination, "MEMORY COPY SOURCE IS NULL\n");
		assert_in_function((source_size <= destination_size), "MEMORY COPY SOURCE IS TOO BIG FOR DESTINATION\n");

		for (int i = 0; i < source_size; i++) {
			((u8*)destination)[i] = ((u8*)source)[i];
		}
	}

	void memory_zero(void* data, u32 data_size_in_bytes) {
		for (int i = 0; i < data_size_in_bytes; i++) {
			((u8*)data)[i] = 0;
		}
	}

	void memory_set(u8* data, u32 data_size_in_bytes, u8 element) {
		for (int i = 0; i < data_size_in_bytes; i++) {
			((u8*)data)[i] = element;
		}
	}

	/**
	 * @brief O(n)
	 * 
	 * @param data 
	 * @param size_in_bytes 
	 * @param buffer_count 
	 * @param index 
	 */
	void memory_buffer_delete_index(const void* data, u32 size_in_bytes, u32 buffer_count, u32 index) {
		u32 size_of_element = size_in_bytes / buffer_count;

		u8* source_ptr = memory_advance_new_ptr(data, (index + 1) * size_of_element);
		u8* dest_ptr = memory_advance_new_ptr(data, index * size_of_element);

		u32 source_ptr_size = (buffer_count - (index + 1)) * size_of_element;
		u32 dest_ptr_size = (buffer_count - (index)) * size_of_element;
		memory_copy(source_ptr, dest_ptr, source_ptr_size, dest_ptr_size);
	}

	u8* memory_advance_new_ptr(const void* data, u32 size_in_bytes) {
		u8* base_address = (u8*)data;
		base_address += size_in_bytes;
		return base_address;
	}

	u8* memory_retreat_new_ptr(const void* data, u32 size_in_bytes) {
		u8* base_address = (u8*)data;
		base_address -= size_in_bytes;
		return base_address;
	}

	void* MACRO_memory_byte_advance(const void* data, u32 size_in_bytes) {
		u8* base_address = (u8*)data;
		base_address += size_in_bytes;
		return base_address;
	}

	void* MACRO_memory_byte_retreat(const void* data, u32 size_in_bytes) {
		u8* base_address = (u8*)data;
		base_address -= size_in_bytes;
		return base_address;
	}
#pragma endregion

#pragma region STRING
	#include "../include/ckg_string.h"
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
#pragma endregion

#pragma region LOGGER
	#include "../include/ckg_logger.h"
	#include "../include/ckg_memory.h"
	#include "../include/ckg_platform_services.h"
	#include "../include/ckg_assert.h"
	#include "../include/ckg_string.h"

	static Boolean logging_is_initialized = FALSE;
	Boolean logger_init() {
		if (!LOGGING_ENABLED) {
			// The logging system is disabled!
			return 1;
		}

		if (logging_is_initialized == FALSE) {
			logging_is_initialized = TRUE;
			platform_console_init();
			return TRUE;
		} else {
			LOG_FATAL("The logger system is already initalized!\n");
			return FALSE;
		}
	}

	/**
	 * @brief Includes a newline. This has a imposed limit of (PLATFORM_CHARACTER_LIMIT = 3200)
	 * Also another note this might want to allow the user of the log call to specify if its a new line or not instead of forcing it upon them.
	 * @param log_level 
	 * @param message 
	 * @param ... 
	 */
	void MACRO_log_output(LogLevel log_level, const char* message, ...) {
		char log_level_strings[LOG_LEVEL_COUNT][LOG_LEVEL_CHARACTER_LIMIT] = {
			"[FATAL]: ",
			"[ERROR]: ",
			"[WARN] : ",
			"[DEBUG]: ",
			"[INFO] : ",
			"",
		};

		u8 log_level_format[LOG_LEVEL_COUNT] = {
			BACK_RED,
			TEXT_RED,
			TEXT_PURPLE,
			TEXT_BLUE,
			TEXT_GREEN,
			TEXT_WHITE,
		};

		Boolean is_fatal = (log_level == 0);

		char out_message[PLATFORM_CHARACTER_LIMIT];
		memory_zero(out_message, sizeof(out_message));

		char out_message2[PLATFORM_CHARACTER_LIMIT];
		memory_zero(out_message2, sizeof(out_message2));
		
		va_list args_list;
		va_start(args_list, message);
		vsnprintf(out_message, PLATFORM_CHARACTER_LIMIT, message, args_list);
		va_end(args_list);

		sprintf(out_message2, "%s%s", log_level_strings[log_level], out_message);
		platform_console_write(out_message2, log_level_format[log_level]);
	}
#pragma endregion

