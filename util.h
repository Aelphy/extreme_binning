//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_UTIL_H
#define EXTREME_BINNING_UTIL_H

#endif //EXTREME_BINNING_UTIL_H

#include <openssl/md5.h>

class Util {
public:
    Util();
    unsigned char result[MD5_DIGEST_LENGTH];
    void hash_next_chunk(unsigned char * data, int len);
    void finish_hash();
private:
    MD5_CTX md_context;
};
