// ../cxxtest-4.4/bin/cxxtestgen --have-eh --error-printer -o test/runner.cpp  test/primary_index_test.h
// g++ -o test/runner -std=c++11 -I/usr/local/Cellar/openssl/1.0.2h_1/include -I../cxxtest-4.4 -lcrypto test/runner.cpp bin.cpp chunk.cpp util.cpp storage.cpp primary_index.cpp
// test/runner

#include <cxxtest/TestSuite.h>
#include "../bin.h"
#include "../chunk.h"
#include "../storage.h"
#include "../exceptions.h"
#include "../primary_index.h"

class IndexItemTest : public CxxTest::TestSuite {
public:
    void test_index_item(void) {
        std::string file_name = "file for backup";
        Bin* bin = new Bin();
        Chunk* chunk1 = new Chunk();

        std::string s1 = "test data 1";

        char* s1_c = new char[s1.length()];
        memcpy(s1_c, s1.data(), s1.length());

        chunk1->set_data(s1_c, 11);

        bin->chunks.push_back(chunk1);

        PrimaryIndex* primary_index = new PrimaryIndex(RECEPIE_FILE);

        std::string file_hash = "file hash";

        TS_ASSERT_EQUALS(primary_index->bin_ids_by_file_hash.find(file_hash), primary_index->bin_ids_by_file_hash.end());

        primary_index->insert(file_name, file_hash, bin);
        TS_ASSERT_EQUALS(primary_index->bin_ids_by_file_hash.find(file_hash)->second, bin->get_id());

        Util util;
        util.init_hash();
        util.hash_chunk(chunk1->get_data(), chunk1->get_length());
        util.finish_hash();
        char* hash_c = util.get_result();
        std::string hash(hash_c, SHA256_DIGEST_LENGTH);
        delete hash_c;
        TS_ASSERT_EQUALS(primary_index->bin_ids_by_representative_chunk_hash.find(hash)->second, bin->get_id());

        Bin* loaded_bin = Bin::load(primary_index->bin_ids_by_representative_chunk_hash.find(hash)->second);

        TS_ASSERT_EQUALS(loaded_bin->chunks.size(), bin->chunks.size());

        for (auto existing_chunk : bin->chunks) {
            util.init_hash();
            util.hash_chunk(existing_chunk->get_data(), existing_chunk->get_length());
            util.finish_hash();
            char* existing_hash_c_str = util.get_result();
            std::string existing_hash(existing_hash_c_str, SHA256_DIGEST_LENGTH);
            delete[] existing_hash_c_str;

            bool matched = false;

            for (auto loaded_chunk : loaded_bin->chunks) {
                util.init_hash();
                util.hash_chunk(loaded_chunk->get_data(), loaded_chunk->get_length());
                util.finish_hash();
                char* loaded_hash_c_str = util.get_result();
                std::string loaded_hash(loaded_hash_c_str, SHA256_DIGEST_LENGTH);
                delete[] loaded_hash_c_str;

                if (loaded_hash == existing_hash) {
                    matched = true;
                    break;
                }
            }

            TS_ASSERT_EQUALS(matched, true);
        }

        delete loaded_bin;

        Chunk* chunk2 = new Chunk();

        std::string s2 = "test data 2";

        char* s2_c = new char[s2.length()];
        memcpy(s2_c, s2.data(), s2.length());

        chunk2->set_data(s2_c, 11);

        bin->chunks.push_back(chunk2);

        std::string file2_hash = "file 2 hash";
        primary_index->insert(file_name, file2_hash, bin);
        TS_ASSERT_EQUALS(primary_index->bin_ids_by_file_hash.find(file2_hash), primary_index->bin_ids_by_file_hash.end());

        loaded_bin = Bin::load(primary_index->bin_ids_by_representative_chunk_hash.find(hash)->second);

        TS_ASSERT_EQUALS(loaded_bin->chunks.size(), bin->chunks.size());

        for (auto existing_chunk : bin->chunks) {
            util.init_hash();
            util.hash_chunk(existing_chunk->get_data(), existing_chunk->get_length());
            util.finish_hash();
            char* existing_hash_c_str = util.get_result();
            std::string existing_hash(existing_hash_c_str, SHA256_DIGEST_LENGTH);
            delete[] existing_hash_c_str;

            bool matched = false;

            for (auto loaded_chunk : loaded_bin->chunks) {
                util.init_hash();
                util.hash_chunk(loaded_chunk->get_data(), loaded_chunk->get_length());
                util.finish_hash();
                char* loaded_hash_c_str = util.get_result();
                std::string loaded_hash(loaded_hash_c_str, SHA256_DIGEST_LENGTH);
                delete[] loaded_hash_c_str;

                if (loaded_hash == existing_hash) {
                    matched = true;
                    break;
                }
            }

            TS_ASSERT_EQUALS(matched, true);
        }

        delete loaded_bin;


        Storage::finalize();

        delete bin;
        delete primary_index;
    }
};
