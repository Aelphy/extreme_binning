// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp  test/util_test.h
// g++ -o test/runner -std=c++11 -I/usr/local/Cellar/openssl/1.0.2h_1/include -I../cxxtest-4.4 -lcrypto test/runner.cpp util.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../util.h"

class UtilTest : public CxxTest::TestSuite {
 public:
    void test_hashing(void) {
        Util* util = new Util();
        const char data[] = "Test data 1";
        unsigned char result[SHA256_DIGEST_LENGTH];
        SHA256_CTX context;

        util->init_hash();
        util->hash_chunk(data, 11);
        util->finish_hash();

        SHA256_Init(&context);
        SHA256_Update(&context, data, 11);
        SHA256_Final(result, &context);

        char* tmp1 = util->get_result();
        char tmp2[SHA256_DIGEST_LENGTH + 1];
        memcpy(tmp2, result, SHA256_DIGEST_LENGTH);
        tmp2[SHA256_DIGEST_LENGTH] = 0;

        std::string s1(tmp1);
        std::string s2(tmp2);

        TS_ASSERT_EQUALS(s1, s2);

        delete util;
        delete tmp1;
    }
};
