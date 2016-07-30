cmake_minimum_required(VERSION 3.3)
project(extreme_binning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcrypto")
set(OPENSSL_LIBRARIES "/usr/local/Cellar/openssl/1.0.2d_1/lib/")
set(OPENSSL_ROOT_DIR "/usr/local/Cellar/openssl/1.0.2d_1")

FIND_PACKAGE(OpenSSL)
FIND_PACKAGE(Boost COMPONENTS regex system filesystem REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

set(SOURCE_FILES backup.cpp
    chunker.cpp
    bin.cpp
    primary_index.cpp
    util.cpp
    storage.cpp
    chunk.cpp
    rabin_karp_hasher.cpp)
add_executable(extreme_binning ${SOURCE_FILES})

target_link_libraries(extreme_binning
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)