//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "util.h"

Util::Util() {
    MD5_Init(&md_context);
}

void Util::hash_next_chunk(unsigned char * data, int len) {
    MD5_Update(&md_context, data, len);
}

void Util::finish_hash() {
    MD5_Final(result, &md_context);
}
