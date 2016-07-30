#include <boost/filesystem.hpp>
#include "primary_index.h"
#include "chunker.h"

int main() {
    std::string backup_data_dir = "/Users/Aelphy/Documents/projects/extreme_binning/test_data";
    boost::filesystem::path p(backup_data_dir);

    boost::filesystem::directory_iterator end_itr;
    Chunker chunker;
    PrimaryIndex* primary_index = new PrimaryIndex(RECEPIE_FILE);
    Util util;

    for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr) {
        if (is_regular_file(itr->path())) {
            std::string file_path = itr->path().string();
            Bin* bin = new Bin();
            chunker.init(file_path);

            while (!chunker.eof()) {
                bin->chunks.push_back(chunker.get_next_chunk(D, r));
            }

            util.init_hash();
            util.hash_file(file_path);
            util.finish_hash();

            char* file_hash_c_str = util.get_result();
            std::string file_hash(file_hash_c_str, SHA256_DIGEST_LENGTH);
            delete file_hash_c_str;

            primary_index->insert(file_path, file_hash, bin);
            chunker.finish();
            delete bin;
        }
    }

    Storage::get_instance()->finalize();
    delete primary_index;

    return 0;
}