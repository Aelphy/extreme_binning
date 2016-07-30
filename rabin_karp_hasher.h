//
// Created by Mikhail Usvyatsov on 16.03.16.
//

#ifndef EXTREME_BINNING_RABIN_KARP_H
#define EXTREME_BINNING_RABIN_KARP_H

    #include <vector>

    #define X_P_DEGREE (1ULL << (P_DEGREE - 1))
    #define P_DEGREE 64
    #define P 1

    class RabinKarpHasher {
     public:
        RabinKarpHasher();
        ~RabinKarpHasher();
        void init(std::vector<char>* data);
        void recompute(char next);
        void finish();
        unsigned long long int get_hash();
        std::vector<char>* get_data();
     private:
        std::vector<char>* data_;
        void init_tables();
        unsigned long long shifted_rolling_hash(unsigned long long rolling_hash);
        unsigned long long int *Q32_, *Q40_, *Q48_, *Q56_, *Q64_, *Q72_, *Q80_, *Q88_;
        unsigned long long int rolling_hash_;
    };

#endif //EXTREME_BINNING_RABIN_KARP_H
