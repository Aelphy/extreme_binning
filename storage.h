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
    #define BIN_SIZE 5// sizeof bin should be here + sizeoff chunk_size + chunk_addrress
    #define BUFFER_SIZE 5

    class Storage {
     public:
        static void initialize();
        static void finalize();
        static Storage* get_instance();
        static unsigned long long int write(Bin* bin);
        static unsigned long long int write(Bin* bin, Chunk* chunk);
        static Bin* read(unsigned long long int bin_id);
        static Chunk* read(unsigned long long int bin_id, unsigned long long int chunk_id);
     private:
        static Storage* instance_;
        static std::fstream chunks_file_;
        static std::fstream bins_file_;
        static char* read_chunks_blockwise(unsigned long long int chunk_id, int size);
        Storage(std::string bins_file_path, std::string chunks_file_path);
    };
#endif //EXTREME_BINNING_STORAGE_H
