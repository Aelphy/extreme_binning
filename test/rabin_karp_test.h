// ../cxxtest-4.4/bin/cxxtestgen --error-printer -o test/runner.cpp  test/rabin_karp_test.h
// g++ -o test/runner -I../cxxtest-4.4  test/runner.cpp rabin_karp_hasher.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include <math.h>
#include "../rabin_karp_hasher.h"

class RabinKarpTest : public CxxTest::TestSuite {
public:
    long long int hash(const std::string &s) {
        RabinKarpHasher hasher;
        std::vector<char> test_data(s.begin(), s.end());

        hasher.init(&test_data);

        return hasher.get_hash();
    }

    void test_hash(void) {
        TS_ASSERT_EQUALS(hash("\0"), 0);
        TS_ASSERT_EQUALS(hash("\1"), 1);
        TS_ASSERT_EQUALS(hash("1"), 49);
        TS_ASSERT_EQUALS(hash("\1\1"), 256 + 1);
        TS_ASSERT_EQUALS(hash("\1\1\1\1\1\1\1\1"), 1 + pow(256, 1)
                                                   + pow(256, 2)
                                                   + pow(256, 3)
                                                   + pow(256, 4)
                                                   + pow(256, 5)
                                                   + pow(256, 6)
                                                   + pow(256, 7));
        TS_ASSERT_EQUALS(hash("\3"), hash("\1") + hash("\2"));

    }
};
