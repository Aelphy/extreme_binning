//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_UTIL_H
#define EXTREME_BINNING_UTIL_H
    #include <openssl/md5.h>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <vector>

    #define FILE_STEP 1024
    #define WINDOW 64
    #define DEFAULT_IRREDUCIBLE_POLY 0xbfe6b8a5bf378d83LL
    #define r D - 1
    #define D AVG_CHUNK_SIZE - (AVG_CHUNK_SIZE >> 1)
    #define AVG_CHUNK_SIZE 1024
    #define P_K_DEGREE 1L << (WINDOW - 1)

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
        long long int rabin_fingerprint(const std::vector<char> data);
        void finish_rabin_hash();
     private:
        Util();
        static Util * instance_;
        unsigned char md5_result_[MD5_DIGEST_LENGTH];
        MD5_CTX md_context_;
        long long int current_fingerprint_;
        long long int *Q32_, *Q40_, *Q48_, *Q56_, *Q64_, *Q72_, *Q80_, *Q88_, *old_ringing_, *new_ringing_;
        long long int compute_shifted_window(long long int s);
        void init_rabin_hash(const char *data, int len);
        void update_rabin_hash(const char *data, int new_index);
    };

#endif //EXTREME_BINNING_UTIL_H
