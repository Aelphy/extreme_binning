//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_PRIMARY_INDEX_H
#define EXTREME_BINNING_PRIMARY_INDEX_H

#endif //EXTREME_BINNING_PRIMARY_INDEX_H

#include <unordered_map>
#include "bin.h"

#define RECEPIE_FILE "./data/recepie_file"

class PrimaryIndex {
 public:
    PrimaryIndex(std::string file_path);
    ~PrimaryIndex();
    std::unordered_map <std::string, long long int> bin_ids_by_file_hash;
    std::unordered_map <std::string, long long int> bin_ids_by_representative_chunk_hash;
    void insert(std::string file_name,
                std::string file_hash,
                Bin* bin);
 private:
    std::ofstream recipe_file_;
    void write_recipe(std::string file_name, std::vector<Chunk*>* chunks);
};
