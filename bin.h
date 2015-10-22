//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_BIN_H
#define EXTREME_BINNING_BIN_H

#endif //EXTREME_BINNING_BIN_H

#define DB_PATH "./db_file"

#include <unordered_map>
#include "storage.h"

class Bin {
public:
    static Storage * storage;
    std::unordered_map <unsigned char *, int> bin_entries;
    Bin();
    Bin(long long int id);
    static long long int gen_next_id();
};
