//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "index_item.h"
#include "exceptions.h"

IndexItem::IndexItem(const char file_hash[SHA256_DIGEST_LENGTH],
                     const char representative_chunk_hash[SHA256_DIGEST_LENGTH],
                     const long long int bin_id) : bin_id_(bin_id) {
    if (bin_id == -1) {
        throw BrokenOrderException();
    }

    memcpy(file_hash_, file_hash, SHA256_DIGEST_LENGTH);
    memcpy(representative_chunk_hash_, representative_chunk_hash, SHA256_DIGEST_LENGTH);
}

long long int IndexItem::get_bin_id() {
    return bin_id_;
}
