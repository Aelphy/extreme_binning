//
// Created by Mikhail Usvyatsov on 21.10.15.
//

#include "primary_index.h"
#include "exceptions.h"

PrimaryIndex::PrimaryIndex(std::string file_path) {
    recepie_file_.open(file_path, std::ofstream::binary);

    if (!recepie_file_.is_open()) {
        throw FileOpenException();
    }
}

PrimaryIndex::~PrimaryIndex() {
    recepie_file_.close();
}

void PrimaryIndex::insert(std::string file_name,
                          std::string file_hash,
                          Bin* bin) {
    auto item = bin_ids_by_file_hash.find(file_hash);

    if (item == bin_ids_by_file_hash.end()) {
        Util util;
        Chunk* representative = bin->get_representative_chunk();

        util.init_hash();
        util.hash_chunk(representative->get_data(), representative->get_length());
        util.finish_hash();

        char* representative_chunk_hash_c_str = util.get_result();
        std::string representative_chunk_hash(representative_chunk_hash_c_str, SHA256_DIGEST_LENGTH);
        delete[] representative_chunk_hash_c_str;

        item = bin_ids_by_representative_chunk_hash.find(representative_chunk_hash);

        if (item == bin_ids_by_representative_chunk_hash.end()) {
            bin->save();
            bin_ids_by_file_hash[file_hash] = bin->get_id();
            bin_ids_by_representative_chunk_hash[representative_chunk_hash] = bin->get_id();

            write_recepie(file_name, &bin->chunks);
        } else {
            Bin* existing_bin = Bin::load(item->second);
            std::vector<Chunk*> delta;

            for (auto new_chunk : bin->chunks) {
                util.init_hash();
                util.hash_chunk(new_chunk->get_data(), new_chunk->get_length());
                util.finish_hash();
                char* new_hash_c_str = util.get_result();
                std::string new_hash(new_hash_c_str, SHA256_DIGEST_LENGTH);
                delete[] new_hash_c_str;

                bool matched = false;

                for (auto old_chunk : existing_bin->chunks) {
                    util.init_hash();
                    util.hash_chunk(old_chunk->get_data(), old_chunk->get_length());
                    util.finish_hash();
                    char* old_hash_c_str = util.get_result();
                    std::string old_hash(old_hash_c_str, SHA256_DIGEST_LENGTH);
                    delete[] old_hash_c_str;

                    if (new_hash == old_hash) {
                        matched = true;
                        new_chunk->set_id(old_chunk->get_id());
                        break;
                    }
                }

                if (!matched) {
                    delta.push_back(new_chunk);
                }
            }

            delete existing_bin;

            bin->update(delta);
            write_recepie(file_name, &bin->chunks);
        }
    } else {
        Bin* loaded_bin = Bin::load(item->second);

        write_recepie(file_name, &loaded_bin->chunks);

        delete loaded_bin;
    }
}

void PrimaryIndex::write_recepie(std::string file_name, std::vector<Chunk*>* chunks) {
    unsigned long int file_name_length = file_name.length();
    recepie_file_.write(reinterpret_cast<const char*>(&file_name_length), sizeof(file_name_length));
    recepie_file_.write(file_name.data(), file_name_length);
    long long int cid;

    for (auto chunk : *chunks) {
        cid = chunk->get_id();

        recepie_file_.write(reinterpret_cast<const char*>(&cid), sizeof(cid));
    }

    cid = -1;
    recepie_file_.write(reinterpret_cast<const char*>(&cid), sizeof(cid));
}
