# CKG
The point of the ckit granular (ckg) is building out everything at a granular level  and then using these building block to build a good common use case version. so very few types and allocation is decided by the caller in most cases.

# How to build
1. ./bootstrap.ps1
2. ./build.ps1
2. ./run.ps1

- Collection of tools, data structures, and algorithms that I find useful
- If cl.exe is not defined in your terminal run vars.ps1
- Compile with CUSTOM_PLATFORM_IMPL defined if you want to change how platform specific functions work.


# Goals

## CORE

- [x] ckg_types.c

### Assert
- [x] ckg_assert.c

### Logger
- [x] ckg_logger.c

### String
- [x] ckg_cstring.c

### Memory
- [x] ckg_memory.c

### FileIO
- [x] ckg_file_io.c // should revist this though
	- [x] ckg_open_file()
	- [x] ckg_read_entire_file() // Not great because it can overflow
	- [x] ckg_close_file()






- [ ] ckg_math.c
	- [ ] Vector2, Vector3
	- [ ] simd calculations
	- [ ] ckg_abs() // sort of done for signed integers but make it better
	- [ ] roundf, sin, cos, tan (use intrinsics)

