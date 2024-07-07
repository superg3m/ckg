#include "../../ckg.h"

void test_ckg_math() {
    s32 a = -5;
    s64 b = -8;

    float at = -5.0;
    double bt = -6.13;

    CKG_LOG_DEBUG("MATH TEST: %d\n", abs(a));
    CKG_LOG_DEBUG("MATH TEST: %lld\n", fabs(b));

    // CKG_LOG_DEBUG("MATH TEST: %f\n", ckg_f32_abs(at));
    // CKG_LOG_DEBUG("MATH TEST: %llf\n", ckg_f64_abs(bt));
}