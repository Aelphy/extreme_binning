//
// Created by Mikhail Usvyatsov on 16.03.16.
//

#ifndef EXTREME_BINNING_RABIN_KARP_H
#define EXTREME_BINNING_RABIN_KARP_H

    #include <vector>
    #include <iostream>

    /** Represents x<sup>64</sup> + x<sup>4</sup> + x<sup>3</sup> + x + 1. */
    #define DEFAULT_IRREDUCIBLE_POLY 27ULL
    #define X_P_DEGREE (1ULL << (P_DEGREE - 1))
    #define P_DEGREE 64
    #define WINDOW_SIZE 48
    #define P 1
    #define r D - 1
    #define D AVG_CHUNK_SIZE - (AVG_CHUNK_SIZE >> 1)
    #define AVG_CHUNK_SIZE 1024


    class RabinKarpHasher {
     public:
        RabinKarpHasher();
        ~RabinKarpHasher();
        void init(std::vector<char> *data);
        void recompute(char next);
        void finish();
        long long int get_hash();
     private:
        std::vector<char> *data_;
        void init_tables();
        unsigned long long shifted_rolling_hash(unsigned long long rolling_hash);
        unsigned long long int *Q32_, *Q40_, *Q48_, *Q56_, *Q64_, *Q72_, *Q80_, *Q88_;
        long long int rolling_hash_;
    };

#endif //EXTREME_BINNING_RABIN_KARP_H
