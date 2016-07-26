// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp  test/bin_test.h
// g++ -o test/runner -std=c++11 -I/usr/local/Cellar/openssl/1.0.2h_1/include -I../cxxtest-4.4 -lcrypto test/runner.cpp storage.cpp bin.cpp chunk.cpp util.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../bin.h"
#include "../storage.h"
#include "../chunk.h"
#include "../exceptions.h"

class BinTest : public CxxTest::TestSuite {
public:
    void test_creation(void) {
        Chunk* chunk1 = new Chunk();
        Chunk* chunk2 = new Chunk();
        Chunk* chunk3 = new Chunk();
        Chunk* chunk4 = new Chunk();
        Bin* bin1 = new Bin();
        Bin* bin2 = new Bin();

        TS_ASSERT_EQUALS(bin1->get_id(), -1);
        TS_ASSERT_EQUALS(bin2->get_id(), -1);

        Storage* storage = Storage::get_instance();

        std::string s1 = "test data 1";
        std::string s2 = "test data 2";
        std::string s3 = "test data 3";
        std::string s4 = "test data 4";

        char* s1_c = new char[s1.length()];
        char* s2_c = new char[s2.length()];
        char* s3_c = new char[s3.length()];
        char* s4_c = new char[s4.length()];
        memcpy(s1_c, s1.data(), s1.length());
        memcpy(s2_c, s2.data(), s2.length());
        memcpy(s3_c, s3.data(), s3.length());
        memcpy(s4_c, s4.data(), s4.length());

        chunk1->set_data(s1_c, 11);
        chunk2->set_data(s2_c, 11);
        chunk3->set_data(s3_c, 11);
        chunk4->set_data(s4_c, 11);

        bin1->chunks.push_back(chunk1);
        bin1->chunks.push_back(chunk2);
        bin2->chunks.push_back(chunk3);
        bin2->chunks.push_back(chunk4);

        storage->write(bin1);
        TS_ASSERT_EQUALS(bin1->get_id(), 0);

        storage->write(bin2);
        int chunk_entry_size = sizeof(chunk1->get_id()) + sizeof(chunk1->get_length()) + sizeof(bin2->get_id());
        TS_ASSERT_EQUALS(bin2->get_id(), 2 * chunk_entry_size);

        Bin* bin3 = Bin::load(bin1->get_id());
        TS_ASSERT_EQUALS(bin3->get_id(), bin1->get_id());
        TS_ASSERT_EQUALS(bin3->chunks.size(), bin1->chunks.size());

        storage->finalize();
        delete bin1;
        delete bin2;
        delete bin3;
    }

    void test_get_representative_chunk(void) {
        Chunk* chunk1 = new Chunk();
        Chunk* chunk2 = new Chunk();
        Bin* bin = new Bin();

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

        Chunk* representative = bin->get_representative_chunk();
        TS_ASSERT_EQUALS(chunk1, representative); // impirical fact

        Chunk* chunk3 = new Chunk();
        Chunk* chunk4 = new Chunk();
        Bin* bin1 = new Bin();

        std::string s3 = "test data 2";
        std::string s4 = "test data 1";

        char* s3_c = new char[s3.length()];
        char* s4_c = new char[s4.length()];
        memcpy(s3_c, s3.data(), s3.length());
        memcpy(s4_c, s4.data(), s4.length());

        chunk3->set_data(s3_c, 11);
        chunk4->set_data(s4_c, 11);

        bin1->chunks.push_back(chunk3);
        bin1->chunks.push_back(chunk4);

        Chunk* representative1 = bin1->get_representative_chunk();
        TS_ASSERT_EQUALS(chunk4, representative1); // impirical fact

        delete bin;
        delete bin1;
    }
};
