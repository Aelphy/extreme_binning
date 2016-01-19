//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "util.h"

Util * Util::instance_;

Util::Util() {
    long long int * polynomial = new long long int[window];
    polynomial[0] = DEFAULT_IRREDUCIBLE_POLY;

    for (int i = 1; i < window; ++i) {
        polynomial[i] = polynomial[i - 1] << 1;

        if ((polynomial[i - 1] & P_K_DEGREE))
            polynomial[i] ^= DEFAULT_IRREDUCIBLE_POLY;
    }

    Q32_ = new long long int[256] ();
    Q40_ = new long long int[256] ();
    Q48_ = new long long int[256] ();
    Q56_ = new long long int[256] ();
    Q64_ = new long long int[256] ();
    Q72_ = new long long int[256] ();
    Q80_ = new long long int[256] ();
    Q88_ = new long long int[256] ();
    old_ringing_ = new long long int[256] ();
    new_ringing_ = new long long int[256] ();

    long long int fingerprint = 0;

    /*
     * old_ringing[i] is the remainder in fingerprint
     * due to an old byte i just slid out of the window.
     */
    for (int i = 0; i < 256; ++i) {
        fingerprint = i;

        for (int j = 0; j < WINDOW * 8; j++) {
            fingerprint <<= 1;

            if (fingerprint & P_K_DEGREE)
                fingerprint ^= DEFAULT_IRREDUCIBLE_POLY;
        }

        old_ringing_[i] = fingerprint;
    }

    /*
     * new_ringing[i] is the remainder in fingerprint
     * due to the 9 most significant bits in fingerprint before update.
     */
    for (int i = 0; i < 256; ++i) {
        fingerprint = ((unsigned long long) i) << 55;

        for (int j = 0; j < 8; ++j) {
            fingerprint <<= 1;

            if (fingerprint & P_K_DEGREE)
                fingerprint ^= DEFAULT_IRREDUCIBLE_POLY;
        }

        new_ringing_[i] = fingerprint;
    }

    for (int i = 0; i < 256; ++i) {
        int c = i;

        for (int j = 0; j < 8 && c != 0; ++j) {
            if ((c & 1) != 0) {
                Q32_[i] ^= polynomial[j];
                Q40_[i] ^= polynomial[j + 8];
                Q48_[i] ^= polynomial[j + 16];
                Q56_[i] ^= polynomial[j + 24];
                Q64_[i] ^= polynomial[j + 32];
                Q72_[i] ^= polynomial[j + 40];
                Q80_[i] ^= polynomial[j + 48];
                Q88_[i] ^= polynomial[j + 56];
            }

            c >>= 1;
        }
    }

    current_fingerprint_ = -1;

    delete polynomial;
}

Util::~Util() {
    delete[] Q32_;
    delete[] Q40_;
    delete[] Q48_;
    delete[] Q56_;
    delete[] Q64_;
    delete[] Q72_;
    delete[] Q80_;
    delete[] Q88_;
}

Util * Util::get_instance() {
    if (!instance_) {
        instance_ = new Util();
    }

    return instance_;
}

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

unsigned char * Util::get_md5_result() {
    return md5_result_;
}

long long int Util::rabin_fingerprint(std::vector<char> data) {
    if (current_fingerprint_ == -1) {
        init_rabin_hash(data.data(), data.size());
    } else {
        update_rabin_hash(data.data(), data.size() - 1);
    }

    return current_fingerprint_;
}

long long int Util::compute_shifted_window(long long int s) {
    return Q32_[(int) (s & 0xFF)]
           ^ Q40_[(int) ((s >> 8)  & 0xFF)]
           ^ Q48_[(int) ((s >> 16) & 0xFF)]
           ^ Q56_[(int) ((s >> 24) & 0xFF)]
           ^ Q64_[(int) ((s >> 32) & 0xFF)]
           ^ Q72_[(int) ((s >> 40) & 0xFF)]
           ^ Q80_[(int) ((s >> 48) & 0xFF)]
           ^ Q88_[(int) ((s >> 56) & 0xFF)];
}

void Util::init_rabin_hash(const char *data, int len) {
    const int start = len % 4;
    current_fingerprint_ = 0;

    for (int s = 0; s < start; ++s) {
        current_fingerprint_ = (current_fingerprint_ << 16) ^ (data[s] & 0xFFFF);
    }

    for (int s = start; s < len; s += 4) {
        current_fingerprint_ = compute_shifted_window(current_fingerprint_) ^
                                 ((unsigned long long)(data[s] & 0xFFFF) << 48) ^
                                 ((unsigned long long)(data[s + 1] & 0xFFFF) << 32) ^
                                 ((unsigned long long)(data[s + 2] & 0xFFFF) << 16) ^
                                 (data[s + 3] & 0xFFFF);
    }
}

void Util::update_rabin_hash(const char *data, int new_index) {
    int old_index = new_index + 2 - WINDOW;

    long long int residual = old_ringing_[data[old_index]];
    residual ^= new_ringing_[current_fingerprint_ >> 55];
    current_fingerprint_ = ((current_fingerprint_ << 8) | data[new_index]) ^ residual;
    current_fingerprint_ &= ~P_K_DEGREE;
}

void Util::finish_rabin_hash() {
    current_fingerprint_ = -1;
}
