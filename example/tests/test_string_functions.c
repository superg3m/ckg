#include "../../ckg.h"

void test_ckg_cstr_length() {
    const int expected_size = 5;
    char str1[] = "Hello";
    u64 actual_size = ckg_cstr_length(str1);
    ckg_assert_msg(actual_size == expected_size, "Test ckg_cstr_length failed: expected %d, got %d\n", expected_size, actual_size);

    char str2[] = "";
    ckg_assert(ckg_cstr_length(str2) == 0);

    char str3[] = "Hello World";
    ckg_assert(ckg_cstr_length(str3) == 11);

    char str4[] = "Hi!\n";
    ckg_assert(ckg_cstr_length(str4) == 4);

    CKG_LOG_SUCCESS("Test ckg_cstr_length passed.\n");
}

void test_ckg_string_equal() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";

    u64 str1_length = ckg_cstr_length(str1);
    u64 str2_length = ckg_cstr_length(str2);
    u64 str3_length = ckg_cstr_length(str3);

    ckg_assert(ckg_cstr_equal(str1, str1_length, str2, str2_length) && !ckg_cstr_equal(str1, str1_length, str3, str3_length));

    char str4[] = "";
    u64 str4_length = ckg_cstr_length(str4);
    
    ckg_assert(!ckg_cstr_equal(str1, str1_length, str4, str4_length));
    ckg_assert(ckg_cstr_equal(str4, str4_length, str4, str4_length));

    char str5[] = "Hello ";
    u64 str5_length = ckg_cstr_length(str5);
    ckg_assert(!ckg_cstr_equal(str1, str1_length, str5, str5_length));

    CKG_LOG_SUCCESS("Test ckg_cstr_equal passed.\n");
}

void test_ckg_cstr_insert_char() {
    #define STR_CAP1 7
    char str1[STR_CAP1] = "Hello";
    u64 str1_length = ckg_cstr_length(str1);
    u64 hello_length = sizeof("Hello") - 1;

    ckg_cstr_insert_char(str1, str1_length++, STR_CAP1, 'V', 2);
    ckg_assert_msg(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("HeVllo")), "Test: ckg_cstr_insert_char failed -> got: %s | expected: %s\n", str1, "HeVllo");

    str1_length = hello_length;
    ckg_memory_copy("Hello", str1, sizeof("Hello") - 1, STR_CAP1);
    ckg_cstr_insert_char(str1, str1_length++, STR_CAP1, 'X', 0);
    ckg_assert(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("XHello")));

    str1_length = hello_length;
    ckg_memory_copy("Hello", str1, sizeof("Hello") - 1, STR_CAP1);
    ckg_cstr_insert_char(str1, str1_length++, STR_CAP1, 'Y', 5);
    ckg_assert(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("HelloY")));

    char str2[STR_CAP1] = "";
    u64 str2_length = ckg_cstr_length(str2);
    ckg_cstr_insert_char(str2, str2_length++, STR_CAP1, 'Z', 0);
    ckg_assert(ckg_cstr_equal(str2, str2_length, CKG_LIT_ARG("Z")));

    CKG_LOG_SUCCESS("Test ckg_cstr_insert_char passed.\n");
}

void test_ckg_cstr_insert() {
    #define STR_CAP2 16
    char str1[STR_CAP2] = "Hello";
    const u64 hello_length = sizeof("Hello") - 1;
    u64 str1_length = hello_length;

    ckg_cstr_insert(str1, str1_length, STR_CAP2, CKG_LIT_ARG("|TESTINGS|"), 2);
    str1_length += sizeof("|TESTINGS|") - 1;
    ckg_assert(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("He|TESTINGS|llo")));

    str1_length = hello_length;
    ckg_memory_copy("Hello", str1, sizeof("Hello") - 1, STR_CAP2);
    ckg_cstr_insert(str1, str1_length, STR_CAP2, CKG_LIT_ARG("Start-"), 0);
    str1_length += sizeof("Start-") - 1;
    ckg_assert(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("Start-Hello")));

    str1_length = hello_length;
    ckg_memory_copy("Hello", str1, sizeof("Hello") - 1, STR_CAP2);
    ckg_cstr_insert(str1, str1_length, STR_CAP2, CKG_LIT_ARG("-End"), 5);
    str1_length += sizeof("-End") - 1;

    ckg_assert_msg(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("Hello-End")), "Test: ckg_cstr_insert failed at end s1: %s\n", str1);

    char str2[STR_CAP2] = "";
    u64 str2_length = 0;

    ckg_cstr_insert(str2, str2_length, STR_CAP2, CKG_LIT_ARG("Inserted"), 0);
    str2_length += sizeof("Inserted") - 1;

    ckg_assert(ckg_cstr_equal(str2, str2_length, CKG_LIT_ARG("Inserted")));

    CKG_LOG_SUCCESS("Test ckg_cstr_insert passed.\n");
}

