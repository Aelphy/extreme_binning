//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "util.h"

void Util::init_md5_hash() {
    MD5_CTX new_md_context;
    md_context_ = new_md_context;
    MD5_Init(&md_context_);
}

void Util::hash_chunk(const char *data, int len) {
    MD5_Update(&md_context_, data, len);
}

void Util::hash_file(std::string file_path) {
    std::ifstream fin(file_path, std::ifstream::binary);
    char *buffer = new char[FILE_STEP];

    if (not fin) {
        std::cerr << "file: " << file_path << " failed to open" << std::endl;
        exit(1);
    }

    while (!fin.eof()) {
        fin.read(buffer, FILE_STEP);
        hash_chunk(buffer, fin.gcount());
    }

    delete[] buffer;
    fin.close();
}

void Util::finish_md5_hash() {
    MD5_Final(md5_result_, &md_context_);
}

unsigned char* Util::get_md5_result() {
    return md5_result_;
}
