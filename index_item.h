//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_INDEX_ITEM_H
#define EXTREME_BINNING_INDEX_ITEM_H

#endif //EXTREME_BINNING_INDEX_ITEM_H

#include "util.h"

class IndexItem {
 public:
    IndexItem(const unsigned char file_hash[MD5_DIGEST_LENGTH],
              const unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH],
              const long long int bin_id);

    long long int get_bin_id();
 private:
    unsigned char file_hash_[MD5_DIGEST_LENGTH];
    unsigned char representative_chunk_hash_[MD5_DIGEST_LENGTH];
    long long int bin_id_;
};
