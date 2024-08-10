#pragma once

#include "../ckg_types.h"

//************************* Begin Functions *************************
#ifdef __cplusplus
extern "C" {
#endif
    Boolean ckg_char_is_digit(char c);
    Boolean ckg_char_is_alpha(char c);
    Boolean ckg_char_is_alpha_numeric(char c);
    Boolean ckg_char_is_upper(char c);
    Boolean ckg_char_is_lower(char c);
#ifdef __cplusplus
}
#endif
//************************** End Functions **************************

#if defined(CKG_IMPL)
    Boolean ckg_char_is_digit(char c) {
        return (c >= '0' && c <= '9');
    }

    Boolean ckg_char_is_upper(char c) {
        return (c >= 'A' && c <= 'Z');
    }

    Boolean ckg_char_is_lower(char c) {
        return (c >= 'a' && c <= 'z');
    }

    Boolean ckg_char_is_alpha(char c) {
        return ckg_char_is_lower(c) || ckg_char_is_upper(c) ;
    }

    Boolean ckg_char_is_alpha_numeric(char c) {
        return ckg_char_is_alpha(c) || ckg_char_is_digit(c);
    }
#endif // CKG_IMPL