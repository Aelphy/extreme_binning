// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp  test/rabin_karp_test.h
// g++ -o test/runner -I../cxxtest-4.4  test/runner.cpp rabin_karp_hasher.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../exceptions.h"

class RabinKarpTest : public CxxTest::TestSuite {
public:

    void test_hash(void) {
    }
};
