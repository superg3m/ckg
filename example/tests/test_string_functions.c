#include "../../ckg.h"

void test_ckg_cstr_length() {
    u64 expected_size = 5;
    char str1[] = "Hello";
    u64 actual_size = ckg_cstr_length(str1);
    ckg_assert_msg(actual_size == expected_size, "Test ckg_str_length failed: expected %d, got %d\n", expected_size, actual_size);

    char str2[] = "";
    ckg_assert(ckg_cstr_length(str2) == 0);

    char str3[] = "Hello World";
    ckg_assert(ckg_cstr_length(str3) == 11);

    char str4[] = "Hi!\n";
    ckg_assert(ckg_cstr_length(str4) == 4);

    CKG_LOG_SUCCESS("Test ckg_str_length passed.\n");
}

void test_ckg_string_equal() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";

    u64 str1_length = ckg_cstr_length(str1);
    u64 str2_length = ckg_cstr_length(str2);
    u64 str3_length = ckg_cstr_length(str3);

    ckg_assert(ckg_str_equal(str1, str1_length, str2, str2_length) && !ckg_str_equal(str1, str1_length, str3, str3_length));

    char str4[] = "";
    u64 str4_length = ckg_cstr_length(str4);
    
    ckg_assert(!ckg_str_equal(str1, str1_length, str4, str4_length));
    ckg_assert(ckg_str_equal(str4, str4_length, str4, str4_length));

    char str5[] = "Hello ";
    u64 str5_length = ckg_cstr_length(str5);
    ckg_assert(!ckg_str_equal(str1, str1_length, str5, str5_length));

    CKG_LOG_SUCCESS("Test ckg_str_equal passed.\n");
}

void test_ckg_cstr_insert_char() {
    #define STR_CAP1 7
    char str1[STR_CAP1] = "Hello";
    u64 str1_length = ckg_cstr_length(str1);
    u64 hello_length = sizeof("Hello") - 1;

    ckg_str_insert_char(str1, str1_length++, STR_CAP1, 'V', 2);
    ckg_assert_msg(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("HeVllo")), "Test: ckg_cstr_insert_char failed -> got: %s | expected: %s\n", str1, "HeVllo");

    str1_length = hello_length;
    ckg_str_copy(str1, STR_CAP1, CKG_LIT_ARG("Hello"));
    ckg_str_insert_char(str1, str1_length++, STR_CAP1, 'X', 0);
    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("XHello")));

    str1_length = hello_length;
    ckg_str_copy(str1, STR_CAP1, CKG_LIT_ARG("Hello"));
    ckg_str_insert_char(str1, str1_length++, STR_CAP1, 'Y', 5);
    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("HelloY")));

    char str2[STR_CAP1] = "";
    u64 str2_length = ckg_cstr_length(str2);
    ckg_str_insert_char(str2, str2_length++, STR_CAP1, 'Z', 0);
    ckg_assert(ckg_str_equal(str2, str2_length, CKG_LIT_ARG("Z")));

    CKG_LOG_SUCCESS("Test ckg_cstr_insert_char passed.\n");
}

void test_ckg_cstr_insert() {
    #define STR_CAP2 16
    char str1[STR_CAP2] = "Hello";
    u64 hello_length = sizeof("Hello") - 1;
    u64 str1_length = hello_length;

    ckg_str_insert(str1, str1_length, STR_CAP2, CKG_LIT_ARG("|TESTINGS|"), 2);
    str1_length += sizeof("|TESTINGS|") - 1;
    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("He|TESTINGS|llo")));

    str1_length = hello_length;
    ckg_str_copy(str1, STR_CAP2, CKG_LIT_ARG("Hello"));
    ckg_str_insert(str1, str1_length, STR_CAP2, CKG_LIT_ARG("Start-"), 0);
    str1_length += sizeof("Start-") - 1;
    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("Start-Hello")));

    str1_length = hello_length;
    ckg_str_copy(str1, STR_CAP2, CKG_LIT_ARG("Hello"));
    ckg_str_insert(str1, str1_length, STR_CAP2, CKG_LIT_ARG("-End"), 5);
    str1_length += sizeof("-End") - 1;

    ckg_assert_msg(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("Hello-End")), "Test: ckg_cstr_insert failed at end s1: %s\n", str1);

    char str2[STR_CAP2] = "";
    u64 str2_length = 0;

    ckg_str_insert(str2, str2_length, STR_CAP2, CKG_LIT_ARG("Inserted"), 0);
    str2_length += sizeof("Inserted") - 1;

    ckg_assert(ckg_str_equal(str2, str2_length, CKG_LIT_ARG("Inserted")));

    CKG_LOG_SUCCESS("Test ckg_cstr_insert passed.\n");
}

