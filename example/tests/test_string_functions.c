#include "../../ckg.h"

void test_cstring_length() {
    const int expected_size = 5;
    char str1[] = "Hello";
    int actual_size = cstring_length(str1);
    ckg_assert(actual_size == expected_size, "Test cstring_length failed.\n");
    
    CKG_LOG_SUCCESS("Test cstring_length passed.\n");
}

void test_string_compare() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";
    ckg_assert(ckg_string_equal(str1, str2) && !ckg_string_equal(str1, str3), "Test ckg_string_equal failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_string_equal passed.\n");
}

void test_ckg_string_insert_char() {
    char str1[50] = "Hello";
    ckg_string_insert_char(str1, 50, 'V', 2);
    ckg_assert(ckg_string_equal(str1, "HeVllo"), "Test: ckg_string_insert_char -> got: %s | expected %s.\n", str1, "HeVllo");

    CKG_LOG_SUCCESS("Test ckg_string_insert_char passed.\n");
}

void test_ckg_string_insert() {
    char str1[50] = "Hello";
    ckg_string_insert(str1, 50, "|TESTINGS|", 2);
    ckg_assert(ckg_string_equal(str1, "He|TESTINGS|llo"), "Test: ckg_string_insert failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_string_insert passed.\n");
}

void test_ckg_string_append() {
    char str4[50] = {0};
    ckg_string_copy(str4, 50, "Hello");
    ckg_string_append(str4, 50, " World!");
    ckg_assert(ckg_string_equal(str4, "Hello World!"), "Test: ckg_string_append failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_string_append passed.\n");
}

void test_ckg_string_append_char() {
    char str5[50] = {0};

    ckg_string_copy(str5, 50, "Hello");
    ckg_string_append_char(str5, 50, '!');

    ckg_assert(ckg_string_equal(str5, "Hello!"), "Test: ckg_string_append_char failed.\n");
    CKG_LOG_SUCCESS("Test ckg_string_append_char passed.\n");
}

void test_ckg_string_clear() {
    char str1[50] = "Hello";
    ckg_string_clear(str1);
    ckg_assert(ckg_string_equal(str1, ""), "Test: ckg_string_clear failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_string_clear passed.\n");
}

void test_ckg_string_copy() {
    char str1[50] = {0};
    ckg_string_copy(str1, 50, "Hello!");
    ckg_assert(ckg_string_equal(str1, "Hello!"), "Test: ckg_string_copy failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_string_copy passed.\n");
}

void test_ckg_string_contains() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);

	ckg_assert(ckg_string_contains(sub_str, "he"), "test_ckg_ckg_string_contains failed");
	ckg_free(sub_str);

	ckg_assert(!ckg_string_contains(t1, ""), "test_ckg_ckg_string_contains failed");
	ckg_assert(ckg_string_contains(t1, "ell"), "test_ckg_ckg_string_contains failed");
	ckg_assert(ckg_string_contains(t1, "hello"), "test_ckg_ckg_string_contains failed");
	ckg_assert(!ckg_string_contains(t1, "hllo"), "test_ckg_ckg_string_contains failed");

	char* t2 = "";
	ckg_assert(ckg_string_contains(t2, ""), "test_ckg_ckg_string_contains failed");
	

	t2 = "f";
	ckg_assert(!ckg_string_contains(t2, "g"), "test_ckg_ckg_string_contains failed");
	ckg_assert(ckg_string_contains(t2, "f"), "test_ckg_ckg_string_contains failed");

    CKG_LOG_SUCCESS("Test ckg_ckg_string_contains passed.\n");
}

void test_ckg_string_starts_with() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
	ckg_assert(ckg_string_starts_with(sub_str, "he"), "test_ckg_ckg_string_starts_with failed");
	ckg_free(sub_str);

	ckg_assert(ckg_string_starts_with(t1, "hell"), "test_ckg_ckg_string_starts_with failed");
	ckg_assert(ckg_string_starts_with(t1, "hello"), "test_ckg_ckg_string_starts_with failed");
	ckg_assert(!ckg_string_starts_with(t1, "hllo"), "test_ckg_ckg_string_starts_with failed");
	ckg_assert(!ckg_string_starts_with(t1, ""), "test_ckg_ckg_string_starts_with failed");


	char* t2 = "";
	ckg_assert(ckg_string_starts_with(t2, ""), "test_ckg_ckg_string_starts_with failed");
	

	t2 = "f";
	ckg_assert(!ckg_string_starts_with(t2, "g"), "test_ckg_ckg_string_starts_with failed");
	ckg_assert(ckg_string_starts_with(t2, "f"), "test_ckg_ckg_string_starts_with failed");

    CKG_LOG_SUCCESS("Test ckg_ckg_string_starts_with passed.\n");
}

