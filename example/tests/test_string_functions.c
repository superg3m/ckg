#include "../../ckg.h"

void test_ckg_cstr_length() {
    const int expected_size = 5;
    char str1[] = "Hello";
    int actual_size = ckg_cstr_length(str1);
    ckg_assert(actual_size == expected_size, "Test ckg_cstr_length failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_cstr_length passed.\n");
}

void test_ckg_string_equal() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";
    ckg_assert(ckg_str_equal(str1, str2) && !ckg_str_equal(str1, str3), "Test ckg_str_equal failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_str_equal passed.\n");
}

void test_ckg_str_insert_char() {
    char str1[50] = "Hello";
    ckg_str_insert_char(str1, 50, 'V', 2);
    ckg_assert(ckg_str_equal(str1, "HeVllo"), "Test: ckg_str_insert_char -> got: %s | expected %s.\n", str1, "HeVllo");

    CKG_LOG_SUCCESS("Test ckg_str_insert_char passed.\n");
}

void test_ckg_str_insert() {
    char str1[50] = "Hello";
    ckg_str_insert(str1, 50, "|TESTINGS|", 2);
    ckg_assert(ckg_str_equal(str1, "He|TESTINGS|llo"), "Test: ckg_str_insert failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_str_insert passed.\n");
}

void test_ckg_str_append() {
    char str4[50] = {0};
    ckg_str_copy(str4, 50, "Hello");
    ckg_str_append(str4, 50, " World!");
    ckg_assert(ckg_str_equal(str4, "Hello World!"), "Test: ckg_str_append failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_str_append passed.\n");
}

void test_ckg_str_append_char() {
    char str5[50] = {0};

    ckg_str_copy(str5, 50, "Hello");
    ckg_str_append_char(str5, 50, '!');

    ckg_assert(ckg_str_equal(str5, "Hello!"), "Test: ckg_str_append_char failed.\n");
    CKG_LOG_SUCCESS("Test ckg_str_append_char passed.\n");
}

void test_ckg_str_clear() {
    char str1[50] = "Hello";
    ckg_str_clear(str1);
    ckg_assert(ckg_str_equal(str1, ""), "Test: ckg_str_clear failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_str_clear passed.\n");
}

void test_ckg_str_copy() {
    char str1[50] = {0};
    ckg_str_copy(str1, 50, "Hello!");
    ckg_assert(ckg_str_equal(str1, "Hello!"), "Test: ckg_str_copy failed.\n");
    
    CKG_LOG_SUCCESS("Test ckg_str_copy passed.\n");
}

void test_ckg_str_contains() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);

	ckg_assert(ckg_str_contains(sub_str, "he"), "test_ckg_ckg_str_contains failed");
	ckg_free(sub_str);

	ckg_assert(!ckg_str_contains(t1, ""), "test_ckg_ckg_str_contains failed");
	ckg_assert(ckg_str_contains(t1, "h"), "test_ckg_ckg_str_contains failed");
	ckg_assert(ckg_str_contains(t1, "he"), "test_ckg_ckg_str_contains failed");
	ckg_assert(ckg_str_contains(t1, ";;o"), "test_ckg_ckg_str_contains failed");
	ckg_assert(ckg_str_contains(t1, "hello"), "test_ckg_ckg_str_contains failed");
	ckg_assert(!ckg_str_contains(t1, "hllo"), "test_ckg_ckg_str_contains failed");

	char* t2 = "";
	ckg_assert(ckg_str_contains(t2, ""), "test_ckg_ckg_str_contains failed");
	

	t2 = "f";
	ckg_assert(!ckg_str_contains(t2, "g"), "test_ckg_ckg_str_contains failed");
	ckg_assert(ckg_str_contains(t2, "f"), "test_ckg_ckg_str_contains failed");

    CKG_LOG_SUCCESS("Test ckg_ckg_str_contains passed.\n");
}

void test_ckg_str_starts_with() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
	ckg_assert(ckg_str_starts_with(sub_str, "he"), "test_ckg_ckg_str_starts_with failed");
	ckg_free(sub_str);

	ckg_assert(ckg_str_starts_with(t1, "hell"), "test_ckg_ckg_str_starts_with failed");
	ckg_assert(ckg_str_starts_with(t1, "hello"), "test_ckg_ckg_str_starts_with failed");
	ckg_assert(!ckg_str_starts_with(t1, "hllo"), "test_ckg_ckg_str_starts_with failed");
	ckg_assert(!ckg_str_starts_with(t1, ""), "test_ckg_ckg_str_starts_with failed");


	char* t2 = "";
	ckg_assert(ckg_str_starts_with(t2, ""), "test_ckg_ckg_str_starts_with failed");
	

	t2 = "f";
	ckg_assert(!ckg_str_starts_with(t2, "g"), "test_ckg_ckg_str_starts_with failed");
	ckg_assert(ckg_str_starts_with(t2, "f"), "test_ckg_ckg_str_starts_with failed");

    CKG_LOG_SUCCESS("Test ckg_ckg_str_starts_with passed.\n");
}

