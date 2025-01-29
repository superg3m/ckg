#include "../ckg.h"

#include "./tests/test_string_functions.c"

int main() {
    // The goal is the never worry about null terminator

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

    return 0;
}