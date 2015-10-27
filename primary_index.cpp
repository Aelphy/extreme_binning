//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "primary_index.h"

Bin * PrimaryIndex::add(unsigned char file_hash[MD5_DIGEST_LENGTH], unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH]) {
    try {
        items_by_file_hash.at(file_hash);
    } catch (std::out_of_range) {
        try {
            IndexItem * item = items_by_representative_chunk_hash.at(representative_chunk_hash);
            return new Bin(item->get_bin_id());
        } catch (std::out_of_range) {
            insert(file_hash, representative_chunk_hash);
            return new Bin(items_by_representative_chunk_hash.at(representative_chunk_hash)->get_bin_id());
        }
    }

    return NULL;
}

void PrimaryIndex::insert(unsigned char file_hash[MD5_DIGEST_LENGTH], unsigned char representative_chunk_hash[MD5_DIGEST_LENGTH]) {
    IndexItem * item = new IndexItem(file_hash, representative_chunk_hash, Bin::gen_next_id());
    items_by_file_hash[file_hash] = item;
    items_by_representative_chunk_hash[representative_chunk_hash] = item;
}
