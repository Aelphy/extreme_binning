//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#include "storage.h"

Storage * Storage::instance_;

Storage::Storage(std::string file_path) {

}

void Storage::initialize() {
    if(!instance_) {
        instance_ = new Storage(DB_FILE);
    }
}

void Storage::finalize() {
}

long long int Storage::gen_next_id() {
    return 1;
}
