//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#ifndef EXTREME_BINNING_UTIL_H
#define EXTREME_BINNING_UTIL_H
    #include <openssl/md5.h>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <vector>

    #define FILE_STEP 1024

    class Util {
     public:
        static Util * get_instance();
        void init_md5_hash();
        void hash_chunk(const char *data, int len);
        void hash_file(std::string file_path);
        void finish_md5_hash();
        unsigned char * get_md5_result();
     private:
        Util() { }
        static Util * instance_;
        unsigned char md5_result_[MD5_DIGEST_LENGTH];
        MD5_CTX md_context_;
    };

#endif //EXTREME_BINNING_UTIL_H
