#include "../../ckg.h"

void test_ckg_str_length() {
    const int expected_size = 5;
    char str1[] = "Hello";
    int actual_size = ckg_str_length(str1);
    ckg_assert_msg(actual_size == expected_size, "Test ckg_str_length failed: expected %d, got %d\n", expected_size, actual_size);

    char str2[] = "";
    ckg_assert(ckg_str_length(str2) == 0);

    char str3[] = "Hello World";
    ckg_assert(ckg_str_length(str3) == 11);

    char str4[] = "Hi!\n";
    ckg_assert(ckg_str_length(str4) == 4);

    CKG_LOG_SUCCESS("Test ckg_str_length passed.\n");
}

void test_ckg_string_equal() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";
    ckg_assert(ckg_str_equal(str1, str2) && !ckg_str_equal(str1, str3));

    char str4[] = "";
    ckg_assert(!ckg_str_equal(str1, str4));

    ckg_assert(ckg_str_equal(str4, str4));

    char str5[] = "Hello ";
    ckg_assert(!ckg_str_equal(str1, str5));

    CKG_LOG_SUCCESS("Test ckg_str_equal passed.\n");
}

void test_ckg_cstr_insert_char() {
    char str1[50] = "Hello";
    ckg_cstr_insert_char(str1, 50, 'V', 2);
    ckg_assert_msg(ckg_str_equal(str1, "HeVllo"), "Test: ckg_cstr_insert_char failed -> got: %s | expected: %s\n", str1, "HeVllo");

    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_insert_char(str1, 50, 'X', 0);
    ckg_assert(ckg_str_equal(str1, "XHello"));

    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_insert_char(str1, 50, 'Y', 5);
    ckg_assert(ckg_str_equal(str1, "HelloY"));

    char str2[50] = "";
    ckg_cstr_insert_char(str2, 50, 'Z', 0);
    ckg_assert(ckg_str_equal(str2, "Z"));

    CKG_LOG_SUCCESS("Test ckg_cstr_insert_char passed.\n");
}

void test_ckg_cstr_insert() {
    char str1[50] = "Hello";
    ckg_cstr_insert(str1, 50, "|TESTINGS|", 2);
    ckg_assert(ckg_str_equal(str1, "He|TESTINGS|llo"));

    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_insert(str1, 50, "Start-", 0);
    ckg_assert(ckg_str_equal(str1, "Start-Hello"));

    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_insert(str1, 50, "-End", 5);

    ckg_assert_msg(ckg_str_equal(str1, "Hello-End"), "Test: ckg_cstr_insert failed at end s1: %s\n", str1);

    char str2[50] = "";
    ckg_cstr_insert(str2, 50, "Inserted", 0);
    ckg_assert(ckg_str_equal(str2, "Inserted"));

    CKG_LOG_SUCCESS("Test ckg_cstr_insert passed.\n");
}

void test_ckg_cstr_append() {
    char str1[50] = {0};
    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_append(str1, 50, " World!");
    ckg_assert(ckg_str_equal(str1, "Hello World!"));

    char str2[50] = "";
    ckg_cstr_append(str2, 50, "Appended");
    ckg_assert(ckg_str_equal(str2, "Appended"));

    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_append(str1, 50, "");
    ckg_assert(ckg_str_equal(str1, "Hello"));

    CKG_LOG_SUCCESS("Test ckg_cstr_append passed.\n");
}

void test_ckg_cstr_append_char() {
    char str1[50] = {0};
    ckg_cstr_copy(str1, 50, "Hello");
    ckg_cstr_append_char(str1, 50, '!');
    ckg_assert(ckg_str_equal(str1, "Hello!"));

    char str2[50] = "";
    ckg_cstr_append_char(str2, 50, 'A');
    ckg_assert(ckg_str_equal(str2, "A"));

    ckg_cstr_copy(str1, 50, "Hi");
    ckg_cstr_append_char(str1, 50, ' ');
    ckg_cstr_append_char(str1, 50, 'A');
    ckg_cstr_append_char(str1, 50, '!');
    ckg_assert(ckg_str_equal(str1, "Hi A!"));

    CKG_LOG_SUCCESS("Test ckg_cstr_append_char passed.\n");
}

