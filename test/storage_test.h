// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp test/storage_test.h
// g++ -o test/runner -std=c++11 -I../cxxtest-4.4 test/runner.cpp  storage.cpp bin.cpp chunk.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../storage.h"
#include "../exceptions.h"

class StorageTest : public CxxTest::TestSuite {
public:
    void test_storage_read_write(void) {
        Bin* bin = new Bin();
        Chunk* chunk1 = new Chunk();
        Chunk* chunk2 = new Chunk();
        Storage* storage = Storage::get_instance();
        storage->initialize();

        TS_ASSERT_EQUALS(bin->get_id(), -1);

        std::string s1 = "test data 1";
        std::string s2 = "test data 2";

        chunk1->set_data(s1.data(), 11);
        chunk2->set_data(s2.data(), 11);

        bin->chunks.push_back(chunk1);

        TS_ASSERT_EQUALS(storage->write(bin, chunk1), 0);
        TS_ASSERT_THROWS(storage->write(bin, chunk1), OwerwriteException);

        Chunk* chunk3 = storage->read(bin->get_id(), chunk1->get_id());
        TS_ASSERT_EQUALS(chunk3->get_id(), chunk1->get_id());
        TS_ASSERT_EQUALS(chunk3->get_length(), chunk1->get_length());

        storage->finalize();
        delete storage;
        delete bin;
        delete chunk2;
        delete chunk3;
    }
};