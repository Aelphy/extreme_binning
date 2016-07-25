//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_UTIL_H
#define EXTREME_BINNING_UTIL_H
    #include <openssl/sha.h>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <vector>

    #define FILE_STEP 1024

    class Util {
     public:
        void init_hash();
        void hash_chunk(const char *data, int len);
        void hash_file(std::string file_path);
        void finish_hash();
        char* get_result();
     private:
        unsigned char result_[SHA256_DIGEST_LENGTH];
        SHA256_CTX context_;
    };

#endif //EXTREME_BINNING_UTIL_H
