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
        unsigned long long int get_id();
        char* get_data();
        int get_length();
        void set_id(unsigned long long int id);
        void set_data(const char *data, int length);
        void set_length(int length);
        static Chunk* load(unsigned long long int bin_id, unsigned long long int chunk_id);
     private:
        int length_;
        char* data_;
        unsigned long long int id_;
    };
#endif //EXTREME_BINNING_CHUNK_H
