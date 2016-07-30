//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "bin.h"
#include "storage.h"
#include "util.h"
#include "exceptions.h"

Bin::Bin() {
    id_ = -1;
}

Bin::~Bin() {
    for (auto it = chunks.begin(); it != chunks.end(); ++it) {
        delete *it;
    }
}

Bin* Bin::load(long long int id) {
    Bin* bin = Storage::get_instance()->read(id);

    return bin;
}

void Bin::set_id(long long int id) {
    id_ = id;
}

long long int Bin::get_id() {
    return id_;
}

void Bin::save() {
    Storage::get_instance()->write(this);
}

void Bin::update(std::vector<Chunk*> chunks) {
    for (auto chunk: chunks) {
        Storage::get_instance()->write(this, chunk);
    }
}

Chunk* Bin::get_representative_chunk() {
    if (chunks.size() == 0) {
        throw BrokenOrderException();
    }

    Chunk* representative_chunk = chunks[0];
    Util util;

    util.init_hash();
    util.hash_chunk(representative_chunk->get_data(), representative_chunk->get_length());
    util.finish_hash();

    char* representative_chunk_hash = util.get_result();
    char* current_chunk_hash = nullptr;

    for (int i = 1 ; i < chunks.size(); ++i) {
        util.init_hash();
        util.hash_chunk(chunks[i]->get_data(), chunks[i]->get_length());
        util.finish_hash();

        current_chunk_hash = util.get_result();

        if (hash_cmp(current_chunk_hash, representative_chunk_hash) == -1) {
            representative_chunk = chunks[i];
            delete representative_chunk_hash;
            representative_chunk_hash = current_chunk_hash;
        }
    }


    if (current_chunk_hash != nullptr) {
        delete current_chunk_hash;
    }

    if (representative_chunk_hash != current_chunk_hash) {
        delete representative_chunk_hash;
    }

    return representative_chunk;
}

int Bin::hash_cmp(char hash1[SHA256_DIGEST_LENGTH], char hash2[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        if (hash1[i] < hash2[i]) {
            return -1;
        }

        if (hash1[i] > hash2[i]) {
            return 1;
        }
    }

    return 0;
}
