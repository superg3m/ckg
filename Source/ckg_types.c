#include "../Include/ckg_types.h"

void U32_EndianSwap(u32* number_to_endian_swap) {
    u32 temp = *number_to_endian_swap;
    
    u32 b0 = (temp >> 0) & 0xFF;
    u32 b1 = (temp >> 8) & 0xFF;
    u32 b2 = (temp >> 16) & 0xFF;
    u32 b3 = (temp >> 24) & 0xFF;

    *number_to_endian_swap = (b0 << 24)|(b1 << 16)|(b2 << 8)|(b3 << 0);
} 

void U64_EndianSwap(u64* number_to_endian_swap) {
    u64 temp = *number_to_endian_swap;
    
    u64 b0 = (temp >> 0) & 0xFF;
    u64 b1 = (temp >> 8) & 0xFF;
    u64 b2 = (temp >> 16) & 0xFF;
    u64 b3 = (temp >> 24) & 0xFF;
    u64 b4 = (temp >> 32) & 0xFF;
    u64 b5 = (temp >> 40) & 0xFF;
    u64 b6 = (temp >> 48) & 0xFF;
    u64 b7 = (temp >> 56) & 0xFF;

    *number_to_endian_swap = (b0 << 56)|(b1 << 48)|(b2 << 40)|(b3 << 32)|(b4 << 24)|(b5 << 16)|(b6 << 8)|(b7 << 0);
}