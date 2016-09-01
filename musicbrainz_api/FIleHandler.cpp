//
// Created by Elenore on 2016. 8. 30..
//

#include "FIleHandler.h"
#include <fstream>
#include <sstream>


FIleHandler::FIleHandler() {

}
FIleHandler::~FIleHandler() {

}

void FIleHandler::readFileFromPath(std::string path) {

    std::ifstream inFile(path);
    std::string line;

    std::list<MusicBrainz5::CArtist*> artistList;

    while(getline(inFile, line)) {

        std::istringstream ss(line);


        MusicBrainz5::CArtist *artist = new MusicBrainz5::CArtist();
        
        int begin_date_year, begin_date_month, begin_date_day;

        //ss >> artist->ID() >> artist->Name() >> artist->SortName() >> begin_date_year >> begin_date_month >> begin_date_day;
    }

    inFile.close();

}