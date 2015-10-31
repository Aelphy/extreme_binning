#include <boost/filesystem.hpp>
#include "primary_index.h"
#include "chunker.h"

#define RECIPE_FILE "./data/recipe_file"

using namespace std;
using namespace boost::filesystem;

int hash_cmp(unsigned char hash1[MD5_DIGEST_LENGTH], unsigned char hash2[MD5_DIGEST_LENGTH]) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        if (hash1[i] < hash2[i]) {
            return -1;
        }

        if (hash1[i] > hash2[i]) {
            return 1;
        }
    }

    return 0;
}

int main() {
    string backup_dir = "/Users/Aelphy/Documents/projects/extreme_binning/test_data";
    path p(backup_dir);

    directory_iterator end_itr;
    Chunker *chunker = new Chunker();
    PrimaryIndex *primary_index = new PrimaryIndex();
    Util *util = Util::get_instance();
    Storage::initialize();
    fstream recipe_file(RECIPE_FILE);


    for (directory_iterator itr(p); itr != end_itr; ++itr) {
        if (is_regular_file(itr->path())) {
            string file_path = itr->path().string();

            util->init_hash();
            util->hash_file(file_path);
            util->finish_hash();
            const unsigned char * file_hash = util->get_result();

            auto item = primary_index->items_by_file_hash.find(file_hash);

            if (item == primary_index->items_by_file_hash.end()) {
                chunker->init(file_path);
                util->init_hash();
                vector<Chunk *> chunks;
                Chunk *chunk;
                unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH];

                if (!chunker->eof()) {
                    chunk = chunker->get_next_chunk();
                    chunks.push_back(chunk);
                    util->init_hash();
                    util->hash_chunk(chunk->data, chunk->length);
                    util->finish_hash();
                    memcpy(representative_chunk_hash, util->get_result(), MD5_DIGEST_LENGTH);
                    // write info to recipe file
                }

                while (!chunker->eof()) {
                    chunk = chunker->get_next_chunk();
                    chunks.push_back(chunk);
                    util->init_hash();
                    util->hash_chunk(chunk->data, chunk->length);
                    util->finish_hash();

                    if (hash_cmp(util->get_result(), representative_chunk_hash) == -1) {
                        memcpy(representative_chunk_hash, util->get_result(), MD5_DIGEST_LENGTH);
                    }
                    // write info to recipe file
                }

                chunker->finish();

                Bin *bin = primary_index->add(file_hash, representative_chunk_hash);

                if (bin != nullptr) {
                    if (!bin->existing) {
                        for (auto chunk : chunks) {
                            bin->chunks[chunk] = chunk->length;
                        }

                        bin->save();
                    } else {
                        vector<Chunk *> delta;

                        for (auto chunk : chunks) {
                            try {
                                bin->chunks.at(chunk);
                            } catch (std::out_of_range) {
                                delta.push_back(chunk);
                            }
                        }

                        bin->update(delta);
                    }
                }

                delete bin;
            } else {
                // write info about duplicates to recipe file
            }
        }
    }

    recipe_file.close();
    delete chunker;
    delete primary_index;
    delete util;
    Storage::finalize();

    return 0;
}