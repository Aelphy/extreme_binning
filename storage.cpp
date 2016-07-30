//
// Created by Mikhail Usvyatsov on 22.10.15.
//

#include "storage.h"
#include "exceptions.h"

Storage* Storage::instance_;

Storage::Storage(std::string bins_file_path, std::string chunks_file_path) {
    bins_file_.open(bins_file_path, std::fstream::out | std::fstream::trunc);
    bins_file_.close();
    chunks_file_.open(chunks_file_path, std::fstream::out | std::fstream::trunc);
    chunks_file_.close();

    bins_file_.open(bins_file_path, std::fstream::in | std::fstream::out | std::fstream::binary);

    //std::cout << "backup started" << std::endl;

    if (!bins_file_.is_open()) {
        throw FileOpenException();
    }

    chunks_file_.open(chunks_file_path, std::fstream::in | std::fstream::out | std::fstream::binary);

    if (!chunks_file_.is_open()) {
        throw FileOpenException();
    }
}

Storage::~Storage() {
    bins_file_.close();
    chunks_file_.close();
}

Storage* Storage::get_instance() {
    if(instance_ == nullptr) {
        instance_ = new Storage(BINS_FILE, CHUNKS_FILE);
    }

    return instance_;
}

void Storage::finalize() {
    if(instance_ != nullptr) {
        //std::cout << "backup finished" << std::endl;
        delete instance_;
        instance_ = nullptr;
    } else {
        throw BrokenOrderException();
    }
}

char* Storage::read_chunks_blockwise(long long int chunk_id, unsigned long int size) {
    char* buffer = new char[BUFFER_SIZE];
    std::vector<char> result;
    unsigned long int pos = 0;
    unsigned long int result_size = 0;
    chunks_file_.seekg(chunk_id);

    while (pos < size) {
        result_size = result.size();
        chunks_file_.read(buffer, BUFFER_SIZE);
        unsigned long int с = 0;

        for (unsigned long int i = result_size; i < std::min(result_size + chunks_file_.gcount(), size); ++i) {
            result.push_back(buffer[i - result_size]);
            с++;
        }

        pos += с;
    }

    chunks_file_.clear();
    delete[] buffer;

    char* tmp_data = new char[result.size()];
    memcpy(tmp_data, result.data(), result.size());

    return tmp_data;
}

Bin* Storage::read(long long int bin_id) {
    long long int cid, next_chunk_offset = bin_id;
    unsigned long int chunk_size;
    Bin* bin = new Bin();
    bin->set_id(bin_id);

    while(next_chunk_offset != -1) {
        Chunk* chunk = new Chunk();

        bins_file_.seekg(next_chunk_offset);
        bins_file_.read(reinterpret_cast<char*>(&cid), sizeof(cid));
        bins_file_.read(reinterpret_cast<char*>(&chunk_size), sizeof(chunk_size));
        bins_file_.read(reinterpret_cast<char*>(&next_chunk_offset), sizeof(next_chunk_offset));

        chunk->set_id(cid);
        chunk->set_length(chunk_size);
        chunk->set_data(read_chunks_blockwise(cid, chunk_size), chunk_size);

        bin->chunks.push_back(chunk);
    }


    return bin;
}

void Storage::write(Bin* bin, Chunk* chunk) {
    long long int bid, cid, next_chunk_offset = bin->get_id();
    unsigned long int chunk_size;

    if (bin->get_id() == -1) { // a bin is new
        bins_file_.seekp(0, bins_file_.end);
        bid = bins_file_.tellg();
        bin->set_id(bid);
    } else { // a bin is existing
        while (next_chunk_offset != -1) {
            bins_file_.seekg(next_chunk_offset);
            bins_file_.read(reinterpret_cast<char*>(&cid), sizeof(cid));
            bins_file_.read(reinterpret_cast<char*>(&chunk_size), sizeof(chunk_size));
            bins_file_.read(reinterpret_cast<char*>(&next_chunk_offset), sizeof(next_chunk_offset));

            if (cid == chunk->get_id() && cid != -1) {
                throw OwerwriteException();
            }
        }

        // write next chunk addres to the end of previous entry
        next_chunk_offset = (long long int) bins_file_.tellg() - sizeof(next_chunk_offset); // here is a fucking magic, putting seekp here makes doesn't work
        bins_file_.seekg(0, bins_file_.end);
        bid = bins_file_.tellg();
        bins_file_.seekp(next_chunk_offset);
        bins_file_.write(reinterpret_cast<const char*>(&bid), sizeof(bid));

        bins_file_.seekp(0, bins_file_.end);
    }

    chunks_file_.seekp(0, chunks_file_.end);
    cid = chunks_file_.tellp();
    chunk->set_id(cid);

    chunk_size = chunk->get_length();
    next_chunk_offset = -1;

    bins_file_.write(reinterpret_cast<const char*>(&cid), sizeof(cid));
    bins_file_.write(reinterpret_cast<const char*>(&chunk_size), sizeof(chunk_size));
    bins_file_.write(reinterpret_cast<const char*>(&next_chunk_offset), sizeof(next_chunk_offset));

    chunks_file_.write(chunk->get_data(), chunk->get_length());
}

void Storage::write(Bin* bin) {
    for (int i = 0; i != bin->chunks.size(); ++i) {
        write(bin, bin->chunks.at(i));
    }
}

Chunk* Storage::read(long long int bin_id, long long int chunk_id) {
    long long int cid, next_chunk_offset = bin_id;
    unsigned long int chunk_size;

    while(next_chunk_offset != -1) {
        bins_file_.seekg(next_chunk_offset);
        bins_file_.read(reinterpret_cast<char*>(&cid), sizeof(cid));
        bins_file_.read(reinterpret_cast<char*>(&chunk_size), sizeof(chunk_size));
        bins_file_.read(reinterpret_cast<char*>(&next_chunk_offset), sizeof(next_chunk_offset));

        if (cid == chunk_id) {
            Chunk* chunk = new Chunk();

            chunk->set_id(cid);
            chunk->set_length(chunk_size);
            chunk->set_data(read_chunks_blockwise(cid, chunk_size), chunk_size);

            return chunk;
        }
    }

    return nullptr;
}
