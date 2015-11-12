//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "chunker.h"

void Chunker::init(std::string fp) {
    fin_.open(fp, std::ifstream::binary);
    current_position = 0;
}

Chunk * Chunker::get_next_chunk() {
    Chunk *chunk = new Chunk(Storage::gen_next_id());
    std::vector<char> chunk_data;

    for (int i = 0; i < Util::window; ++i) {
        if (!fin_.eof()) {
            chunk_data.push_back(read_next());
        } else {
            eof_ = true;
            break;
        }
    }

    Util *util = Util::get_instance();
    int current_state = util->rabin_fingerprint(chunk_data);

    while (current_state % D != r) {
        if (!fin_.eof()) {
            chunk_data.push_back(read_next());
        } else {
            eof_ = true;
            break;
        }

        current_state = util->rabin_fingerprint(chunk_data);
    }

    chunk->set_data(chunk_data.data(), chunk_data.size());
    util->finish_rabin_hash();
    return chunk;
}

void Chunker::finish() {
    fin_.close();
}

char Chunker::read_next() {
    char buffer;
    fin_.read(&buffer, 1);
    current_position++;
    return buffer;
}

bool Chunker::eof() {
    return eof_;
}
