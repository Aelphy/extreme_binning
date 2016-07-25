//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_INDEX_ITEM_H
#define EXTREME_BINNING_INDEX_ITEM_H

#endif //EXTREME_BINNING_INDEX_ITEM_H

#include "util.h"

class IndexItem {
 public:
    IndexItem(const char file_hash[SHA256_DIGEST_LENGTH],
              const char representative_chunk_hash[SHA256_DIGEST_LENGTH],
              const long long int bin_id);

    long long int get_bin_id();
 private:
    char file_hash_[SHA256_DIGEST_LENGTH];
    char representative_chunk_hash_[SHA256_DIGEST_LENGTH];
    long long int bin_id_;
};
