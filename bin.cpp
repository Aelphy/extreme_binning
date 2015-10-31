//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "bin.h"

Bin::Bin(long long int id) {
    id_ = id;
}

long long int Bin::get_bin_id() {
    return id_;
}