void test_ckg_cstr_append() {
    #define STR_CAP3 13
    char str1[STR_CAP3] = {0};
    u64 str1_length = 0;

    str1_length = sizeof("Hello") - 1;
    ckg_str_copy(str1, STR_CAP3, CKG_LIT_ARG("Hello"));

    ckg_str_append(str1, str1_length, STR_CAP3, CKG_LIT_ARG(" World!"));
    str1_length += sizeof(" World!") - 1;

    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("Hello World!")));

    char str2[STR_CAP3] = "";
    u64 str2_length = 0;

    ckg_str_append(str2, str2_length, STR_CAP3, CKG_LIT_ARG("Appended"));
    str2_length += sizeof("Appended") - 1;

    ckg_assert(ckg_str_equal(str2, str2_length, CKG_LIT_ARG("Appended")));

    str1_length = sizeof("Hello") - 1;
    ckg_str_copy(str1, STR_CAP3, CKG_LIT_ARG("Hello"));
    ckg_str_append(str1, str1_length, STR_CAP3, CKG_LIT_ARG(""));
    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("Hello")));

    CKG_LOG_SUCCESS("Test ckg_cstr_append passed.\n");
}

void test_ckg_cstr_append_char() {
    #define STR_CAP4 50
    char str1[STR_CAP4] = "";
    u64 str1_length = 0;

    str1_length = sizeof("Hello") - 1;
    ckg_str_copy(str1, STR_CAP4, CKG_LIT_ARG("Hello"));
    ckg_str_append_char(str1, str1_length++, STR_CAP4, '!');
    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("Hello!")));

    char str2[50] = "";
    u64 str2_length = 0;
    ckg_str_append_char(str2, str2_length++, STR_CAP4, 'A');
    ckg_assert(ckg_str_equal(str2, str2_length, CKG_LIT_ARG("A")));

    str1_length = sizeof("Hi") - 1;
    ckg_str_copy(str1, STR_CAP4, CKG_LIT_ARG("Hi"));
    ckg_str_append_char(str1, str1_length++, STR_CAP4, ' ');
    ckg_str_append_char(str1, str1_length++, STR_CAP4, 'A');
    ckg_str_append_char(str1, str1_length++, STR_CAP4, '!');
    ckg_assert(ckg_str_equal(str1, str1_length, CKG_LIT_ARG("Hi A!")));

    CKG_LOG_SUCCESS("Test ckg_cstr_append_char passed.\n");
}

void test_ckg_cstr_clear() {
    char str1[50] = "Hello";
    ckg_memory_zero(str1, 50);
    ckg_assert(ckg_str_equal(str1, 0, "", 0));

    char str2[50] = "";
    ckg_memory_zero(str2, 50);
    ckg_assert(ckg_str_equal(str2, sizeof("") - 1, "", 0));

    CKG_LOG_SUCCESS("Test ckg_cstr_clear passed.\n");
}

void test_ckg_cstr_copy() {
    char str1[50] = "";
    ckg_str_copy(str1, 50, CKG_LIT_ARG("Hello!"));
    ckg_assert(ckg_str_equal(str1, sizeof("Hello!") - 1, CKG_LIT_ARG("Hello!")));

    CKG_LOG_SUCCESS("Test ckg_cstr_copy passed.\n");
}

void test_ckg_str_contains() {
    char t1[] = "hello";
    u64 t1_length = sizeof("hello") - 1;

    CKG_StringView substring_view = ckg_sv_create(t1, 1);
    ckg_assert(ckg_str_contains(substring_view.data, substring_view.length, CKG_LIT_ARG("h")));

    ckg_assert(!ckg_str_contains(t1, t1_length, CKG_LIT_ARG("")));
    ckg_assert(ckg_str_contains(t1, t1_length, CKG_LIT_ARG("h")));
    ckg_assert(ckg_str_contains(t1, t1_length, CKG_LIT_ARG("he")));
    ckg_assert(ckg_str_contains(t1, t1_length, CKG_LIT_ARG("o")));
    ckg_assert(!ckg_str_contains(t1, t1_length, CKG_LIT_ARG(";;;;;;")));
    ckg_assert(ckg_str_contains(t1, t1_length, CKG_LIT_ARG("hello")));
    ckg_assert(!ckg_str_contains(t1, t1_length, CKG_LIT_ARG("hllo")));
    ckg_assert(ckg_str_contains(t1, t1_length, CKG_LIT_ARG("hello")));

    CKG_LOG_SUCCESS("Test ckg_str_contains passed.\n");
}

