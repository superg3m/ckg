#include "../../ckg.h"

void test_serialization() {
    const char* filename = "test_serialization.txt";

    CKG_StringView* original_vec = NULL;

    ckg_vector_push(original_vec, CKG_SV_LIT("hello"));
    ckg_vector_push(original_vec, CKG_SV_LIT("world"));
    ckg_vector_push(original_vec, CKG_SV_LIT("!"));

    FILE* out = fopen(filename, "wb");
    ckg_assert(out);
    ckg_serialize_collection(original_vec, out, CKG_COLLECTION_VECTOR, CKG_DATA_TYPE_STRING_VIEW);
    fclose(out);

    FILE* in = fopen(filename, "rb");
    ckg_assert(in);
    CKG_StringView* deserialized_vec = ckg_deserialize_collection(in, CKG_COLLECTION_VECTOR, CKG_DATA_TYPE_STRING_VIEW);
    fclose(in);

    size_t original_size = ckg_vector_count(original_vec);
    size_t deserialized_size = ckg_vector_count(deserialized_vec);
    ckg_assert(original_size == deserialized_size);

    for (size_t i = 0; i < original_size; i++) {
        CKG_StringView orig = original_vec[i];
        CKG_StringView deser = deserialized_vec[i];
        ckg_assert(ckg_str_equal(orig.data, orig.length, deser.data, deser.length));
    }

    for (int i = 0; i < ckg_vector_count(deserialized_vec); i++) {
        char* str = (char*)deserialized_vec[i].data;
        ckg_free(str);
    }

    ckg_vector_free(original_vec);
    ckg_vector_free(deserialized_vec);
    CKG_LOG_SUCCESS("test_serialization passed\n");
}