//
// Created by Mikhail Usvyatsov on 16.03.16.
//

#ifndef EXTREME_BINNING_RABIN_KARP_H
#define EXTREME_BINNING_RABIN_KARP_H

    #include <vector>

    #define WINDOW 64
    #define DEFAULT_IRREDUCIBLE_POLY 0xbfe6b8a5bf378d83LL
    #define r D - 1
    #define D AVG_CHUNK_SIZE - (AVG_CHUNK_SIZE >> 1)
    #define AVG_CHUNK_SIZE 1024
    #define P_K_DEGREE 1L << (WINDOW - 1)

    class RabinKarp {
     public:
        ~RabinKarp();
        const static int window = WINDOW;
        long long int fingerprint(const std::vector<char> data);
        void finish_hash();
     private:
        RabinKarp();
        static RabinKarp * instance_;
        long long int current_fingerprint_;
        long long int *Q32_, *Q40_, *Q48_, *Q56_, *Q64_, *Q72_, *Q80_, *Q88_, *old_ringing_, *new_ringing_;
        long long int compute_shifted_window(long long int s);
        void init_hash(const char *data, int len);
        void update_hash(const char *data, int new_index);
    };

#endif //EXTREME_BINNING_RABIN_KARP_H