void test_ckg_cstr_append() {
    #define STR_CAP3 13
    char str1[STR_CAP3] = {0};
    u64 str1_length = 0;
    ckg_memory_copy("Hello", str1, sizeof("Hello") - 1, STR_CAP3);
    str1_length = sizeof("Hello") - 1;

    ckg_cstr_append(str1, str1_length, STR_CAP3, CKG_LIT_ARG(" World!"));
    str1_length += sizeof(" World!") - 1;

    ckg_assert(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("Hello World!")));

    char str2[STR_CAP3] = "";
    u64 str2_length = 0;

    ckg_cstr_append(str2, str2_length, STR_CAP3, CKG_LIT_ARG("Appended"));
    str2_length += sizeof("Appended") - 1;

    ckg_assert(ckg_cstr_equal(str2, str2_length, CKG_LIT_ARG("Appended")));

    ckg_memory_copy("Hello", str1, sizeof("Hello") - 1, STR_CAP3);
    str1_length = sizeof("Hello") - 1;
    ckg_cstr_append(str1, str1_length, STR_CAP3, CKG_LIT_ARG(""));
    ckg_assert(ckg_cstr_equal(str1, str1_length, CKG_LIT_ARG("Hello")));

    CKG_LOG_SUCCESS("Test ckg_cstr_append passed.\n");
}