void test_ckg_str_starts_with() {
    char t1[] = "hello";
    u64 t1_length = sizeof("hello") - 1;
    CKG_StringView substring_view = ckg_sv_create(t1, 2);
	ckg_assert(ckg_str_starts_with(substring_view.data, substring_view.length, CKG_LIT_ARG("he")));

	ckg_assert(ckg_str_starts_with(t1, t1_length, CKG_LIT_ARG("hell")));
	ckg_assert(ckg_str_starts_with(t1, t1_length, CKG_LIT_ARG("hello")));
	ckg_assert(!ckg_str_starts_with(t1, t1_length, CKG_LIT_ARG("hllo")));
	ckg_assert(!ckg_str_starts_with(t1, t1_length, CKG_LIT_ARG("")));


	char* t2 = "";
    u64 t2_length = 0;
	ckg_assert(ckg_str_starts_with(t2, t2_length, CKG_LIT_ARG("")));

	t2 = "f";
    t2_length = 1;
	ckg_assert(!ckg_str_starts_with(t2, t2_length, CKG_LIT_ARG("g")));
	ckg_assert(ckg_str_starts_with(t2, t2_length, CKG_LIT_ARG("f")));

    CKG_LOG_SUCCESS("Test ckg_str_starts_with passed.\n");
}

void test_ckg_str_ends_with() {
    char t1[] = "hello";
    u64 t1_length = sizeof("hello") - 1;
    CKG_StringView substring_view = ckg_sv_create(t1, 2);
	ckg_assert(ckg_str_ends_with(substring_view.data, substring_view.length, CKG_LIT_ARG("he")));
	ckg_assert(!ckg_str_ends_with(substring_view.data, substring_view.length, CKG_LIT_ARG("llo")));

	ckg_assert(ckg_str_ends_with(t1, t1_length, CKG_LIT_ARG("")));
	ckg_assert(ckg_str_ends_with(t1, t1_length, CKG_LIT_ARG("lo")));
	ckg_assert(ckg_str_ends_with(t1, t1_length, CKG_LIT_ARG("hello")));
	ckg_assert(ckg_str_ends_with(t1, t1_length, CKG_LIT_ARG("ello")));

	char* t2 = "";
    u64 t2_length = 0;
	ckg_assert(ckg_str_ends_with(t2, t2_length, CKG_LIT_ARG("")));
	
	t2 = "f";
    t2_length = 1;
	ckg_assert(!ckg_str_ends_with(t2, t2_length, CKG_LIT_ARG("g")));
	ckg_assert(ckg_str_ends_with(t2, t2_length, CKG_LIT_ARG("f")));

    CKG_LOG_SUCCESS("Test ckg_str_ends_with passed.\n");
}

void test_ckg_cstr_reverse() {
    char t1[] = "hello";

    CKG_StringView substring_view = ckg_sv_create(t1, 2);
    u64 reversed_string_length = substring_view.length;
    char* reversed_string = ckg_str_reverse(substring_view.data, substring_view.length);

	ckg_assert(ckg_str_equal(reversed_string, reversed_string_length, CKG_LIT_ARG("eh")));
	ckg_free(reversed_string);

    u64 reversed_string2_length = sizeof("Chicken") - 1;
    char* reversed_string2 = ckg_str_reverse(CKG_LIT_ARG("Chicken"));

    u64 reversed_string3_length = sizeof("Roast") - 1;
    char* reversed_string3 = ckg_str_reverse(CKG_LIT_ARG("Roast"));

    u64 reversed_string4_length = sizeof("Soup") - 1;
    char* reversed_string4 = ckg_str_reverse(CKG_LIT_ARG("Soup"));

	ckg_assert_msg(ckg_str_equal(reversed_string2, reversed_string2_length, CKG_LIT_ARG("nekcihC")), "test_ckg_cstr_reverse failed expected: %s | got: %s", "nekcihC", reversed_string2);
	ckg_assert_msg(ckg_str_equal(reversed_string3, reversed_string3_length, CKG_LIT_ARG("tsaoR")), "test_ckg_cstr_reverse failed expected: %s | got: %s", "tsaoR", reversed_string3);
	ckg_assert_msg(ckg_str_equal(reversed_string4, reversed_string4_length, CKG_LIT_ARG("puoS")), "test_ckg_cstr_reverse failed expected: %s | got: %s", "puoS", reversed_string4);

	ckg_free(reversed_string2);
	ckg_free(reversed_string3);
	ckg_free(reversed_string4);

	char* t2 = "";
    u64 reversed_t2_length = sizeof("") - 1;
    char* reversed_t2 = ckg_str_reverse(t2, reversed_t2_length);
	ckg_assert_msg(ckg_str_equal(reversed_t2, reversed_t2_length, CKG_LIT_ARG("")), "test_ckg_cstr_reverse failed expected: %s | got: %s", "\"\"", reversed_t2);
    ckg_free(reversed_t2);

	t2 = "f";
    reversed_t2_length = sizeof("f") - 1;
    reversed_t2 = ckg_str_reverse(t2, reversed_t2_length);
	ckg_assert_msg(ckg_str_equal(reversed_t2, reversed_t2_length, CKG_LIT_ARG("f")), "test_ckg_cstr_reverse failed expected: %s | got: %s", "f", reversed_t2);
	ckg_assert_msg(!ckg_str_equal(reversed_t2, reversed_t2_length, CKG_LIT_ARG("g")), "test_ckg_cstr_reverse failed expected: %s | got: %s", "f", reversed_t2);
    ckg_free(reversed_t2);

    CKG_LOG_SUCCESS("Test ckg_cstr_reverse passed.\n");
}

