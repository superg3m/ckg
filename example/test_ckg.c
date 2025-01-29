#include "../ckg.h"

#include "./tests/test_string_functions.c"

int main() {
    // The goal is the never worry about null terminator

    char* str = "---- HEY_YOU ----";

    CKG_StringView s1 = ckg_strview_create(str, 5, 12);
    CKG_StringView s2 = CKG_SV_LIT("HEY_YOU");

    ckg_assert(ckg_strview_equal(s1, s2));
    ckg_assert(ckg_cstr_contains(CKG_SV_ARG(s1), CKG_SV_ARG(s2)));
    

    CKG_LOG_PRINT("HELLO: %s\n", ckg_strview_to_cstr(s1));
    CKG_LOG_PRINT("HELLO: %lld\n", ckg_cstr_index_of(CKG_SV_ARG(s1), CKG_LIT_ARG("HEY_YOU")));

    test_ckg_cstr_length();
    test_ckg_string_equal();
    test_ckg_cstr_insert_char();

    return 0;
}