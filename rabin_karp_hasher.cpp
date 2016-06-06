#include <iostream>
#include "rabin_karp_hasher.h"

RabinKarpHasher::RabinKarpHasher() {
    init_tables();
}

RabinKarpHasher::~RabinKarpHasher() {
    delete[] Q32_;
    delete[] Q40_;
    delete[] Q48_;
    delete[] Q56_;
    delete[] Q64_;
    delete[] Q72_;
    delete[] Q80_;
    delete[] Q88_;
}

long long int RabinKarpHasher::get_hash() {
    return rolling_hash_;
}

unsigned long long RabinKarpHasher::shifted_rolling_hash(unsigned long long rolling_hash) {
    return Q32_[(int) (rolling_hash & 0xFF)] ^
           Q40_[(int) ((rolling_hash >> 8) & 0xFF)] ^
           Q48_[(int) ((rolling_hash >> 16) & 0xFF)] ^
           Q56_[(int) ((rolling_hash >> 24) & 0xFF)] ^
           Q64_[(int) ((rolling_hash >> 32) & 0xFF)] ^
           Q72_[(int) ((rolling_hash >> 40) & 0xFF)] ^
           Q80_[(int) ((rolling_hash >> 48) & 0xFF)] ^
           Q88_[(int) ((rolling_hash >> 56) & 0xFF)];
}

void RabinKarpHasher::init_tables() {
    Q32_ = new unsigned long long int[256] ();
    Q40_ = new unsigned long long int[256] ();
    Q48_ = new unsigned long long int[256] ();
    Q56_ = new unsigned long long int[256] ();
    Q64_ = new unsigned long long int[256] ();
    Q72_ = new unsigned long long int[256] ();
    Q80_ = new unsigned long long int[256] ();
    Q88_ = new unsigned long long int[256] ();

    unsigned long long int mods[P_DEGREE];

    // We want to have mods[i] == x^(P_DEGREE+i)
    mods[0] = P;

    for (int i = 1; i < P_DEGREE; ++i) {
        // x^i == x(x^(i-1)) (mod P)
        unsigned long long int new_mod = mods[i - 1] << 1;
        // if x^(i-1) had a x_(P_DEGREE-1) term then x^i has a
        // x^P_DEGREE term that 'fell off' the top end.
        // Since x^P_DEGREE == P (mod P), we should add P
        // to account for this:
        if (mods[i - 1] & X_P_DEGREE) {
            new_mod ^= P;
        }

        mods[i] = new_mod;
    }

    // Let i be a number between 0 and 255 (i.e. a byte).
    // Let its bits be b0, b1, ..., b7.
    // Let Q32 be the polynomial b0*x^39 + b1*x^38 + ... + b7*x^32 (mod P).
    // Likewise Q40 be the polynomial b0*x^47 + b1*x^46 + ... + b7*x^40 (mod P).
    for (int i = 0; i < 256; ++i) {
        int c = i;

        for (int j = 0; j < 8 && c > 0; ++j) {
            if (c & 1) {
                Q32_[i] ^= mods[j];
                Q40_[i] ^= mods[j + 8];
                Q48_[i] ^= mods[j + 16];
                Q56_[i] ^= mods[j + 24];
                Q64_[i] ^= mods[j + 32];
                Q72_[i] ^= mods[j + 40];
                Q80_[i] ^= mods[j + 48];
                Q88_[i] ^= mods[j + 56];
            }

            c >>= 1;
        }
    }
}

void RabinKarpHasher::init(std::vector<char> *data) {
    if (data_ != nullptr) {
        std::cerr <<  "do not forget to finish before init" << std::endl;
        return;
    }

    data_ = data;
    rolling_hash_ = 0;

    // First, process a few bytes so that the number of bytes remaining is a multiple of 8.
    // This makes the later loop easier.
    const int starter_bytes = data_->size() % 8;
    int s = 0;

    while (s < starter_bytes) {
        rolling_hash_ = (rolling_hash_ << 8) ^ (data_->at(s++) & 0xFF);
    }

    while (s < data_->size()) {
        rolling_hash_ = shifted_rolling_hash(rolling_hash_) ^
                ((unsigned long long)data_->at(s) << 56) ^
                (((unsigned long long)data_->at(s + 1) & 0xFF) << 48) ^
                (((unsigned long long)data_->at(s + 2) & 0xFF) << 40) ^
                (((unsigned long long)data_->at(s + 3) & 0xFF) << 32) ^
                (((unsigned long long)data_->at(s + 4) & 0xFF) << 24) ^
                (((unsigned long long)data_->at(s + 5) & 0xFF) << 16) ^
                (((unsigned long long)data_->at(s + 6) & 0xFF) << 8) ^
                (data_->at(s + 7) & 0xFF);
        s += 8;
    }
}

void RabinKarpHasher::recompute(char next_char) {
    if (data_ == nullptr) {
        std::cerr <<  "impossible to recompute before init" << std::endl;
        return;
    }

    data_->push_back(next_char);

    rolling_hash_ = (rolling_hash_ << 8) ^ (next_char & 0xFF);
}

void RabinKarpHasher::finish() {
    rolling_hash_ = -1;
    data_ = nullptr;
}