//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "util.h"

void Util::init_hash() {
    SHA256_CTX new_md_context;
    context_ = new_md_context;
    SHA256_Init(&context_);
}

void Util::hash_chunk(const char* data, unsigned long int len) {
    SHA256_Update(&context_, data, len);
}

void Util::hash_file(std::string file_path) {
    std::ifstream fin(file_path, std::ifstream::binary);
    char buffer[FILE_STEP];

    if (not fin) {
        std::cerr << "file: " << file_path << " failed to open" << std::endl;
        exit(1);
    }

    while (!fin.eof()) {
        fin.read(buffer, FILE_STEP);
        hash_chunk(buffer, fin.gcount());
    }

    fin.close();
}

void Util::finish_hash() {
    SHA256_Final(result_, &context_);
}

char* Util::get_result() {
    char* result = new char[SHA256_DIGEST_LENGTH];
    memcpy(result, result_, SHA256_DIGEST_LENGTH);

    return result;
}
