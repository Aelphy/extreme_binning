//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_CHUNKER_H
#define EXTREME_BINNING_CHUNKER_H

#endif //EXTREME_BINNING_CHUNKER_H

#include <string>
#include <iostream>
#include <fstream>

class Chunker {
 public:
    std::ifstream fin;
    void init(std::string file_path);
    unsigned char * get_next_chunk();
    void finish();
 private:

};