void test_ckg_str_clear() {
    char str1[50] = "Hello";
    ckg_str_clear(str1);
    ckg_assert(ckg_str_equal(str1, ""));

    char str2[50] = "";
    ckg_str_clear(str2);
    ckg_assert(ckg_str_equal(str2, ""));

    CKG_LOG_SUCCESS("Test ckg_str_clear passed.\n");
}

void test_ckg_cstr_copy() {
    char str1[50] = {0};
    ckg_cstr_copy(str1, 50, "Hello!");
    ckg_assert(ckg_str_equal(str1, "Hello!"));

    CKG_LOG_SUCCESS("Test ckg_cstr_copy passed.\n");
}

void test_ckg_str_contains() {
    char* t1 = "hello";
    char* sub_str = ckg_substring(t1, 0, 1);
    ckg_assert(ckg_str_contains(sub_str, "he"));
    ckg_free(sub_str);

    ckg_assert(!ckg_str_contains(t1, ""));
    ckg_assert(ckg_str_contains(t1, "h"));
    ckg_assert(ckg_str_contains(t1, "he"));
    ckg_assert(ckg_str_contains(t1, "o"));
    ckg_assert(!ckg_str_contains(t1, ";;;;;;"));
    ckg_assert(ckg_str_contains(t1, "hello"));
    ckg_assert(!ckg_str_contains(t1, "hllo"));

    CKG_LOG_SUCCESS("Test ckg_str_contains passed.\n");
}

void test_ckg_str_starts_with() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
	ckg_assert(ckg_str_starts_with(sub_str, "he"));
	ckg_free(sub_str);

	ckg_assert(ckg_str_starts_with(t1, "hell"));
	ckg_assert(ckg_str_starts_with(t1, "hello"));
	ckg_assert(!ckg_str_starts_with(t1, "hllo"));
	ckg_assert(!ckg_str_starts_with(t1, ""));


	char* t2 = "";
	ckg_assert(ckg_str_starts_with(t2, ""));
	

	t2 = "f";
	ckg_assert(!ckg_str_starts_with(t2, "g"));
	ckg_assert(ckg_str_starts_with(t2, "f"));

    CKG_LOG_SUCCESS("Test ckg_str_starts_with passed.\n");
}

void test_ckg_str_ends_with() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
	ckg_assert(!ckg_str_ends_with(sub_str, "llo"));
	ckg_free(sub_str);

	ckg_assert(ckg_str_ends_with(t1, ""));
	ckg_assert(ckg_str_ends_with(t1, "lo"));
	ckg_assert(ckg_str_ends_with(t1, "hello"));
	ckg_assert(ckg_str_ends_with(t1, "ello"));

	char* t2 = "";
	ckg_assert(ckg_str_ends_with(t2, ""));
	

	t2 = "f";
	ckg_assert(!ckg_str_ends_with(t2, "g"));
	ckg_assert(ckg_str_ends_with(t2, "f"));

    CKG_LOG_SUCCESS("Test ckg_str_ends_with passed.\n");
}

void test_ckg_str_reverse() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
    char* reversed_string = ckg_str_reverse(sub_str);
	ckg_assert(ckg_str_equal(reversed_string, "eh"));
	ckg_free(sub_str);
	ckg_free(reversed_string);

    char* reversed_string2 = ckg_str_reverse("Chicken");
    char* reversed_string3 = ckg_str_reverse("Roast");
    char* reversed_string4 = ckg_str_reverse("Soup");

	ckg_assert_msg(ckg_str_equal(reversed_string2, "nekcihC"), "test_ckg_str_reverse failed expected: %s | got: %s", "nekcihC", reversed_string2);
	ckg_assert_msg(ckg_str_equal(reversed_string3, "tsaoR"), "test_ckg_str_reverse failed expected: %s | got: %s", "tsaoR", reversed_string3);
	ckg_assert_msg(ckg_str_equal(reversed_string4, "puoS"), "test_ckg_str_reverse failed expected: %s | got: %s", "puoS", reversed_string4);

	ckg_free(reversed_string2);
	ckg_free(reversed_string3);
	ckg_free(reversed_string4);


	char* t2 = "";
    char* reversed_t2 = ckg_str_reverse(t2);
	ckg_assert_msg(ckg_str_equal(reversed_t2, ""), "test_ckg_str_reverse failed expected: %s | got: %s", "", reversed_t2);
    ckg_free(reversed_t2);

	t2 = "f";
    reversed_t2 = ckg_str_reverse(t2);
	ckg_assert_msg(ckg_str_equal(reversed_t2, "f"), "test_ckg_str_reverse failed expected: %s | got: %s", "f", reversed_t2);
	ckg_assert_msg(!ckg_str_equal(reversed_t2, "g"), "test_ckg_str_reverse failed expected: %s | got: %s", "f", reversed_t2);
    ckg_free(reversed_t2);

    CKG_LOG_SUCCESS("Test ckg_str_reverse passed.\n");
}

