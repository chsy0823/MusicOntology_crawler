//
// Created by Elenore on 2016. 8. 30..
//

#ifndef MUSICBRAINZ_API_FILEHANDLER_H
#define MUSICBRAINZ_API_FILEHANDLER_H


#pragma once

#include <vector>
#include "ArtistCopy.h"
#include <sstream>
#include <list>



class FIleHandler {

private:
    std::vector<ArtistCopy> artistList;
public:

    FIleHandler();
    ~FIleHandler();

    void readFileFromPath(std::string path);
    std::vector<ArtistCopy> getArtistList();
};


#endif //MUSICBRAINZ_API_FILEHANDLER_H
