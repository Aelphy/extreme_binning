//
// Created by Mikhail Usvyatsov on 29.10.15.
//

#ifndef EXTREME_BINNING_CHUNK_H
#define EXTREME_BINNING_CHUNK_H
    #include <string>

    class Chunk {
     public:
        Chunk();
        ~Chunk();
        long long int get_id();
        char* get_data();
        unsigned long int get_length();
        void set_id(long long int id);
        void set_data(char* data, unsigned long int length);
        void set_length(unsigned long int length);
        static Chunk* load(long long int bin_id, long long int chunk_id);
     private:
        unsigned long int length_;
        char* data_;
        long long int id_;
    };
#endif //EXTREME_BINNING_CHUNK_H
