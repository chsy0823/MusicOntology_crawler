//
// Created by Elenore on 2016. 8. 30..
//

#include "FIleHandler.h"
#include <fstream>


FIleHandler::FIleHandler() {

}
FIleHandler::~FIleHandler() {

}

std::vector<ArtistCopy> FIleHandler::getArtistList() {

    return this->artistList;
}

void FIleHandler::readFileFromPath(std::string path) {

    this->artistList.clear();

    std::ifstream inFile(path);
    std::string line;

    std::cout << "Start reading file" << std::endl;
    while(getline(inFile, line)) {

        std::stringstream linestream(line);

        ArtistCopy artist;

        std::getline(linestream, artist.id, '\t');
        std::getline(linestream, artist.gid, '\t');
        std::getline(linestream, artist.name, '\t');
        std::getline(linestream, artist.begin_date_year, '\t');
        std::getline(linestream, artist.begin_date_month, '\t');
        std::getline(linestream, artist.begin_date_day, '\t');
        std::getline(linestream, artist.end_date_year, '\t');
        std::getline(linestream, artist.end_date_month, '\t');
        std::getline(linestream, artist.end_date_day, '\t');
        std::getline(linestream, artist.type, '\t');
        std::getline(linestream, artist.area, '\t');
        std::getline(linestream, artist.gender, '\t');
        std::getline(linestream, artist.comment, '\t');
        std::getline(linestream, artist.edits_pending, '\t');
        std::getline(linestream, artist.last_updated, '\t');
        std::getline(linestream, artist.ended, '\t');
        std::getline(linestream, artist.begin_area, '\t');
        std::getline(linestream, artist.end_area, '\t');

        this->artistList.push_back(artist);
    }

    std::cout << "end reading file" << std::endl;
    inFile.close();

}