//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#ifndef EXTREME_BINNING_STORAGE_H
#define EXTREME_BINNING_STORAGE_H
    #include <string>
    #include <fstream>

    #define DB_FILE "./data/db_file"

    class Storage {
     public:
        static void initialize();
        static void finalize();
        static long long int gen_next_id();
        static void write(char *data, long long int pos);
     private:
        static Storage * instance_;
        static std::ofstream db_file_;
        Storage(std::string file_path);
    };
#endif //EXTREME_BINNING_STORAGE_H
