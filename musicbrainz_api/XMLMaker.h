//
// Created by Elenore on 2016. 9. 2..
//

#ifndef MUSICBRAINZ_API_XMLMAKER_H
#define MUSICBRAINZ_API_XMLMAKER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "ArtistCopy.h"

using boost::property_tree::ptree;
using boost::property_tree::write_xml;
using boost::property_tree::xml_writer_settings;

class XMLMaker {

public:
    XMLMaker();
    ~XMLMaker();
    void generateXML(std::vector<ArtistCopy> artistList);
};


#endif //MUSICBRAINZ_API_XMLMAKER_H
