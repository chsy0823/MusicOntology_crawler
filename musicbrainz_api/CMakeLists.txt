cmake_minimum_required(VERSION 3.5)
project(musicbrainz_api)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
include_directories("/usr/local/include")
link_directories(/usr/local/lib)
add_executable(musicbrainz_api ${SOURCE_FILES})
target_link_libraries(musicbrainz_api /usr/local/lib/libmusicbrainz5cc.dylib)
