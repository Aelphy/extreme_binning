//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#ifndef EXTREME_BINNING_STORAGE_H
#define EXTREME_BINNING_STORAGE_H

#endif //EXTREME_BINNING_STORAGE_H

#define DB_FILE "./db_file"

#include <string>

class Storage {
 public:
    Storage(std::string file_path);
    long long int gen_next_bin_id();
};