void test_ckg_str_index_of() {
    char t1[] = "hello ";
    u64 t1_length = sizeof("hello ") - 1;
    CKG_StringView substring_view = ckg_sv_create(t1, 2);

	ckg_assert(ckg_str_index_of(substring_view.data, substring_view.length, CKG_LIT_ARG("he")) == 0);
	ckg_assert(ckg_str_index_of(t1, t1_length, CKG_LIT_ARG("ell")) == 1);
	ckg_assert(ckg_str_index_of(t1, t1_length, CKG_LIT_ARG("l")) == 2);
	ckg_assert(ckg_str_index_of(t1, t1_length, CKG_LIT_ARG("o")) == 4);
	ckg_assert(ckg_str_index_of(t1, t1_length, CKG_LIT_ARG("hello")) == 0);

	ckg_assert(ckg_str_index_of(t1, t1_length, CKG_LIT_ARG(" ")) == 5);

	char* t2 = "";
    u64 t2_length = 0;
	ckg_assert(ckg_str_index_of(t2, t2_length, CKG_LIT_ARG("")) == 0);

	t2 = "f";
    t2_length = 1;
	ckg_assert(ckg_str_index_of(t2, t2_length, CKG_LIT_ARG("f")) == 0);

    CKG_LOG_SUCCESS("Test test_ckg_str_index_of passed.\n");
}

void test_ckg_str_last_index_of() {
    char t1[] = "hello";
    u64 t1_length = sizeof("hello") - 1;
    CKG_StringView substring_view = ckg_sv_create(t1, 2);

	ckg_assert(ckg_str_last_index_of(substring_view.data, substring_view.length, CKG_LIT_ARG("he")) == 0);

	ckg_assert(ckg_str_last_index_of(t1, t1_length, CKG_LIT_ARG("l")) == 3);
	ckg_assert(ckg_str_last_index_of(t1, t1_length, CKG_LIT_ARG("o")) == 4);
	ckg_assert(ckg_str_last_index_of(t1, t1_length, CKG_LIT_ARG("hello")) == 0);
	ckg_assert(ckg_str_last_index_of(t1, t1_length, CKG_LIT_ARG("r")) == -1);
	ckg_assert(ckg_str_last_index_of(t1, t1_length, CKG_LIT_ARG("h")) == 0);

	char* t2 = "";
    u64 t2_length = 0;
	ckg_assert(ckg_str_last_index_of(t2, t2_length, CKG_LIT_ARG("")) == 0);

	t2 = "ffefe";
    t2_length = sizeof("ffefe") - 1;
	ckg_assert(ckg_str_last_index_of(t2, t2_length, CKG_LIT_ARG("fe")) == 3);

    CKG_LOG_SUCCESS("Test test_ckg_str_last_index_of passed.\n");
}

void test_ckg_str_operations() { 
    CKG_LOG_PRINT("\n");
    CKG_LOG_DEBUG("======================= Testing String Functions =======================\n");
    test_ckg_cstr_length();
    test_ckg_string_equal();
    test_ckg_cstr_insert_char();
    test_ckg_cstr_insert();
    test_ckg_cstr_append();
    test_ckg_cstr_append_char();
    test_ckg_cstr_clear();
    test_ckg_cstr_copy();
    test_ckg_str_contains();
    test_ckg_str_starts_with();
    test_ckg_str_ends_with();
    test_ckg_cstr_reverse();
    test_ckg_str_index_of();
    test_ckg_str_last_index_of();

    // test_ckg_string_edgecases();
    // test_ckg_string_assertions();
    CKG_LOG_DEBUG("======================= String Functions All Passed =======================\n");
    CKG_LOG_PRINT("\n");
}