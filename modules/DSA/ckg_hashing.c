#include "../../core/ckg_types.h"
#include "../../core/ckg_memory.h"
#include "../ckg_hashing.h"
#include "../../core/ckg_string.h"

internal const u32 prime_numbers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

u32 ckg_get_prime_by_index(u32 index) {
	return prime_numbers[index % ArrayCount(prime_numbers)];
}

u64 ckg_hash(unsigned char *str) {
    u64 hash = 5381;
    int c;

    u32 str_length = ckg_cstr_length(str);

    while (c = *str++) {
        hash = (((hash << 5) + hash) + c) + str_length;
    }

    return hash;
}

void ckg_test_collisions() {
    srand(time(NULL));

    const u32 STRING_LENGTH = 14;
    const u32 NUM_TESTS = 500;

    u8* hash_map = ckg_alloc(NUM_TESTS * sizeof(u8));
    char* test_string = ckg_alloc(sizeof(char) * (STRING_LENGTH + 1));

    s32 collisions = 0;

    for (s32 i = 0; i < NUM_TESTS; i++) {
        string_random(test_string, STRING_LENGTH);
        u64 h = ckg_hash(test_string);

        u32 hash_index = h % NUM_TESTS;

        // Check for collision
        if (hash_map[hash_index] != 0) {
            collisions++;
        }
        hash_map[h % NUM_TESTS]++;
    }

    ckg_free(hash_map);
    ckg_free(test_string);

    CKG_LOG_PRINT("Number of collisions: %d / %d\n", collisions, NUM_TESTS);
    CKG_LOG_PRINT("Collision rate: %f%%\n", ((double)collisions / (double)NUM_TESTS) * 100);
}
