//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "bin.h"
#include "storage.h"

Bin::Bin() {
    id_ = -1;
}

Bin::~Bin() {
    for (auto it = chunks.begin(); it != chunks.end(); ++it) {
        delete *it;
    }
}

Bin* Bin::load(long long int id) {
    Bin* bin = Storage::read(id);

    return bin;
}

void Bin::set_id(long long int id) {
    id_ = id;
}

long long int Bin::get_id() {
    return id_;
}

void Bin::save() {
    Storage::write(this);
}

void Bin::update(std::vector<Chunk *> chunks) {
    for (auto chunk: chunks) {
        Storage::write(this, chunk);
    }
}
