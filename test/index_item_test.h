// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp  test/index_item_test.h
// g++ -o test/runner -std=c++11 -I/usr/local/Cellar/openssl/1.0.2h_1/include -I../cxxtest-4.4 -lcrypto test/runner.cpp index_item.cpp bin.cpp chunk.cpp util.cpp storage.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../index_item.h"
#include "../bin.h"
#include "../chunk.h"
#include "../storage.h"
#include "../exceptions.h"

class IndexItemTest : public CxxTest::TestSuite {
public:
    void test_index_item(void) {
        Bin* bin = new Bin();
        Chunk* chunk1 = new Chunk();

        TS_ASSERT_THROWS(IndexItem("", "", bin->get_id()), BrokenOrderException);

        std::string s1 = "test data 1";

        char* s1_c = new char[s1.length()];
        memcpy(s1_c, s1.data(), s1.length());

        chunk1->set_data(s1_c, 11);

        bin->chunks.push_back(chunk1);

        Storage::get_instance()->write(bin);

        Storage::finalize();

        delete bin;
    }
};
