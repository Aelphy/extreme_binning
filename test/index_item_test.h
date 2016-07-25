// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp  test/index_item_test.h
// g++ -o test/runner -std=c++11 -I/usr/local/Cellar/openssl/1.0.2h_1/include -I../cxxtest-4.4 -lcrypto test/runner.cpp index_item.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../index_item.h"

class IndexItemTest : public CxxTest::TestSuite {
public:
    void test_index_item(void) {

    }
};