void test_ckg_str_ends_with() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
	ckg_assert(!ckg_str_ends_with(sub_str, "llo"), "test_ckg_ckg_str_ends_with failed");
	ckg_free(sub_str);

	ckg_assert(ckg_str_ends_with(t1, ""), "test_ckg_ckg_str_ends_with failed");
	ckg_assert(ckg_str_ends_with(t1, "lo"), "test_ckg_ckg_str_ends_with failed");
	ckg_assert(ckg_str_ends_with(t1, "hello"), "test_ckg_ckg_str_ends_with failed");
	ckg_assert(ckg_str_ends_with(t1, "ello"), "test_ckg_ckg_str_ends_with failed");

	char* t2 = "";
	ckg_assert(ckg_str_ends_with(t2, ""), "test_ckg_ckg_str_ends_with failed");
	

	t2 = "f";
	ckg_assert(!ckg_str_ends_with(t2, "g"), "test_ckg_ckg_str_ends_with failed");
	ckg_assert(ckg_str_ends_with(t2, "f"), "test_ckg_ckg_str_ends_with failed");

    CKG_LOG_SUCCESS("Test ckg_ckg_str_ends_with passed.\n");
}

void test_ckg_str_reverse() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);
    char* reversed_string = ckg_str_reverse(sub_str);
	ckg_assert(ckg_str_equal(reversed_string, "eh"), "test_ckg_ckg_str_reverse failed");
	ckg_free(sub_str);
	ckg_free(reversed_string);

    char* reversed_string2 = ckg_str_reverse("Chicken");
    char* reversed_string3 = ckg_str_reverse("Roast");
    char* reversed_string4 = ckg_str_reverse("Soup");

	ckg_assert(ckg_str_equal(reversed_string2, "nekcihC"), "test_ckg_ckg_str_reverse failed expected: %s | got: %s", "nekcihC", reversed_string2);
	ckg_assert(ckg_str_equal(reversed_string3, "tsaoR"), "test_ckg_ckg_str_reverse failed expected: %s | got: %s", "tsaoR", reversed_string3);
	ckg_assert(ckg_str_equal(reversed_string4, "puoS"), "test_ckg_ckg_str_reverse failed expected: %s | got: %s", "puoS", reversed_string4);

	ckg_free(reversed_string2);
	ckg_free(reversed_string3);
	ckg_free(reversed_string4);


	char* t2 = "";
    char* reversed_t2 = ckg_str_reverse(t2);
	ckg_assert(ckg_str_equal(reversed_t2, ""), "test_ckg_ckg_str_reverse failed expected: %s | got: %s", "", reversed_t2);
    ckg_free(reversed_t2);

	t2 = "f";
    reversed_t2 = ckg_str_reverse(t2);
	ckg_assert(ckg_str_equal(reversed_t2, "f"), "test_ckg_ckg_str_reverse failed expected: %s | got: %s", "f", reversed_t2);
	ckg_assert(!ckg_str_equal(reversed_t2, "g"), "test_ckg_ckg_str_reverse failed expected: %s | got: %s", "f", reversed_t2);
    ckg_free(reversed_t2);

    CKG_LOG_SUCCESS("Test ckg_ckg_str_reverse passed.\n");
}

void test_ckg_str_index_of() {
    char* t1 = "hello";
	char* sub_str = ckg_substring(t1, 0, 1);

	ckg_assert(ckg_str_index_of(sub_str, "he") == 0, "test_ckg_str_index_of failed");
	ckg_free(sub_str);

	ckg_assert(ckg_str_index_of(t1, "") == -1, "test_ckg_str_index_of failed");
	ckg_assert(ckg_str_index_of(t1, "ell") == 1, "test_ckg_str_index_of failed");
	ckg_assert(ckg_str_index_of(t1, "l") == 2, "test_ckg_str_index_of failed");
	ckg_assert(ckg_str_index_of(t1, "o") == 4, "test_ckg_str_index_of failed");
	ckg_assert(ckg_str_index_of(t1, "7") == -1, "test_ckg_str_index_of failed");
	ckg_assert(ckg_str_index_of(t1, "hello") == 0, "test_ckg_str_index_of failed");
	ckg_assert(ckg_str_index_of(t1, "hllo") == -1, "test_ckg_str_index_of failed");

	char* t2 = "";
	ckg_assert(ckg_str_index_of(t2, "") == 0, "test_ckg_str_index_of failed");
	

	t2 = "f";
	ckg_assert(ckg_str_index_of(t2, "g") == -1, "test_ckg_str_index_of failed");
	ckg_assert(ckg_str_index_of(t2, "f") == 0, "test_ckg_str_index_of failed");

    CKG_LOG_SUCCESS("Test test_ckg_str_index_of passed.\n");
}

void test_ckg_str_operations() { 
    CKG_LOG_PRINT("\n");
    CKG_LOG_DEBUG("======================= Testing String Functions =======================\n");
    test_ckg_cstr_length();
    test_ckg_string_equal();
    test_ckg_str_insert_char();
    test_ckg_str_insert();
    test_ckg_str_append();
    test_ckg_str_append_char();
    test_ckg_str_clear();
    test_ckg_str_copy();
    test_ckg_str_contains();
    test_ckg_str_starts_with();
    test_ckg_str_ends_with();
    test_ckg_str_reverse();
    test_ckg_str_index_of();
    test_ckg_str_reverse();
    CKG_LOG_DEBUG("======================= String Functions All Passed =======================\n");
    CKG_LOG_PRINT("\n");
}