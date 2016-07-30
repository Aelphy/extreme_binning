//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "chunker.h"
#include "exceptions.h"

void Chunker::init(std::string file_path) {
    fin_.open(file_path, std::ifstream::binary);

    if (!fin_.is_open()) {
        throw FileOpenException();
    }
}

Chunk* Chunker::get_next_chunk(unsigned long long int divisor, unsigned long long int residual) {
    RabinKarpHasher hasher_;
    Chunk* chunk = new Chunk();
    std::vector<char> chunk_data;

    for (int i = 0; i < WINDOW_SIZE; ++i) {
        if (!fin_.eof()) {
            chunk_data.push_back(read_next());
        } else {
            break;
        }
    }

    if (!fin_.eof()) {
        hasher_.init(&chunk_data);

        while ((hasher_.get_hash() % divisor) != residual) {
            if (!fin_.eof()) {
                hasher_.recompute(read_next());
            } else {
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

    return buffer;
}

bool Chunker::eof() {
    return fin_.eof();
}
