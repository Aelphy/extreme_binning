//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_BIN_H
#define EXTREME_BINNING_BIN_H
    #include <vector>
    #include "util.h"
    #include "chunk.h"

    class Bin {
     public:
        std::vector <Chunk *> chunks;
        Bin();
        ~Bin();
        long long int get_id();
        void set_id(long long int id);
        void save();
        void update(std::vector<Chunk *>);
        Chunk* get_representative_chunk();
        static Bin* load(long long int id);
     private:
        long long int id_;
        int hash_cmp(char hash1[SHA256_DIGEST_LENGTH], char hash2[SHA256_DIGEST_LENGTH]);
    };
#endif //EXTREME_BINNING_BIN_H
