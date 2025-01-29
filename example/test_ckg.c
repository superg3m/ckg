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

    return 0;
}