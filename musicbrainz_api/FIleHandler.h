//
// Created by Elenore on 2016. 8. 30..
//

#ifndef MUSICBRAINZ_API_FILEHANDLER_H
#define MUSICBRAINZ_API_FILEHANDLER_H

#include <iostream>

#include <sstream>
#include <list>

#include "musicbrainz5/Query.h"
#include "musicbrainz5/HTTPFetch.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/Recording.h"
#include "musicbrainz5/Artist.h"

class FIleHandler {

public:

    FIleHandler();
    ~FIleHandler();

    void readFileFromPath(std::string path);
};


#endif //MUSICBRAINZ_API_FILEHANDLER_H
