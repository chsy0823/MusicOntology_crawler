//
// Created by Elenore on 2016. 9. 2..
//

#include "XMLMaker.h"


XMLMaker::XMLMaker() {

}

XMLMaker::~XMLMaker() {

}

void XMLMaker::generateXML(std::vector<ArtistCopy> artistList) {

    for(int i = 0; i<artistList.size(); i++) {
        ArtistCopy artist = artistList.at(i);

        std::cout << "## " << artist.name << "release-group count :" << artist.totalReleaseInGroup.size() << std::endl;
    }
}