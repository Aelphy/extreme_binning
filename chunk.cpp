//
// Created by Mikhail Usvyatsov on 31.10.15.
//

#include "chunk.h"
#include "storage.h"
#include "exceptions.h"

Chunk::~Chunk() {
    delete data_;
}

unsigned long long int Chunk::get_id() {
    return id_;
}

void Chunk::set_id(unsigned long long int id) {
    id_ = id;
}

void Chunk::set_length(int length) {
    length_ = length;
}

Chunk* Chunk::load(unsigned long long int bin_id, unsigned long long int chunk_id) {
    return Storage::get_instance()->read(bin_id, chunk_id);
};

char* Chunk::get_data() {
 return data_;
}

int Chunk::get_length() {
    return length_;
}

void Chunk::set_data(char *chunk_data, int data_length) {
    if (data_ != nullptr) {
        throw BrokenOrderException();
    }

    data_ = new char[data_length];

    for (int i = 0; i < data_length; ++i) {
        data_[i] = chunk_data[i];
    }

    length_ = data_length;
}
