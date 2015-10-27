//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "chunker.h"

void Chunker::init(std::string fp) {
    fin.open(fp, std::ios::binary);

    if (not fin) {
        std::cerr << "file: " << fp << " failed to open" << std::endl;
        return;
    }
}

unsigned char * Chunker::get_next_chunk() {

}

void Chunker::finish() {
    fin.close();
}
