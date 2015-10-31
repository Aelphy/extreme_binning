//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#ifndef EXTREME_BINNING_STORAGE_H
    #include <string>

    #define DB_FILE "./data/db_file"

    class Storage {
    public:
        static void initialize();
        static void finalize();
        static long long int gen_next_id();
    private:
        static Storage * instance_;
        Storage(std::string file_path);
    };
#define EXTREME_BINNING_STORAGE_H

#endif //EXTREME_BINNING_STORAGE_H
