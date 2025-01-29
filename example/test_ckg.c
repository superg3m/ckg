#include "../ckg.h"

#include "./tests/test_string_functions.c"

int main() {
    // The goal is the never worry about null terminator

    test_ckg_str_operations();

    return 0;
}