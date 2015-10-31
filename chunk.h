//
// Created by Mikhail Usvyatsov on 29.10.15.
//

#ifndef EXTREME_BINNING_CHUNK_H
#define EXTREME_BINNING_CHUNK_H

#endif //EXTREME_BINNING_CHUNK_H

#include <string>

class Chunk {
 public:
    explicit Chunk(long long int id) : id_(id) {};
    Chunk(long long int id, char * data, int length) : id_(id), length_(length) {
        data_ = new char(length);
        memcpy(data_, data, length);
    };
    ~Chunk();
    void set_data(char *data, int length);
 private:
    long long int id_;
    char * data_;
    int length_;
};
