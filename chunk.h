//
// Created by Mikhail Usvyatsov on 29.10.15.
//

#ifndef EXTREME_BINNING_CHUNK_H
    #include <string>

    class Chunk {
     public:
        char * data;
        int length;
        explicit Chunk(long long int id) : id_(id) {};
        Chunk(long long int id, char * chuk_data, int data_length);
        ~Chunk();
        void set_data(char *data, int length);
     private:
        long long int id_;
    };
#define EXTREME_BINNING_CHUNK_H

#endif //EXTREME_BINNING_CHUNK_H
