//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "util.h"

void Util::init() {
    MD5_CTX new_md_context;
    md_context = new_md_context;
    MD5_Init(&md_context);
}

void Util::hash_next_chunk(unsigned char * data, int len) {
    MD5_Update(&md_context, data, len);
}

void Util::hash_file(std::string file_path) {
    std::ifstream fin(file_path, std::ios::binary);
    char *buffer = new char [FILE_STEP];

    if (not fin) {
        std::cerr << "file: " << file_path << " failed to open" << std::endl;
        return;
    }

    while (!fin.eof( )) {
        fin.read(buffer, FILE_STEP);
        MD5_Update(&md_context, buffer, fin.gcount());
    }

    delete[] buffer;
    fin.close();
}

void Util::finish_hash() {
    MD5_Final(result, &md_context);
}
