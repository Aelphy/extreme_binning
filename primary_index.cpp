//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "primary_index.h"

PrimaryIndex::~PrimaryIndex() {
    for (auto it = items_by_file_hash.begin(); it != items_by_file_hash.end(); ++it) {
        delete it->second;
    }
}

Bin * PrimaryIndex::add(const unsigned char file_hash[MD5_DIGEST_LENGTH],
                        const unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH]) {
    auto item = items_by_file_hash.find(file_hash);

    if (item == items_by_file_hash.end()) {
        item = items_by_representative_chunk_hash.find(representative_chunk_hash);

        if (item == items_by_representative_chunk_hash.end()) {
            insert(file_hash, representative_chunk_hash);
            return Bin::load(items_by_representative_chunk_hash.at(representative_chunk_hash)->get_bin_id());
        } else {
            return Bin::load(item->second->get_bin_id());
        }
    }

    return nullptr;
}

void PrimaryIndex::insert(const unsigned char file_hash[MD5_DIGEST_LENGTH],
                          const unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH]) {
    Bin * bin = new Bin();
    IndexItem * item = new IndexItem(file_hash, representative_chunk_hash, -1);
    items_by_file_hash[file_hash] = item;
    items_by_representative_chunk_hash[representative_chunk_hash] = item;
}
