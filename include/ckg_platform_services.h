#pragma once
/*===========================================================
 * File: platform_services.h
 * Date: May 10, 2024
 * Creator: Jovanni Djonaj
===========================================================*/


//========================== Begin Types ==========================
// Supported Platforms
#if (_WIN32)
  #define PLATFORM_WINDOWS
  #include <windows.h>
#elif (__linux__)
  #define PLATFORM_LINUX
#elif (__APPLE__)
  #define PLATFORM_MACOS
#endif
//=========================== End Types ===========================





//************************* Begin Functions *************************
// Supported Platform Operations

#ifdef __cplusplus
extern "C" {
#endif
  void* platform_allocate(unsigned long long number_of_bytes);
  void* MACRO_platform_free(void* data);
  void platform_console_write(const char* message, unsigned char color);
  void platform_console_init();
  void platform_console_shutdown();
  // void _platform_open_window();
  // void _platform_open_file();
  // void _platform_close_file();
  // void _platform_sleep();
#ifdef __cplusplus
}
#endif

//************************** End Functions **************************

//+++++++++++++++++++++++++++ Begin Macros ++++++++++++++++++++++++++
#define platform_free(data) data = MACRO_platform_free(data);
//++++++++++++++++++++++++++++ End Macros +++++++++++++++++++++++++++

#define PLATFORM_CHARACTER_LIMIT 200