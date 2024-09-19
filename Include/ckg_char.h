#pragma once

#include "./ckg_types.h"

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