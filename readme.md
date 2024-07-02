# CKG
The point of the ckit granular (ckg) is building out everything at a granular level  and then using these building block to build a good common use case version. so very few types and allocation is decided by the caller in most cases.

# how to build
1. ./bootstrap.ps1
2. ./build.ps1
2. ./run.ps1

- Collection of tools, data structures, and algorithms that I find useful
- If cl.exe is not defined in your terminal run vars.ps1
- Compile with CUSTOM_PLATFORM_IMPL defined if you want to change how platform specific functions work.


- CORE
    - memory.c
    - string.c
    - file_io.c
        - open_file()
        - read_entire_file()
        - close_file()

    - os.c
        - os_get_extension(path)
        - os_get_child_items(path, Boolean is_recrusive_search)

    - assert.c
    - error.c
    - logger.c
    - event_system.c
    - input.c
        - key_up(KeyCode key_a) released current frame and last from
        - key_down(KeyCode key_a) // pressed in that frame 
        - key_pressed(KeyCode key_a) // key down currently and was down last frame
        - key_released(KeyCode key_a) // release that frame

        - key_group_up(...) released current frame and last from
        - key_group_down(...) // pressed in that frame 
        - key_group_pressed(...) // key down currently and was down last frame
        - key_group_released(...) // release that frame
    - platform_services.c
    - networking.c
        - udp/tcp
        - udp hole punching
        - host and client structs 
        - NAT

    - types.c

    - threading.c
        - semaphores
        - job_system
    - simd.c
        - intrinsics
    - math.c
        - Vector2, Vector3
        - simd calculations
        - roundf, sin, cos, tan (use intrinsics)

- MODULES
    - asset.c
        - 2D
            - bitmap_loader
            - png_loader
        - 3D
            - obj_loader

    - DSA.c
        - Data Structures
            - vector (Make sure this isn't used everywhere in ckg)
            - hashing
            - hashmap (uses hashing)
            - linked_list