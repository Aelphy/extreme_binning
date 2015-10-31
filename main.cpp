#include <boost/filesystem.hpp>
#include "primary_index.h"
#include "chunker.h"

#define RECIPE_FILE "./data/recipe_file"

using namespace std;
using namespace boost::filesystem;

int main() {
    string backup_dir = "/Users/Aelphy/Documents/projects/extreme_binning/test_data_dir";
    path p(backup_dir);

    directory_iterator end_itr;

    for (directory_iterator itr(p); itr != end_itr; ++itr) {
        if (is_regular_file(itr->path())) {
            string file_path = itr->path().string();

            Chunker *chunker = new Chunker();
            PrimaryIndex *primary_index = new PrimaryIndex();
            Util *util = Util::get_instance();
            Storage::initialize();

            util->init_hash();
            util->hash_file(file_path);
            util->finish_hash();

            ofstream recipe_file(RECIPE_FILE);

            try {
                primary_index->items_by_file_hash.at(util->get_hash());
                // add information about duplicates to restore_file
            } catch (out_of_range) {
                chunker->init(file_path);
                util->init_hash();
                vector<Chunk *> chunks;

                while (!chunker->eof()) {
                    Chunk *chunk = chunker->get_next_chunk();
                    chunks.push_back(chunk);
                    // write info to recipe file
                }

                chunker->finish();

                //select representative
                // if found get bin and modify it
                // else write new bin
            }

            recipe_file.close();
            delete chunker;
            delete primary_index;
            delete util;
            Storage::finalize();
        }
    }

    return 0;
}