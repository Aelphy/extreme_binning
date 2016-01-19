//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "bin.h"

Bin::~Bin() {
    for (auto it = chunks.begin(); it != chunks.end(); ++it) {
        delete it->first;
    }
}

Bin::Bin(long long int id, bool existing_flag) : id_(id), existing(existing_flag) {

}

long long int Bin::get_id() {
    return id_;
}

void Bin::save() {

}

void Bin::update(std::vector<Chunk *>) {

}
