//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_UTIL_H
#define EXTREME_BINNING_UTIL_H

#endif //EXTREME_BINNING_UTIL_H

#define FILE_STEP 1024

#include <openssl/md5.h>
#include <string>
#include <iostream>
#include <fstream>

class Util {
 public:
    unsigned char result[MD5_DIGEST_LENGTH];
    void init();
    void hash_next_chunk(char *data, int len);
    void hash_file(std::string file_path);
    void finish_hash();
 private:
    MD5_CTX md_context;
};
