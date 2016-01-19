//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#include "storage.h"

Storage * Storage::instance_;
std::ofstream Storage::db_file_;

Storage::Storage(std::string file_path) {
    db_file_.open(file_path, std::ofstream::binary);

    if (db_file_.is_open()) {
        db_file_.write("backup started\n", 15);
    } else {
        db_file_.write("backup failure\n", 15);
    }
}

void Storage::initialize() {
    if(!instance_) {
        instance_ = new Storage(DB_FILE);
    }
}

void Storage::finalize() {
    db_file_.write("backup finished\n", 16);
    db_file_.close();
    delete instance_;
}

long long int Storage::gen_next_id() {
    return 1;
}


void Storage::write(char *data, long long int pos) {

}
