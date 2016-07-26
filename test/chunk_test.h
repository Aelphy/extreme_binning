// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp  test/chunk_test.h
// g++ -o test/runner -std=c++11 -I/usr/local/Cellar/openssl/1.0.2h_1/include -I../cxxtest-4.4 -lcrypto test/runner.cpp storage.cpp bin.cpp chunk.cpp util.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../bin.h"
#include "../storage.h"
#include "../chunk.h"
#include "../exceptions.h"

class ChunkTest : public CxxTest::TestSuite {
public:
    void test_creation(void) {
        Chunk* chunk = new Chunk();
        Bin* bin = new Bin();

        TS_ASSERT_EQUALS(chunk->get_id(), -1);

        Storage* storage = Storage::get_instance();

        std::string s1 = "test data 1";
        char* s1_c = new char[s1.length()];
        memcpy(s1_c, s1.data(), s1.length());
        chunk->set_data(s1_c, 11);

        storage->write(bin, chunk);
        TS_ASSERT_EQUALS(chunk->get_id(), 0);

        storage->finalize();
        delete bin;
        delete chunk;
    }

    void test_load(void) {
        Chunk* chunk = new Chunk();
        Bin* bin = new Bin();

        Storage* storage = Storage::get_instance();

        std::string s1 = "test data 1";
        char* s1_c = new char[s1.length()];
        memcpy(s1_c, s1.data(), s1.length());
        chunk->set_data(s1_c, 11);

        storage->write(bin, chunk);

        Chunk* chunk2 = Chunk::load(bin->get_id(), chunk->get_id());
        TS_ASSERT_EQUALS(chunk2->get_id(), chunk->get_id());
        TS_ASSERT_EQUALS(chunk2->get_length(), chunk->get_length());

        TS_ASSERT_EQUALS(Chunk::load(bin->get_id(), -1), nullptr);

        storage->finalize();
        delete bin;
        delete chunk;
        delete chunk2;
    }
};
