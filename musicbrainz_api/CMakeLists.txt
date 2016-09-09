cmake_minimum_required(VERSION 3.5)
project(musicbrainz_api)

find_package(PkgConfig)
INCLUDE(FindPkgConfig)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp jsoncpp.cpp MusicBrainzSearcher.cpp MusicBrainzSearcher.h FIleHandler.cpp FIleHandler.h ArtistCopy.cpp ArtistCopy.h XMLMaker.cpp XMLMaker.h)
include_directories("/usr/local/include" ${LIBMONGOCXX_INCLUDE_DIRS})

pkg_check_modules(LIBMONGOCXX REQUIRED libmongocxx)


link_directories(/usr/local/lib ${LIBMONGOCXX_LIBRARY_DIRS})
add_executable(musicbrainz_api ${SOURCE_FILES})
target_link_libraries(musicbrainz_api /usr/local/lib/libmusicbrainz5cc.dylib ${LIBMONGOCXX_LIBRARIES})
