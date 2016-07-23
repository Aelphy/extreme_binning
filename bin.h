//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_BIN_H
#define EXTREME_BINNING_BIN_H
    #include <vector>
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
        static Bin* load(long long int id);
     private:
        long long int id_;
    };
#endif //EXTREME_BINNING_BIN_H
