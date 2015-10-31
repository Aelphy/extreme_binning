//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_BIN_H
#define EXTREME_BINNING_BIN_H

#endif //EXTREME_BINNING_BIN_H

#include <unordered_map>
#include <vector>
#include "storage.h"
#include "chunk.h"

class Bin {
 public:
    bool existing;
    std::unordered_map <Chunk *, int> chunks;
    Bin(long long int id, bool existing);
    ~Bin();
    long long int get_bin_id();
    void save();
    void update(std::vector<Chunk *>);
 private:
    long long int id_;
};
