//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_PRIMARY_INDEX_H
#define EXTREME_BINNING_PRIMARY_INDEX_H

#endif //EXTREME_BINNING_PRIMARY_INDEX_H

#include <unordered_map>
#include "index_item.h"
#include "bin.h"

class PrimaryIndex {
 public:
    std::unordered_map <const unsigned char *, IndexItem *> items_by_file_hash;
    std::unordered_map <const unsigned char *, IndexItem *> items_by_representative_chunk_hash;
    ~PrimaryIndex();
    Bin * add(const unsigned char file_hash[MD5_DIGEST_LENGTH],
              const unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH]);
 private:
    void insert(const unsigned char file_hash[MD5_DIGEST_LENGTH],
                const unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH]);
};
