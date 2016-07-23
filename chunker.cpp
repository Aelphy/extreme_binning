//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "chunker.h"

void Chunker::init(std::string fp) {
    fin_.open(fp, std::ifstream::binary);
    current_position_ = 0;
    eof_ = false;
}

Chunk* Chunker::get_next_chunk() {
    Chunk* chunk = new Chunk();
    std::vector<char> chunk_data;

    for (int i = 0; i < WINDOW_SIZE; ++i) {
        if (!fin_.eof()) {
            chunk_data.push_back(read_next());
        } else {
            eof_ = true;
            break;
        }
    }

    if (!eof_) {
        hasher_.init(&chunk_data);

        while (hasher_.get_hash() % D != r) {
            if (!fin_.eof()) {
                hasher_.recompute(read_next());
            } else {
                eof_ = true;
                break;
            }
        }

        hasher_.finish();
    }

    char* tmp_data = new char[chunk_data.size()];
    memcpy(tmp_data, chunk_data.data(), chunk_data.size());

    chunk->set_data(tmp_data, chunk_data.size());

    return chunk;
}

void Chunker::finish() {
    fin_.close();
}

char Chunker::read_next() {
    char buffer = '\0';
    fin_.read(&buffer, 1);
    current_position_++;

    return buffer;
}

bool Chunker::eof() {
    return eof_;
}
