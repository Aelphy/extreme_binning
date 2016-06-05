//
// Created by Mikhail Usvyatsov on 31.10.15.
//

#include "chunk.h"

Chunk::Chunk(long long int id, char * chuk_data, int data_length) : id_(id), length(data_length) {
    data = new char[data_length];
    memcpy(data, chuk_data, data_length);
};

Chunk::~Chunk() {
    delete[] data;
}

void Chunk::set_data(char *chunk_data, int data_length) {
    data = new char[data_length];

    for (int i = 0; i < data_length; ++i) {
        data[i] = chunk_data[i];
    }

    length = data_length;
}
