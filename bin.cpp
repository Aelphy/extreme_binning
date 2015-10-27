//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "bin.h"

Storage * Bin::storage = new Storage(DB_FILE);

Bin::Bin(long long int id) {
    id_ = id;
}

long long int Bin::gen_next_id() {
    return storage->gen_next_bin_id();
}

long long int Bin::get_bin_id() {
    return id_;
}
