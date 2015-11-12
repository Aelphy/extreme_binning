//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_CHUNKER_H
#define EXTREME_BINNING_CHUNKER_H

#endif //EXTREME_BINNING_CHUNKER_H

#include <string>
#include <iostream>
#include <fstream>
#include "chunk.h"
#include "storage.h"
#include "util.h"

class Chunker {
 public:
    void init(std::string file_path);
    Chunk * get_next_chunk();
    void finish();
    bool eof();
 private:
    bool eof_ = false;
    std::ifstream fin_;
    long long int current_position;
    char read_next();
};
