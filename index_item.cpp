//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "index_item.h"

IndexItem::IndexItem(const unsigned char file_hash[MD5_DIGEST_LENGTH],
                     const unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH],
                     const unsigned long long int bin_id) : bin_id_(bin_id) {
    memcpy(file_hash_, file_hash, MD5_DIGEST_LENGTH);
    memcpy(representative_chunk_hash_, representative_chunk_hash, MD5_DIGEST_LENGTH);
}

unsigned long long int IndexItem::get_bin_id() {
    return bin_id_;
}
