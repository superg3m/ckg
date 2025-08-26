#include "../../ckg.h"

/*
typedef struct DebugEntry {
    char* key;
    int value;
    bool filled;
} DebugEntry;

typedef struct DebugMap {
    CKG_HashMapMeta meta;
    char* temp_key;
    int temp_value;
    DebugEntry* entries;
} DebugMap;
*/

typedef struct Person {
    char* name;
    int age;
} Person;

u64 person_hash(void* data, u64 size) {
    (void)size;

    Person* person = (Person*)data;
    u64 h1 = ckg_string_hash(person->name, 0);
    u64 h2 = siphash24(&person->age, sizeof(person->age));
    return h1 ^ h2;
}

bool person_equality(void* c1, size_t c1_size, void* c2, size_t c2_size) {
    (void)c1_size;
    (void)c2_size;

    Person* p1 = (Person*)c1;
    Person* p2 = (Person*)c2;

    return (
        p1->age == p2->age &&
        ckg_str_equal(p1->name, ckg_cstr_length(p1->name), p2->name, ckg_cstr_length(p2->name))
    );
}

void test_integer_keys() {
    CKG_HashMap(int, int)* map = NULLPTR;
    ckg_hashmap_init_siphash(map, int, int);

    for (int i = 0; i < 100; i++) {
        ckg_hashmap_put(map, i, i * 10);
    }

    for (int i = 0; i < 100; i++) {
        int value = ckg_hashmap_get(map, i);
        ckg_assert(value == i * 10);
    }

    for (int i = 0; i < 50; i++) {
        ckg_hashmap_put(map, i, i * 20);
    }

    for (int i = 0; i < 50; i++) {
        int value = ckg_hashmap_get(map, i);
        ckg_assert(value == i * 20);
    }

    ckg_free(map->entries);
    ckg_free(map);

    CKG_LOG_SUCCESS("Integer key test passed!\n");
}

void test_string_literal_keys() {
    CKG_HashMap(char*, int)* str_map = NULLPTR;
    ckg_hashmap_init_string_hash(str_map, char*, int);

    ckg_hashmap_put(str_map, "one", 1);
    ckg_hashmap_put(str_map, "two", 2);
    ckg_hashmap_put(str_map, "three", 3);
    ckg_hashmap_put(str_map, "four", 4);
    ckg_hashmap_put(str_map, "five", 5);

    ckg_assert(ckg_hashmap_get(str_map, "one") == 1);
    ckg_assert(ckg_hashmap_get(str_map, "two") == 2);
    ckg_assert(ckg_hashmap_get(str_map, "three") == 3);
    ckg_assert(ckg_hashmap_get(str_map, "four") == 4);
    ckg_assert(ckg_hashmap_get(str_map, "five") == 5);

    char buffer[10];
    ckg_str_copy(buffer, sizeof(buffer), CKG_LIT_ARG("three"));
    ckg_assert(ckg_hashmap_get(str_map, buffer) == 3);

    ckg_hashmap_free(str_map);

    CKG_LOG_SUCCESS("String literal test passed!\n");
}

void test_char_ptr_keys() {
    CKG_HashMap(char*, double)* map = NULLPTR;
    ckg_hashmap_init_string_hash(map, char*, double);

    char* key1 = ckg_str_alloc(CKG_LIT_ARG("apple"));
    char* key2 = ckg_str_alloc(CKG_LIT_ARG("banana"));
    char* key3 = ckg_str_alloc(CKG_LIT_ARG("cherry"));
    char* key4 = ckg_str_alloc(CKG_LIT_ARG("apple"));

    ckg_hashmap_put(map, key1, 1.5);
    ckg_hashmap_put(map, key2, 2.7);
    ckg_hashmap_put(map, key3, 3.14);

    ckg_assert(ckg_hashmap_get(map, key1) == 1.5);
    ckg_assert(ckg_hashmap_get(map, key2) == 2.7);
    ckg_assert(ckg_hashmap_get(map, key3) == 3.14);
    ckg_assert(ckg_hashmap_get(map, key4) == 1.5);

    ckg_hashmap_put(map, key1, 5.5);
    ckg_assert(ckg_hashmap_get(map, key1) == 5.5);
    ckg_assert(ckg_hashmap_get(map, key4) == 5.5);

    ckg_free(key1);
    ckg_free(key2);
    ckg_free(key3);
    ckg_free(key4);

    ckg_hashmap_free(map);

    CKG_LOG_SUCCESS("Char pointer test passed!\n");
}

void test_struct_keys() {
    CKG_HashMap(Person, int)* map = NULLPTR;
    ckg_hashmap_init_with_hash(map, Person, int, false, person_hash, person_equality);

    Person p1 = { "Alice", 30 };
    Person p2 = { "Bob", 25 };
    Person p3 = { "Charlie", 40 };
    Person p4 = { "Alice", 30 }; // Duplicate of p1

    ckg_hashmap_put(map, p1, 100);
    ckg_hashmap_put(map, p2, 200);
    ckg_hashmap_put(map, p3, 300);

    ckg_assert(ckg_hashmap_get(map, p1) == 100);
    ckg_assert(ckg_hashmap_get(map, p2) == 200);
    ckg_assert(ckg_hashmap_get(map, p3) == 300);
    ckg_assert(ckg_hashmap_get(map, p4) == 100); // Should match p1

    ckg_hashmap_put(map, p4, 999); // Overwrite p1

    ckg_assert(ckg_hashmap_get(map, p1) == 999);
    ckg_assert(ckg_hashmap_get(map, p4) == 999);

    int v = ckg_hashmap_pop(map, p4);
    ckg_assert(v == 999);

    ckg_hashmap_free(map);

    CKG_LOG_SUCCESS("Struct key test passed!\n");
}

typedef struct TrivialStruct {
  int a;
  bool b;
  char c;
  double d;
} TrivialStruct;

void test_trival_struct() {
  CKG_HashMap(TrivialStruct, double)* map = NULLPTR;
  ckg_hashmap_init_siphash(map, TrivialStruct, double);

  TrivialStruct p1 = {1, true, 'a', 1.0};
  TrivialStruct p2 = {2, false, 'b', 2.0};
  TrivialStruct p3 = {3, true, 'c', 3.0};
  TrivialStruct p4 = {1, true, 'a', 1.0}; // Duplicate of p1

  ckg_hashmap_put(map, p1, 100.0);
  ckg_hashmap_put(map, p2, 200.0);
  ckg_hashmap_put(map, p3, 300.0);

  ckg_assert(ckg_hashmap_get(map, p1) == 100.0);
  ckg_assert(ckg_hashmap_get(map, p2) == 200.0);
  ckg_assert(ckg_hashmap_get(map, p3) == 300.0);
  ckg_assert(ckg_hashmap_get(map, p4) == 100.0); // Should match p1

  ckg_hashmap_put(map, p4, 999.0); // Overwrite p1

  ckg_assert(ckg_hashmap_get(map, p1) == 999.0);
  ckg_assert(ckg_hashmap_get(map, p4) == 999.0);

  double v = ckg_hashmap_pop(map, p4);
  ckg_assert(v == 999.0);

  ckg_hashmap_free(map);

  CKG_LOG_SUCCESS("TrivialStruct key test passed!\n");
}

// nothing

// Combine all tests here
void ckg_hashmap_test() {
    // DebugMap m = {0};
    // (void)m;

    test_integer_keys();
    test_string_literal_keys();
    test_char_ptr_keys();
    test_struct_keys();
    test_trival_struct();
}
