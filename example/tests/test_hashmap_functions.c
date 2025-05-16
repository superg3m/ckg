#include "../../ckg.h"

typedef struct Person {
    char* name;
    u32 age;
} Person;

u64 person_hash(u8* data, u32 size) {
    Person* person = (Person*)data;
    u64 h1 = ckg_string_hash(person->name, 0);
    u64 h2 = siphash24((u8*)&person->age, sizeof(person->age));
    return h1 ^ h2;
}

void test_hashmap_int_keys() {
    printf("Testing integer keys...\n");

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

    printf("Integer key test passed!\n");
}

/*
void test_string_literal_keys() {
    printf("Testing string literal keys...\n");

    CKG_HashMap(const char*, int)* map = NULLPTR;
    ckg_hashmap_init_string_hash(map, const char*, int);

    ckg_hashmap_put(map, "one", 1);
    ckg_hashmap_put(map, "two", 2);
    ckg_hashmap_put(map, "three", 3);
    ckg_hashmap_put(map, "four", 4);
    ckg_hashmap_put(map, "five", 5);

    ckg_assert(ckg_hashmap_get(map, "one") == 1);
    ckg_assert(ckg_hashmap_get(map, "two") == 2);
    ckg_assert(ckg_hashmap_get(map, "three") == 3);
    ckg_assert(ckg_hashmap_get(map, "four") == 4);
    ckg_assert(ckg_hashmap_get(map, "five") == 5);

    char buffer[10];
    strcpy(buffer, "three");
    ckg_assert(ckg_hashmap_get(map, buffer) == 3);

    ckg_free(map->entries);
    ckg_free(map);

    printf("String literal test passed!\n");
}

void test_char_ptr_keys() {
    printf("Testing char pointer keys...\n");

    CKG_HashMap(char*, double)* map = NULLPTR;
    ckg_hashmap_init_with_hash(map, char*, double, ckg_string_hash);

    char* key1 = strdup("apple");
    char* key2 = strdup("banana");
    char* key3 = strdup("cherry");
    char* key4 = strdup("apple");

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
    ckg_free(map->entries);
    ckg_free(map);

    printf("Char pointer test passed!\n");
}

void test_struct_keys() {
    printf("Testing struct keys...\n");

    CKG_HashMap(Person, int)* person_map = NULLPTR;
    ckg_hashmap_init_with_hash(person_map, Person, int, person_hash);

    Person p1 = {.name = "john", .age = 41};
    Person p2 = {.name = "alice", .age = 32};
    Person p3 = {.name = "bob", .age = 28};
    Person p4 = {.name = "john", .age = 41};

    ckg_hashmap_put(person_map, p1, 100);
    ckg_hashmap_put(person_map, p2, 200);
    ckg_hashmap_put(person_map, p3, 300);

    ckg_assert(ckg_hashmap_get(person_map, p1) == 100);
    ckg_assert(ckg_hashmap_get(person_map, p2) == 200);
    ckg_assert(ckg_hashmap_get(person_map, p3) == 300);
    ckg_assert(ckg_hashmap_get(person_map, p4) == 100);

    ckg_hashmap_put(person_map, p1, 150);
    ckg_assert(ckg_hashmap_get(person_map, p1) == 150);
    ckg_assert(ckg_hashmap_get(person_map, p4) == 150);

    CKG_HashMap(Point, char*)* point_map = NULLPTR;
    ckg_hashmap_init_with_hash(point_map, Point, char*, point_hash);

    Point pt1 = {.x = 10, .y = 20};
    Point pt2 = {.x = 5, .y = 15};
    Point pt3 = {.x = 10, .y = 20};

    ckg_hashmap_put(point_map, pt1, "point1");
    ckg_hashmap_put(point_map, pt2, "point2");

    char* val1 = ckg_hashmap_get(point_map, pt1);
    char* val2 = ckg_hashmap_get(point_map, pt2);
    char* val3 = ckg_hashmap_get(point_map, pt3);

    ckg_assert_msg(strcmp(val1, "point1") == 0, "Point 1 value incorrect");
    ckg_assert_msg(strcmp(val2, "point2") == 0, "Point 2 value incorrect");
    ckg_assert_msg(strcmp(val3, "point1") == 0, "Point 3 (duplicate) value incorrect");

    ckg_free(person_map->entries);
    ckg_free(person_map);
    ckg_free(point_map->entries);
    ckg_free(point_map);

    printf("Struct key test passed!\n");
}

void test_large_keys() {
    printf("Testing large keys...\n");

    CKG_HashMap(LargeKey, int)* map = NULLPTR;
    ckg_hashmap_init(map, LargeKey, int);

    LargeKey key1, key2, key3;
    memset(key1.data, 'A', sizeof(key1.data));
    memset(key2.data, 'B', sizeof(key2.data));
    memset(key3.data, 'A', sizeof(key3.data));

    key1.data[sizeof(key1.data) - 1] = '\0';
    key2.data[sizeof(key2.data) - 1] = '\0';
    key3.data[sizeof(key3.data) - 1] = '\0';

    ckg_hashmap_put(map, key1, 1000);
    ckg_hashmap_put(map, key2, 2000);

    ckg_assert(ckg_hashmap_get(map, key1) == 1000);
    ckg_assert(ckg_hashmap_get(map, key2) == 2000);
    ckg_assert(ckg_hashmap_get(map, key3) == 1000);

    ckg_free(map->entries);
    ckg_free(map);

    printf("Large key test passed!\n");
}

void test_collisions() {
    printf("Testing collision handling...\n");

    u64 bad_hash(const void* data, unsigned long size) {
        return 42;
    }

    CKG_HashMap(int, int)* map = NULLPTR;
    ckg_hashmap_init_with_hash(map, int, int, bad_hash);

    for (int i = 0; i < 20; i++) {
        ckg_hashmap_put(map, i, i * 10);
    }

    for (int i = 0; i < 20; i++) {
        int value = ckg_hashmap_get(map, i);
        ckg_assert_msg(value == i * 10, "Collision resolution failed");
    }

    ckg_free(map->entries);
    ckg_free(map);

    printf("Collision test passed!\n");
}
*/