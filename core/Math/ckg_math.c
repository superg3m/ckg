#include "./ckg_math.h"
#include "../Logger/ckg_logger.h"
#include "../Assert/ckg_assert.h"

typedef union {
    float f;
    s32 i;
} FloatIntUnion;

typedef union {
    double d;
    s64 i;
} DoubleLongUnion;

#define S32_SIGN_BIT (s32)(1 << 31)
#define S64_SIGN_BIT (s64)(1LL << 61)

#define F32_SIGN_BIT (float)(1 << 31)
#define F64_SIGN_BIT (double)(1LL << 61)
    
float ckg_f32_abs(float val) {
    ckg_assert_msg(FALSE, "NOT IMPLEMENTED YET!\n");
    FloatIntUnion ret;
    ret.f = val;
    ret.i = ckg_s32_abs(ret.i);
    return ret.f;
}

double ckg_f64_abs(double val) {
    ckg_assert_msg(FALSE, "NOT IMPLEMENTED YET!\n");
    DoubleLongUnion ret;
    ret.d = val;
    ret.i = ckg_s32_abs(ret.i);
    return ret.d;
}

// Date: July 05, 2024
// TODO(Jovanni): Ensure that this is bullet proof
// I highly, highly doubt this is the correct way to do this
s32 ckg_s32_abs(s32 val) {
    return ~(val - 1);
}

s64 ckg_s64_abs(s64 val) {
    return ~(val - 1);
}
