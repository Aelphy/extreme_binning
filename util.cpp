//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "util.h"
#include <stdio.h>

Util * Util::instance_;

Util::Util() {
    long long int * polynomial = new long long int[window];
    polynomial[0] = DEFAULT_IRREDUCIBLE_POLY;

    for (int i = 1; i < window; ++i) {
        polynomial[i] = polynomial[i - 1] << 1;

        if ((polynomial[i - 1] & P_K_DEGREE) != 0)
            polynomial[i] ^= DEFAULT_IRREDUCIBLE_POLY;
    }

    Q32 = new long long int[256];
    Q40 = new long long int[256];
    Q48 = new long long int[256];
    Q56 = new long long int[256];
    Q64 = new long long int[256];
    Q72 = new long long int[256];
    Q80 = new long long int[256];
    Q88 = new long long int[256];

    for (int i = 0; i < 256; i++) {
        int c = i;

        for (int j = 0; j < 8 && c > 0; j++) {
            if ((c & 1) != 0) {
                Q32[i] ^= polynomial[j];
                Q40[i] ^= polynomial[j + 8];
                Q48[i] ^= polynomial[j + 16];
                Q56[i] ^= polynomial[j + 24];
                Q64[i] ^= polynomial[j + 32];
                Q72[i] ^= polynomial[j + 40];
                Q80[i] ^= polynomial[j + 48];
                Q88[i] ^= polynomial[j + 56];
            }

            c >>= 1;
        }
    }

    current_fingerprint = -1;

    delete polynomial;
}

Util::~Util() {
    delete[] Q32;
    delete[] Q40;
    delete[] Q48;
    delete[] Q56;
    delete[] Q64;
    delete[] Q72;
    delete[] Q80;
    delete[] Q88;
}

Util * Util::get_instance() {
    if (!instance_) {
        instance_ = new Util();
    }

    return instance_;
}

void Util::init_md5_hash() {
    MD5_CTX new_md_context;
    md_context = new_md_context;
    MD5_Init(&md_context);
}

void Util::hash_chunk(const char *data, int len) {
    MD5_Update(&md_context, data, len);
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
    MD5_Final(md5_result_, &md_context);
}

unsigned char * Util::get_md5_result() {
    return md5_result_;
}

long long int Util::rabin_fingerprint(std::vector<char> data) {
    if (current_fingerprint == -1) {
        current_fingerprint = init_rabin_hash(data.data(), data.size());
    } else {
        current_fingerprint = update_rabin_hash(data.data(), data.size() - 1);
    }

    return current_fingerprint;
}

long long int Util::compute_shifted_window(long long int s) {
    return Q32[(int) (s & 0xFF)]
           ^ Q40[(int) ((s >> 8)  & 0xFF)]
           ^ Q48[(int) ((s >> 16) & 0xFF)]
           ^ Q56[(int) ((s >> 24) & 0xFF)]
           ^ Q64[(int) ((s >> 32) & 0xFF)]
           ^ Q72[(int) ((s >> 40) & 0xFF)]
           ^ Q80[(int) ((s >> 48) & 0xFF)]
           ^ Q88[(int) ((s >> 56) & 0xFF)];
}

long long int Util::init_rabin_hash(const char *data, int limit) {
    int start = limit % 8;

    for (int s = 0; s < start; s++) {
        current_fingerprint = (current_fingerprint << 8) ^ (data[s] & 0xFF);
    }

    for (int s = start; s < limit; s += 8) {
        current_fingerprint = compute_shifted_window(current_fingerprint) ^
                                ((long) (data[s]     & 0xFFFF) << 48) ^
                                ((long) (data[s + 1] & 0xFFFF) << 32) ^
                                ((long) (data[s + 2] & 0xFFFF) << 16) ^
                                ((long)  data[s + 3] & 0xFFFF);
    }

    return current_fingerprint;
}

long long int Util::update_rabin_hash(const char *data, int new_index) {
    int old_index = new_index + 2 - WINDOW;


}

void Util::finish_rabin_hash() {
    current_fingerprint = -1;
}
