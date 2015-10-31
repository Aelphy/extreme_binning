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
    #define PRIME 153191
    #define D_VAL 1
    #define r_VAL 1
    #define MIN_CHUNK_SIZE 1

    class Util {
     public:
        const static int D = D_VAL;
        const static int r = r_VAL;
        const static int min_chunk_size = MIN_CHUNK_SIZE;
        static Util * get_instance();
        void init_hash();
        void hash_chunk(const char *data, int len);
        void hash_file(std::string file_path);
        void finish_hash();
        int rabin_fingerprint(std::vector<char> data, int start);
        unsigned char * get_result();
     private:
        static Util * instance_;
        unsigned char result_[MD5_DIGEST_LENGTH];
        MD5_CTX md_context;
        Util();
    };
#define EXTREME_BINNING_UTIL_H

#endif //EXTREME_BINNING_UTIL_H