/*
void test_ckg_cstr_append_char() {
    char str1[50] = {0};
    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_append_char(str1, 50, '!');
    ckg_assert(ckg_cstr_equal(str1, "Hello!"));

    char str2[50] = "";
    ckg_cstr_append_char(str2, 50, 'A');
    ckg_assert(ckg_cstr_equal(str2, "A"));

    ckg_cstr_copy(str1, 50, "Hi");
    ckg_cstr_append_char(str1, 50, ' ');
    ckg_cstr_append_char(str1, 50, 'A');
    ckg_cstr_append_char(str1, 50, '!');
    ckg_assert(ckg_cstr_equal(str1, "Hi A!"));

    CKG_LOG_SUCCESS("Test ckg_cstr_append_char passed.\n");
}

void test_ckg_cstr_clear() {
    char str1[50] = "Hello";
    ckg_cstr_clear(str1);
    ckg_assert(ckg_cstr_equal(str1, ""));

    char str2[50] = "";
    ckg_cstr_clear(str2);
    ckg_assert(ckg_cstr_equal(str2, ""));

    CKG_LOG_SUCCESS("Test ckg_cstr_clear passed.\n");
}

void test_ckg_cstr_copy() {
    char str1[50] = {0};
    ckg_cstr_copy(str1, 50, "Hello!");
    ckg_assert(ckg_cstr_equal(str1, "Hello!"));

    CKG_LOG_SUCCESS("Test ckg_cstr_copy passed.\n");
}

void test_ckg_cstr_contains() {
    char t1[] = "hello";
    char* sub_str = (char*)ckg_alloc(2);
    ckg_substring(t1, sub_str, 0, 1);

    ckg_assert(ckg_cstr_contains(sub_str, "h"));
    ckg_free(sub_str);

    ckg_assert(!ckg_cstr_contains(t1, ""));
    ckg_assert(ckg_cstr_contains(t1, "h"));
    ckg_assert(ckg_cstr_contains(t1, "he"));
    ckg_assert(ckg_cstr_contains(t1, "o"));
    ckg_assert(!ckg_cstr_contains(t1, ";;;;;;"));
    ckg_assert(ckg_cstr_contains(t1, "hello"));
    ckg_assert(!ckg_cstr_contains(t1, "hllo"));
    ckg_assert(ckg_cstr_contains(t1, "hello"));

    CKG_LOG_SUCCESS("Test ckg_cstr_contains passed.\n");
}

void test_ckg_cstr_starts_with() {
    char t1[] = "hello";
	char* sub_str = (char*)ckg_alloc(2);
    ckg_substring(t1, sub_str, 0, 1);
	ckg_assert(ckg_cstr_starts_with(sub_str, "h"));
	ckg_free(sub_str);

	ckg_assert(ckg_cstr_starts_with(t1, "hell"));
	ckg_assert(ckg_cstr_starts_with(t1, "hello"));
	ckg_assert(!ckg_cstr_starts_with(t1, "hllo"));
	ckg_assert(!ckg_cstr_starts_with(t1, ""));


	const char* t2 = "";
	ckg_assert(ckg_cstr_starts_with(t2, ""));
	

	t2 = "f";
	ckg_assert(!ckg_cstr_starts_with(t2, "g"));
	ckg_assert(ckg_cstr_starts_with(t2, "f"));

    CKG_LOG_SUCCESS("Test ckg_cstr_starts_with passed.\n");
}

void test_ckg_cstr_ends_with() {
    char t1[] = "hello";
	char* sub_str = (char*)ckg_alloc(3);
    ckg_substring(t1, sub_str, 0, 2);
	ckg_assert(ckg_cstr_ends_with(sub_str, "he"));
	ckg_assert(!ckg_cstr_ends_with(sub_str, "llo"));
	ckg_free(sub_str);

	ckg_assert(ckg_cstr_ends_with(t1, ""));
	ckg_assert(ckg_cstr_ends_with(t1, "lo"));
	ckg_assert(ckg_cstr_ends_with(t1, "hello"));
	ckg_assert(ckg_cstr_ends_with(t1, "ello"));

	const char* t2 = "";
	ckg_assert(ckg_cstr_ends_with(t2, ""));
	

	t2 = "f";
	ckg_assert(!ckg_cstr_ends_with(t2, "g"));
	ckg_assert(ckg_cstr_ends_with(t2, "f"));

    CKG_LOG_SUCCESS("Test ckg_cstr_ends_with passed.\n");
}

void test_ckg_cstr_reverse() {
    char t1[] = "hello";
	char* sub_str = (char*)ckg_alloc(3);
    ckg_substring(t1, sub_str, 0, 2);
    char* reversed_string = (char*)ckg_alloc(ckg_cstr_length(sub_str) + 1);
    ckg_cstr_reverse(sub_str, reversed_string, ckg_cstr_length(sub_str) + 1);
	ckg_assert(ckg_cstr_equal(reversed_string, "eh"));
	ckg_free(sub_str);
	ckg_free(reversed_string);

    char* reversed_string2 = (char*)ckg_alloc(ckg_cstr_length("Chicken") + 1);
    ckg_cstr_reverse("Chicken", reversed_string2, ckg_cstr_length("Chicken") + 1);
    char* reversed_string3 = (char*)ckg_alloc(ckg_cstr_length("Roast") + 1);
    ckg_cstr_reverse("Roast", reversed_string3, ckg_cstr_length("Chicken") + 1);
    char* reversed_string4 = (char*)ckg_alloc(ckg_cstr_length("Soup") + 1);
    ckg_cstr_reverse("Soup", reversed_string4, ckg_cstr_length("Chicken") + 1);

	ckg_assert_msg(ckg_cstr_equal(reversed_string2, "nekcihC"), "test_ckg_cstr_reverse failed expected: %s | got: %s", "nekcihC", reversed_string2);
	ckg_assert_msg(ckg_cstr_equal(reversed_string3, "tsaoR"), "test_ckg_cstr_reverse failed expected: %s | got: %s", "tsaoR", reversed_string3);
	ckg_assert_msg(ckg_cstr_equal(reversed_string4, "puoS"), "test_ckg_cstr_reverse failed expected: %s | got: %s", "puoS", reversed_string4);

	ckg_free(reversed_string2);
	ckg_free(reversed_string3);
	ckg_free(reversed_string4);


	const char* t2 = "";
    char* reversed_t2 = (char*)ckg_alloc(ckg_cstr_length(t2) + 1);
    ckg_cstr_reverse(t2, reversed_t2, ckg_cstr_length(t2)+ 1);
	ckg_assert_msg(ckg_cstr_equal(reversed_t2, ""), "test_ckg_cstr_reverse failed expected: %s | got: %s", "", reversed_t2);
    ckg_free(reversed_t2);

	t2 = "f";
    reversed_t2 = (char*)ckg_alloc(ckg_cstr_length(t2) + 1);
    ckg_cstr_reverse(t2, reversed_t2, ckg_cstr_length(t2) + 1);
	ckg_assert_msg(ckg_cstr_equal(reversed_t2, "f"), "test_ckg_cstr_reverse failed expected: %s | got: %s", "f", reversed_t2);
	ckg_assert_msg(!ckg_cstr_equal(reversed_t2, "g"), "test_ckg_cstr_reverse failed expected: %s | got: %s", "f", reversed_t2);
    ckg_free(reversed_t2);

    CKG_LOG_SUCCESS("Test ckg_cstr_reverse passed.\n");
}

void test_ckg_cstr_index_of() {
    char t1[] = "hello ";
	char* sub_str = (char*)ckg_alloc(3);
    ckg_substring(t1, sub_str, 0, 2);

	ckg_assert(ckg_cstr_index_of(sub_str, "he") == 0);
	ckg_free(sub_str);

	ckg_assert(ckg_cstr_index_of(t1, "ell") == 1);
	ckg_assert(ckg_cstr_index_of(t1, "l") == 2);
	ckg_assert(ckg_cstr_index_of(t1, "o") == 4);
	ckg_assert(ckg_cstr_index_of(t1, "hello") == 0);

	ckg_assert(ckg_cstr_index_of(t1, " ") == 5);

	const char* t2 = "";
	ckg_assert(ckg_cstr_index_of(t2, "") == 0);

	t2 = "f";
	ckg_assert(ckg_cstr_index_of(t2, "f") == 0);

    CKG_LOG_SUCCESS("Test test_ckg_cstr_index_of passed.\n");
}

void test_ckg_string_assertions() {
    char str1[10] = "Overflow";
    ckg_cstr_append(str1, 10, "ingTest");
    ckg_assert(!ckg_cstr_equal(str1, "OverflowingTest"));

    char str2[6] = "Short";
    ckg_cstr_append_char(str2, 6, 'X');
    ckg_assert(!ckg_cstr_equal(str2, "ShortX"));
}

void test_ckg_string_edgecases() {
    CKG_LOG_WARN("=============================== EXPECTED ASSERTS START ===============================\n");
    ckg_assert(ckg_cstr_length("") == 0);
    ckg_assert(ckg_cstr_length(NULL));

    // Test edge cases for ckg_cstr_equal
    ckg_assert(ckg_cstr_equal(NULL, NULL));
    ckg_assert(!ckg_cstr_equal("Hello", NULL));
    ckg_assert(!ckg_cstr_equal(NULL, "Hello"));

    // Test edge cases for ckg_cstr_insert_char
    char str1[50] = "Hello";

    ckg_cstr_insert_char(str1, 50, 'V', 10); // Insert at a position beyond the string length

    ckg_assert(ckg_cstr_equal(str1, "HelloV"));

    char str2[50] = "";
    ckg_cstr_insert_char(str2, 50, 'Z', 0); // Insert into an empty string
    ckg_assert(ckg_cstr_equal(str2, "Z"));

    // Test edge cases for ckg_cstr_append
    char str3[50] = "Hello";
    ckg_cstr_append(str3, 50, NULL); // Append a null string
    ckg_assert(ckg_cstr_equal(str3, "Hello"));

    char str4[50] = "";
    ckg_cstr_append(str4, 50, "Appended"); // Append to an empty string
    ckg_assert(ckg_cstr_equal(str4, "Appended"));
    CKG_LOG_WARN("=============================== EXPECTED ASSERTS END ===============================\n");
    CKG_LOG_SUCCESS("Test ckg_string_edgecases passed.\n");
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
    test_ckg_cstr_contains();
    test_ckg_cstr_starts_with();
    test_ckg_cstr_ends_with();
    test_ckg_cstr_reverse();
    test_ckg_cstr_index_of();

    int test_int_to_cstr = 5112512;
    char* string_buffer = (char*)ckg_alloc(9);
    ckg_cstr_int_to_cstr(string_buffer, 9, test_int_to_cstr);
    CKG_LOG_SUCCESS("INT TO STRING: %s\n", string_buffer);
    ckg_free(string_buffer);

    // test_ckg_string_edgecases();
    // test_ckg_string_assertions();
    CKG_LOG_DEBUG("======================= String Functions All Passed =======================\n");
    CKG_LOG_PRINT("\n");
}
*/