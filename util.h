//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_UTIL_H
    #include <openssl/md5.h>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <vector>

    #define FILE_STEP 1024
    #define D WINDOW
    #define r 0x78
    #define WINDOW 64
    #define DEFAULT_IRREDUCIBLE_POLY 0x000000000000001BL
    #define P_K_DEGREE 1LL << (WINDOW - 1)

    class Util {
     public:
        const static int window = WINDOW;
        ~Util();
        static Util * get_instance();
        void init_md5_hash();
        void hash_chunk(const char *data, int len);
        void hash_file(std::string file_path);
        void finish_md5_hash();
        unsigned char * get_md5_result();
        long long int rabin_fingerprint(std::vector<char> data);
        void finish_rabin_hash();
     private:
        Util();
        static Util * instance_;
        unsigned char md5_result_[MD5_DIGEST_LENGTH];
        MD5_CTX md_context;

        long long int current_fingerprint;
        long long int *Q32, *Q40, *Q48, *Q56, *Q64, *Q72, *Q80, *Q88;
        long long int compute_shifted_window(long long int s);
        long long int init_rabin_hash(const char *data, int limit);
        long long int update_rabin_hash(const char *data, int new_index);
    };
#define EXTREME_BINNING_UTIL_H

#endif //EXTREME_BINNING_UTIL_H
