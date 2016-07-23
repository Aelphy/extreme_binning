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

        std::string s1 = "test data 1";
        std::string s2 = "test data 2";
        char* s1_c = new char[s1.length()];
        char* s2_c = new char[s2.length()];
        memcpy(s1_c, s1.data(), s1.length());
        memcpy(s2_c, s2.data(), s2.length());

        chunk1->set_data(s1_c, 11);
        chunk2->set_data(s2_c, 11);

        bin->chunks.push_back(chunk1);

        storage->write(bin, chunk1);
        TS_ASSERT_THROWS(storage->write(bin, chunk1), OwerwriteException);

        Chunk* chunk3 = storage->read(bin->get_id(), chunk1->get_id());
        TS_ASSERT_EQUALS(chunk3->get_id(), chunk1->get_id());
        TS_ASSERT_EQUALS(chunk3->get_length(), chunk1->get_length());

        std::string s3(chunk3->get_data()), s4(chunk1->get_data());
        TS_ASSERT_EQUALS(s3, s4);

        bin->chunks.push_back(chunk2);
        storage->write(bin, chunk2);
        TS_ASSERT_EQUALS(chunk2->get_id(), chunk1->get_length());

        Chunk* chunk4 = storage->read(bin->get_id(), chunk2->get_id());

        TS_ASSERT_EQUALS(chunk4->get_id(), chunk2->get_id());
        std::string s5(chunk4->get_data()), s6(chunk2->get_data());
        TS_ASSERT_EQUALS(s5, s6);

        TS_ASSERT_EQUALS(storage->read(-1, -1), nullptr);

        storage->finalize();
        delete bin;
        delete chunk3;
        delete chunk4;
    }
};