void test_ckg_str_index_of() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);

	ckg_assert(ckg_str_index_of(sub_str, "he") == 0);
	ckg_free(sub_str);

	ckg_assert(ckg_str_index_of(t1, "") == -1);
	ckg_assert(ckg_str_index_of(t1, "ell") == 1);
	ckg_assert(ckg_str_index_of(t1, "l") == 2);
	ckg_assert(ckg_str_index_of(t1, "o") == 4);
	ckg_assert(ckg_str_index_of(t1, "7") == -1);
	ckg_assert(ckg_str_index_of(t1, "hello") == 0);
	ckg_assert(ckg_str_index_of(t1, "hllo") == -1);

	char* t2 = "";
	ckg_assert(ckg_str_index_of(t2, "") == 0);
	

	t2 = "f";
	ckg_assert(ckg_str_index_of(t2, "g") == -1);
	ckg_assert(ckg_str_index_of(t2, "f") == 0);

    CKG_LOG_SUCCESS("Test test_ckg_str_index_of passed.\n");
}

void test_ckg_string_assertions() {
    char str1[10] = "Overflow";
    ckg_cstr_append(str1, 10, "ingTest");
    ckg_assert(!ckg_str_equal(str1, "OverflowingTest"));

    char str2[6] = "Short";
    ckg_cstr_append_char(str2, 6, 'X');
    ckg_assert(!ckg_str_equal(str2, "ShortX"));
}

void test_ckg_string_edgecases() {
    ckg_assert(ckg_str_length("") == 0);
    ckg_assert(ckg_str_length(NULL));

    // Test edge cases for ckg_str_equal
    ckg_assert(ckg_str_equal(NULL, NULL));
    ckg_assert(!ckg_str_equal("Hello", NULL));
    ckg_assert(!ckg_str_equal(NULL, "Hello"));

    // Test edge cases for ckg_cstr_insert_char
    char str1[50] = "Hello";
    ckg_cstr_insert_char(str1, 50, 'V', 10); // Insert at a position beyond the string length
    ckg_assert(ckg_str_equal(str1, "HelloV"));

    char str2[50] = "";
    ckg_cstr_insert_char(str2, 50, 'Z', 0); // Insert into an empty string
    ckg_assert(ckg_str_equal(str2, "Z"));

    // Test edge cases for ckg_cstr_append
    char str3[50] = "Hello";
    ckg_cstr_append(str3, 50, NULL); // Append a null string
    ckg_assert(ckg_str_equal(str3, "Hello"));

    char str4[50] = "";
    ckg_cstr_append(str4, 50, "Appended"); // Append to an empty string
    ckg_assert(ckg_str_equal(str4, "Appended"));

    CKG_LOG_SUCCESS("Test ckg_string_edgecases passed.\n");

}

void test_ckg_str_operations() { 
    CKG_LOG_PRINT("\n");
    CKG_LOG_DEBUG("======================= Testing String Functions =======================\n");
    test_ckg_str_length();
    test_ckg_string_equal();
    test_ckg_cstr_insert_char();
    test_ckg_cstr_insert();
    test_ckg_cstr_append();
    test_ckg_cstr_append_char();
    test_ckg_str_clear();
    test_ckg_cstr_copy();
    test_ckg_str_contains();
    test_ckg_str_starts_with();
    test_ckg_str_ends_with();
    test_ckg_str_reverse();
    test_ckg_str_index_of();
    // test_ckg_string_edgecases();
    // test_ckg_string_assertions();
    CKG_LOG_DEBUG("======================= String Functions All Passed =======================\n");
    CKG_LOG_PRINT("\n");
}