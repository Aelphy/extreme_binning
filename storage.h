//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#ifndef EXTREME_BINNING_STORAGE_H
#define EXTREME_BINNING_STORAGE_H
    #include <string>
    #include <fstream>
    #include <iostream>
    #include "bin.h"

    #define CHUNKS_FILE "./data/chunks_file"
    #define BINS_FILE "./data/bins_file"
    #define BUFFER_SIZE 1024

    class Storage {
     public:
        static void finalize();
        static Storage* get_instance();
        void write(Bin* bin);
        void write(Bin* bin, Chunk* chunk);
        Bin* read(long long int bin_id);
        Chunk* read(long long int bin_id, long long int chunk_id);
     private:
        static Storage* instance_;
        std::fstream chunks_file_;
        std::fstream bins_file_;
        char* read_chunks_blockwise(long long int chunk_id, unsigned long int size);
        Storage(std::string bins_file_path, std::string chunks_file_path);
        ~Storage();
    };
#endif //EXTREME_BINNING_STORAGE_H
