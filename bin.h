//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_BIN_H
#define EXTREME_BINNING_BIN_H

#endif //EXTREME_BINNING_BIN_H

#include <unordered_map>
#include "storage.h"

class Bin {
 public:
    std::unordered_map <unsigned char *, int> chunks;
    explicit Bin(long long int id);
    static long long int gen_next_id();
    long long int get_bin_id();
 private:
    long long int id_;
    static Storage *storage;
};