void test_ckg_string_ends_with() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
	ckg_assert(!ckg_string_ends_with(sub_str, "llo"), "test_ckg_ckg_string_ends_with failed");
	ckg_free(sub_str);

	ckg_assert(ckg_string_ends_with(t1, ""), "test_ckg_ckg_string_ends_with failed");
	ckg_assert(ckg_string_ends_with(t1, "lo"), "test_ckg_ckg_string_ends_with failed");
	ckg_assert(ckg_string_ends_with(t1, "hello"), "test_ckg_ckg_string_ends_with failed");
	ckg_assert(ckg_string_ends_with(t1, "ello"), "test_ckg_ckg_string_ends_with failed");

	char* t2 = "";
	ckg_assert(ckg_string_ends_with(t2, ""), "test_ckg_ckg_string_ends_with failed");
	

	t2 = "f";
	ckg_assert(!ckg_string_ends_with(t2, "g"), "test_ckg_ckg_string_ends_with failed");
	ckg_assert(ckg_string_ends_with(t2, "f"), "test_ckg_ckg_string_ends_with failed");

    CKG_LOG_SUCCESS("Test ckg_ckg_string_ends_with passed.\n");
}

void test_ckg_string_reverse() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
    char* reversed_string = ckg_string_reverse(sub_str);
	ckg_assert(ckg_string_equal(reversed_string, "eh"), "test_ckg_ckg_string_reverse failed");
	ckg_free(sub_str);
	ckg_free(reversed_string);

    char* reversed_string2 = ckg_string_reverse("Chicken");
    char* reversed_string3 = ckg_string_reverse("Roast");
    char* reversed_string4 = ckg_string_reverse("Soup");

	ckg_assert(ckg_string_equal(reversed_string2, "nekcihC"), "test_ckg_ckg_string_reverse failed expected: %s | got: %s", "nekcihC", reversed_string2);
	ckg_assert(ckg_string_equal(reversed_string3, "tsaoR"), "test_ckg_ckg_string_reverse failed expected: %s | got: %s", "tsaoR", reversed_string3);
	ckg_assert(ckg_string_equal(reversed_string4, "puoS"), "test_ckg_ckg_string_reverse failed expected: %s | got: %s", "puoS", reversed_string4);

	ckg_free(reversed_string2);
	ckg_free(reversed_string3);
	ckg_free(reversed_string4);


	char* t2 = "";
    char* reversed_t2 = ckg_string_reverse(t2);
	ckg_assert(ckg_string_equal(reversed_t2, ""), "test_ckg_ckg_string_reverse failed expected: %s | got: %s", "", reversed_t2);
    ckg_free(reversed_t2);

	t2 = "f";
    reversed_t2 = ckg_string_reverse(t2);
	ckg_assert(ckg_string_equal(reversed_t2, "f"), "test_ckg_ckg_string_reverse failed expected: %s | got: %s", "f", reversed_t2);
	ckg_assert(!ckg_string_equal(reversed_t2, "g"), "test_ckg_ckg_string_reverse failed expected: %s | got: %s", "f", reversed_t2);
    ckg_free(reversed_t2);

    CKG_LOG_SUCCESS("Test ckg_ckg_string_reverse passed.\n");
}

void test_ckg_string_index_of() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);

	ckg_assert(ckg_string_index_of(sub_str, "he") == 0, "test_ckg_string_index_of failed");
	ckg_free(sub_str);

	ckg_assert(ckg_string_index_of(t1, "") == -1, "test_ckg_string_index_of failed");
	ckg_assert(ckg_string_index_of(t1, "ell") == 1, "test_ckg_string_index_of failed");
	ckg_assert(ckg_string_index_of(t1, "l") == 2, "test_ckg_string_index_of failed");
	ckg_assert(ckg_string_index_of(t1, "hello") == 0, "test_ckg_string_index_of failed");
	ckg_assert(ckg_string_index_of(t1, "hllo") == -1, "test_ckg_string_index_of failed");

	char* t2 = "";
	ckg_assert(ckg_string_index_of(t2, "") == 0, "test_ckg_string_index_of failed");
	

	t2 = "f";
	ckg_assert(ckg_string_index_of(t2, "g") == -1, "test_ckg_string_index_of failed");
	ckg_assert(ckg_string_index_of(t2, "f") == 0, "test_ckg_string_index_of failed");

    CKG_LOG_SUCCESS("Test test_ckg_string_index_of passed.\n");
}

void test_ckg_string_operations() { 
    CKG_LOG_PRINT("\n");
    CKG_LOG_DEBUG("======================= Testing String Functions =======================\n");
    test_cstring_length();
    test_string_compare();
    test_ckg_string_insert_char();
    test_ckg_string_insert();
    test_ckg_string_append();
    test_ckg_string_append_char();
    test_ckg_string_clear();
    test_ckg_string_copy();
    test_ckg_string_contains();
    test_ckg_string_starts_with();
    test_ckg_string_ends_with();
    test_ckg_string_reverse();
    test_ckg_string_index_of();
    test_ckg_string_reverse();
    CKG_LOG_DEBUG("======================= String Functions All Passed =======================\n");
    CKG_LOG_PRINT("\n");
}
