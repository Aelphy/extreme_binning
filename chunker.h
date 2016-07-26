//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_CHUNKER_H
#define EXTREME_BINNING_CHUNKER_H

    #include <string>
    #include <iostream>
    #include <fstream>
    #include "chunk.h"
    #include "storage.h"
    #include "util.h"
    #include "rabin_karp_hasher.h"

    #define WINDOW_SIZE 64
    #define r D - 1
    #define D AVG_CHUNK_SIZE - (AVG_CHUNK_SIZE >> 1)
    #define AVG_CHUNK_SIZE 100

    class Chunker {
     public:
        void init(std::string file_path);
        Chunk * get_next_chunk();
        void finish();
        bool eof();
     private:
        RabinKarpHasher hasher_;
        std::ifstream fin_;
        long long int current_position_;
        char read_next();
    };

#endif //EXTREME_BINNING_CHUNKER_H
