//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#include "storage.h"
#include "exceptions.h"

Storage * Storage::instance_;
std::fstream Storage::chunks_file_;
std::fstream Storage::bins_file_;

Storage::Storage(std::string bins_file_path, std::string chunks_file_path) {
    bins_file_.open(bins_file_path, std::fstream::binary | std::fstream::out | std::fstream::in);

    std::cout << "backup started" << std::endl;

    if (!bins_file_.is_open()) {
        throw FileOpenException();
    }

    chunks_file_.open(chunks_file_path, std::ofstream::binary | std::fstream::out | std::fstream::in);

    if (!chunks_file_.is_open()) {
        throw FileOpenException();
    }
}

void Storage::initialize() {
    if(!instance_) {
        instance_ = new Storage(BINS_FILE, CHUNKS_FILE);
    }
}

Storage* Storage::get_instance() {
    return instance_;
}

void Storage::finalize() {
    std::cout << "backup finished" << std::endl;
    bins_file_.close();
    chunks_file_.close();
    delete instance_;
}

char* Storage::read_chunks_blockwise(unsigned long long int chunk_id, int size) {
    char* buffer = new char [BUFFER_SIZE];
    std::vector <char> result;
    chunks_file_.seekg(chunk_id);
    int pos = 0;

    while (pos <= size) {
        int result_size = result.size();
        chunks_file_.read(buffer, BUFFER_SIZE);
        int с = 0;

        for (int i = result_size; i < std::min(result_size + BUFFER_SIZE, size); ++i) {
            result.push_back(buffer[i]);
            с++;
        }

        pos += с;
    }

    delete[] buffer;

    return result.data();
}

Bin* Storage::read(unsigned long long int bin_id) {
    char* buffer = new char [BIN_SIZE];
    unsigned long long int cid;
    long long int next_chunk_offset = bin_id;
    int chunk_size;
    Bin* bin = new Bin();
    bin->set_id(bin_id);

    while(next_chunk_offset != -1) {
        Chunk* chunk = new Chunk();

        bins_file_.seekg(next_chunk_offset);
        bins_file_.read(buffer, BIN_SIZE);

        if (scanf(buffer, "%llu%i%llu", cid, chunk_size, next_chunk_offset) != 3) {
            throw FileReadException();
        }

        chunk->set_id(cid);
        chunk->set_length(chunk_size);
        chunk->set_data(read_chunks_blockwise(cid, chunk_size), chunk_size);

        bin->chunks.push_back(chunk);
    }

    delete[] buffer;

    return bin;
}

unsigned long long int Storage::write(Bin* bin, Chunk* chunk) {
    char* buffer = new char [BIN_SIZE];
    unsigned long long int bid, cid;
    long long int next_chunk_offset = bin->get_id();
    int chunk_size;

    if (next_chunk_offset == -1) {
        throw BrokenOrderException();
    }

    if (bin->get_id() == -1) { // a bin is new
        bins_file_.seekp(0, bins_file_.end);
        bid = bins_file_.tellg();
        bin->set_id(bid);
    } else { // a bin is existing
        while (next_chunk_offset != -1) {
            bins_file_.seekg(next_chunk_offset);

            bins_file_.read(buffer, BIN_SIZE);

            if (scanf(buffer, "%llu%i%ll", &cid, &chunk_size, &next_chunk_offset) != 3) {
                throw FileReadException();
            }
        }

        bins_file_.seekp((unsigned long long int) bins_file_.tellg() + sizeof(cid) + sizeof(chunk_size));
        bins_file_.seekg(0, bins_file_.end);
        bid = bins_file_.tellg();
        bins_file_ << bid;
        bins_file_.seekp(0, bins_file_.end);
    }

    chunks_file_.seekg(0, chunks_file_.end);
    cid = chunks_file_.tellg();
    chunk->set_id(cid);
    bins_file_ << cid << chunk->get_length() << -1;
    chunks_file_ << chunk->get_data();

    return cid;
}

unsigned long long int Storage::write(Bin* bin) {
    if (bin->get_id() != -1) {
        throw BrokenOrderException();
    }

    for (int i = 0; i != bin->chunks.size(); ++i) {
        write(bin, bin->chunks.at(i));
    }

    return bin->get_id();
}

Chunk * Storage::read(unsigned long long int bin_id, unsigned long long int chunk_id) {
    char* buffer = new char [BIN_SIZE];
    unsigned long long int bid, cid;
    long long int next_chunk_offset = chunk_id;
    int chunk_size;

    while(next_chunk_offset != -1) {
        Chunk* chunk = new Chunk();

        bins_file_.seekg(next_chunk_offset);
        bins_file_.read(buffer, BIN_SIZE);

        if (scanf(buffer, "%llu%i%ll", cid, chunk_size, next_chunk_offset) != 3) {
            throw FileReadException();
        }

        if (cid == chunk_id) {
            chunk->set_id(cid);
            chunk->set_length(chunk_size);
            chunk->set_data(read_chunks_blockwise(cid, chunk_size), chunk_size);

            delete[] buffer;
            return chunk;
        }
    }

    delete[] buffer;
    return nullptr;
}
