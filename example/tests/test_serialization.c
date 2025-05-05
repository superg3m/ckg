#include "../../ckg.h"

void test_serialization() {
    const char* filename = "test_serialization.txt";

    char** original_vec = NULL;

    ckg_vector_push(original_vec, ckg_cstr_alloc(CKG_LIT_ARG("hello")));
    ckg_vector_push(original_vec, ckg_cstr_alloc(CKG_LIT_ARG("world")));
    ckg_vector_push(original_vec, ckg_cstr_alloc(CKG_LIT_ARG("!")));

    FILE* out = fopen(filename, "wb");
    ckg_assert(out);
    ckg_serialize_collection(original_vec, out, CKG_COLLECTION_VECTOR, CKG_DATA_TYPE_ASCII);
    fclose(out);

    FILE* in = fopen(filename, "rb");
    ckg_assert(in);
    char** deserialized_vec = ckg_deserialize_collection(in, CKG_COLLECTION_VECTOR, CKG_DATA_TYPE_ASCII);
    fclose(in);

    size_t original_size = ckg_vector_count(original_vec);
    size_t deserialized_size = ckg_vector_count(deserialized_vec);
    ckg_assert(original_size == deserialized_size);

    for (size_t i = 0; i < original_size; i++) {
        char* orig = original_vec[i];
        char* deser = deserialized_vec[i];
        ckg_assert(ckg_str_equal(orig, original_size, deser, deserialized_size));
    }

    ckg_vector_free(original_vec);
    ckg_vector_free(deserialized_vec);
    printf("✅ test_serialization passed\n");
}