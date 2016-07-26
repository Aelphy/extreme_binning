// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp test/storage_test.h
// g++ -o test/runner -std=c++11 -I/usr/local/Cellar/openssl/1.0.2h_1/include -I../cxxtest-4.4 -lcrypto test/runner.cpp  storage.cpp bin.cpp chunk.cpp util.cpp
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

        std::string s1 = "test data 1";
        std::string s2 = "test data 2";
        char* s1_c = new char[s1.length()];
        char* s2_c = new char[s2.length()];
        memcpy(s1_c, s1.data(), s1.length());
        memcpy(s2_c, s2.data(), s2.length());

        chunk1->set_data(s1_c, 11);
        chunk2->set_data(s2_c, 11);

        bin->chunks.push_back(chunk1);
        bin->chunks.push_back(chunk2);

        Storage::get_instance()->write(bin, chunk1);
        TS_ASSERT_THROWS(Storage::get_instance()->write(bin, chunk1), OwerwriteException);

        Chunk* chunk3 = Storage::get_instance()->read(bin->get_id(), chunk1->get_id());
        TS_ASSERT_EQUALS(chunk3->get_id(), chunk1->get_id());

        std::string s3(chunk3->get_data(), chunk3->get_length());
        std::string s4(chunk1->get_data(), chunk1->get_length());
        TS_ASSERT_EQUALS(s3, s4);

        Storage::get_instance()->write(bin, chunk2);
        TS_ASSERT_EQUALS(chunk2->get_id(), chunk1->get_length());

        Chunk* chunk4 = Storage::get_instance()->read(bin->get_id(), chunk2->get_id());

        TS_ASSERT_EQUALS(chunk4->get_id(), chunk2->get_id());
        std::string s5(chunk4->get_data(), chunk4->get_length());
        std::string s6(chunk2->get_data(), chunk2->get_length());
        TS_ASSERT_EQUALS(s5, s6);

        TS_ASSERT_EQUALS(Storage::get_instance()->read(-1, -1), nullptr);

        Storage::finalize();
        delete bin;
        delete chunk3;
        delete chunk4;
    }
};
