//
// Created by Mikhail Usvyatsov on 31.10.15.
//

#include "chunk.h"

Chunk::~Chunk() {
    delete data_;
}

void Chunk::set_data(char *data, int length) {
    memcpy(data_, data, length);
    length_ = length;
}
