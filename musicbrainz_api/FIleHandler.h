//
// Created by Elenore on 2016. 8. 30..
//

#ifndef MUSICBRAINZ_API_FILEHANDLER_H
#define MUSICBRAINZ_API_FILEHANDLER_H

#include <iostream>

class FIleHandler {

public:

    FIleHandler();
    ~FIleHandler();

    void readFileFromPath(std::string path);
};


#endif //MUSICBRAINZ_API_FILEHANDLER_H
