//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "util.h"

Util * Util::instance_;

Util::Util() {}

Util * Util::get_instance() {
    if (!instance_) {
        instance_ = new Util();
    }

    return instance_;
}

void Util::init_hash() {
    MD5_CTX new_md_context;
    md_context = new_md_context;
    MD5_Init(&md_context);
}

void Util::hash_next_chunk(char * data, int len) {
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
    MD5_Final(result_, &md_context);
}

unsigned char * Util::get_hash() {
    return result_;
}

int Util::rabin_fingerprint(std::vector<char> data, int start) {
    if (start >= data.size() - 1) {
        return -1;
    } else {

    }
}
